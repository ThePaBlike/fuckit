#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glui.h"
#include "toInclude.h"
#include "math_3d.h"

int	main_window;

// the camera info  
float eye[3];
float lookat[3];

#pragma region Changes
void Make();
// Buffers
GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;

#pragma region Shaders
static const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
                                                                                    \n\
uniform mat4 gWorld;                                                                \n\
                                                                                    \n\
out vec4 Color;                                                                     \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = gWorld * vec4(Position, 1.0);                                     \n\
    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);                                   \n\
}";

static const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
in vec4 Color;                                                                      \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = vec4(0.5, 0.5, 0.5, 1.0);                                                              \n\
}";
#pragma endregion

// Поверхность
int   wireframe = 1;
int   type_of_surf = 0, prev_tof = 0;
int   segments_x = 50, segments_y = 50;
float _a = 1.0f, _b = 1.0f, _c = 1.0f;

Surface * surface;
float matrix[16];
int mode;
#pragma endregion

int line_width = 1;
int point_size = 1;

// pointers for all of the glui controls
GLUI *glui;
GLUI_Rollout		*surface_rollout;
GLUI_RadioGroup		*radio_tof;
GLUI_RadioGroup		*radio_mode;
GLUI_Rollout		*rollout_modes;
GLUI_Rollout		*anim_rollout;
GLUI_Button			*action_button;

GLUI_Rollout	*rollout_segments;
GLUI_Rollout	*rollout_settings;
GLUI_Spinner    *spinner_segments;
GLUI_Spinner	*spinner_settings;
GLUI_Rollout	*rollout_params;
GLUI_Spinner	*spinner_params;


// the user id's that we can use to identify which control
// caused the callback to be called
#define CB_DEPTH_BUFFER 0
#define CB_ACTION_BUTTON 1
#define CB_RESET 2

// walking action variables
//
GLfloat step = 0;
GLfloat live_anim_speed = 3;

// live variables
// each of these are associated with a control in the interface.
// when the control is modified, these variables are automatically updated
float live_object_rotation[16];
float live_object_xz_trans[2];
float live_object_y_trans;
int live_draw_floor;
int live_draw_object;
int live_use_depth_buffer;



void normalize(float v[3])
{
	float l = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	l = 1 / (float)sqrt(l);

	v[0] *= l;
	v[1] *= l;
	v[2] *= l;
}

void crossproduct(float a[3], float b[3], float res[3])
{
	res[0] = (a[1] * b[2] - a[2] * b[1]);
	res[1] = (a[2] * b[0] - a[0] * b[2]);
	res[2] = (a[0] * b[1] - a[1] * b[0]);
}

float length(float v[3])
{
	return (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}


void myGlutIdle(void)
{
	// make sure the main window is active
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	// if you have moving objects, you can do that here

	// just keep redrawing the scene over and over
	glutPostRedisplay();
}


// mouse handling functions for the main window
// left mouse translates, middle zooms, right rotates
// keep track of which button is down and where the last position was
int cur_button = -1;
int last_x;
int last_y;

// catch mouse up/down events
void myGlutMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		cur_button = button;
	else
	{
		if (button == cur_button)
			cur_button = -1;
	}

	last_x = x;
	last_y = y;
}

// catch mouse move events
void myGlutMotion(int x, int y)
{
	// the change in mouse position
	int dx = x - last_x;
	int dy = y - last_y;

	float scale, len, theta;
	float neye[3], neye2[3];
	float f[3], r[3], u[3];

	switch (cur_button)
	{
		//case GLUT_LEFT_BUTTON:
		//	// translate
		//	f[0] = lookat[0] - eye[0];
		//	f[1] = lookat[1] - eye[1];
		//	f[2] = lookat[2] - eye[2];
		//	u[0] = 0;
		//	u[1] = 1;
		//	u[2] = 0;

		//	// scale the change by how far away we are
		//	scale = sqrt(length(f)) * 0.007;

		//	crossproduct(f, u, r);
		//	crossproduct(r, f, u);
		//	normalize(r);
		//	normalize(u);

		//	eye[0] += -r[0] * dx*scale + u[0] * dy*scale;
		//	eye[1] += -r[1] * dx*scale + u[1] * dy*scale;
		//	eye[2] += -r[2] * dx*scale + u[2] * dy*scale;

		//	lookat[0] += -r[0] * dx*scale + u[0] * dy*scale;
		//	lookat[1] += -r[1] * dx*scale + u[1] * dy*scale;
		//	lookat[2] += -r[2] * dx*scale + u[2] * dy*scale;

		//	break;

	case GLUT_RIGHT_BUTTON:
		// zoom
		f[0] = lookat[0] - eye[0];
		f[1] = lookat[1] - eye[1];
		f[2] = lookat[2] - eye[2];

		len = length(f);
		normalize(f);

		// scale the change by how far away we are
		len -= sqrt(len)*dx*0.03;
		if (len > 2)
		{
			eye[0] = lookat[0] - len*f[0];
			eye[1] = lookat[1] - len*f[1];
			eye[2] = lookat[2] - len*f[2];
		}
		// make sure the eye and lookat points are sufficiently far away
		// push the lookat point forward if it is too close
		if (len < 1)
		{
			printf("lookat move: %f\n", len);
			lookat[0] = eye[0] + f[0];
			lookat[1] = eye[1] + f[1];
			lookat[2] = eye[2] + f[2];
		}

		break;

	case GLUT_LEFT_BUTTON:
		// rotate

		neye[0] = eye[0] - lookat[0];
		neye[1] = eye[1] - lookat[1];
		neye[2] = eye[2] - lookat[2];

		// first rotate in the x/z plane
		theta = -dx * 0.007;
		neye2[0] = (float)cos(theta)*neye[0] + (float)sin(theta)*neye[2];
		neye2[1] = neye[1];
		neye2[2] = -(float)sin(theta)*neye[0] + (float)cos(theta)*neye[2];


		// now rotate vertically
		theta = -dy * 0.007;

		f[0] = -neye2[0];
		f[1] = -neye2[1];
		f[2] = -neye2[2];
		u[0] = 0;
		u[1] = 1;
		u[2] = 0;
		crossproduct(f, u, r);
		crossproduct(r, f, u);
		len = length(f);
		normalize(f);
		normalize(u);

		neye[0] = len * ((float)cos(theta)*f[0] + (float)sin(theta)*u[0]);
		neye[1] = len * ((float)cos(theta)*f[1] + (float)sin(theta)*u[1]);
		neye[2] = len * ((float)cos(theta)*f[2] + (float)sin(theta)*u[2]);

		eye[0] = lookat[0] - neye[0];
		eye[1] = lookat[1] - neye[1];
		eye[2] = lookat[2] - neye[2];

		break;
	}


	last_x = x;
	last_y = y;

	glutPostRedisplay();
}

// you can put keyboard shortcuts in here
void myGlutKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// quit
	case 27:
	case 'q':
	case 'Q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}

// the window has changed shapes, fix ourselves up
void myGlutReshape(int	x, int y)
{
	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
	glViewport(tx, ty, tw, th);

	glutPostRedisplay();
}

void DrawElements()
{
	switch (mode)
	{
	case 0:
		glDrawElements(GL_LINE_LOOP, surface->GetIndexLength(), GL_UNSIGNED_INT, 0);
		break;
	case 1:
		glDrawElements(GL_LINES, surface->GetIndexLength(), GL_UNSIGNED_INT, 0);
		break;
	case 2:
		glDrawElements(GL_POINTS, surface->GetIndexLength(), GL_UNSIGNED_INT, 0);
		break;
	}
}

// draw the scene
void myGlutDisplay(void)
{
	glClearColor(0.6, 0.6, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// projection transform
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 1000);

	// camera transform
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], 0, 1, 0);


	//
	// draw some stuff
	//
#pragma region Changes
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, matrix);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	DrawElements();

	glDisableVertexAttribArray(0);
#pragma endregion


	//if (live_draw_floor)
	//{
	//	glBegin(GL_TRIANGLE_FAN);
	//	glColor3f(0.4f, 0.4f, 0.4f);    // note: color is state and only needs to be set once
	//	glVertex3f(-10, 0, -10);
	//	glVertex3f(10, 0, -10);
	//	glVertex3f(10, 0, 10);
	//	glVertex3f(-10, 0, 10);
	//	glEnd();
	//}

	//if (live_draw_object)
	//{
	//	glColor3f(0, 1, 1);

	//	glPushMatrix();
	//	glTranslatef(live_object_xz_trans[0], live_object_y_trans, -live_object_xz_trans[1]);
	//	glMultMatrixf(live_object_rotation);

	//	switch (live_object_type)
	//	{
	//	case 0:
	//		glutSolidCube(2);
	//		break;
	//	case 1:
	//		glutSolidSphere(2, 30, 30);
	//		break;
	//	case 2:
	//		glutSolidTorus(0.5, 2, 30, 30);
	//		break;
	//	}

	//	glPopMatrix();
	//}

	glutSwapBuffers();
}

// some controls generate a callback when they are changed
void glui_cb(int control)
{

	switch (control)
	{
	case CB_DEPTH_BUFFER:
		if (live_use_depth_buffer)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		break;
	case CB_ACTION_BUTTON:
		if (step < 0)
		{
			step = 0;
			action_button->set_name("Stop");
		}
		else
		{
			step = -1;
			action_button->set_name("Start");
		}
		break;
	case CB_RESET:
		//
		// put your reset callback here
		//
		break;
	}

	glutPostRedisplay();
}

#pragma region Changes
#pragma region Shaders
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
	AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	//glUseProgram(ShaderProgram);

	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}
#pragma endregion
#pragma region Buffers
static void CreateVertexBuffer()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(surface->GetVertexes().at(0)) * surface->GetVertexLength(), surface->GetVertexes().data(), GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(surface->GetIndexes().at(0)) * surface->GetIndexLength(), surface->GetIndexes().data(), GL_STATIC_DRAW);
}
#pragma endregion
float t = 1.5;
void Make(int control)
{
	glLineWidth(line_width);
	glPointSize(point_size);
	if (segments_x % 2 == 1)
		segments_x++;
	if (segments_y % 2 == 1)
		segments_y++;

	switch (type_of_surf)
	{
	case 0:
		surface = new Ellipsoid(_a, _b, _c, segments_x, segments_y, Interval(0, 2 * PI), Interval(0, 2 * PI));
		break;
	case 1:
		surface = new Cylinder(_a, _b, _c, segments_x, segments_y, Interval(0, 2 * PI), Interval(-5, 5));
		break;
	case 2:
		surface = new Cone(_a, _b, _c, segments_x, segments_y, Interval(-t, t), Interval(0, 2 * PI));
		break;
	case 3:
		surface = new Hyper_cylinder(_a, _b, _c, segments_x, segments_y, Interval(-t, t), Interval(-t, t));
		break;
	case 4:
		surface = new Elliptic_paraboloid(_a, _b, _c, segments_x, segments_y, Interval(-t, t), Interval(-PI, PI));
		break;
	case 5:
		surface = new Hyperboloid_of_one_sheet(_a, _b, _c, segments_x, segments_y, Interval(-t, t), Interval(-PI, PI));
		break;
	case 6:
		surface = new Hyperbolic_paraboloid(_a, _b, _c, segments_x, segments_y, Interval(-t, t), Interval(-t, t));
		break;
	}

	CreateVertexBuffer();
	CreateIndexBuffer();
	glutPostRedisplay();
}
#pragma endregion


// entry point
int main(int argc, char* argv[])
{

	//
	// create the glut window
	//
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(100, 100);
	main_window = glutCreateWindow("Surface viewer");

	//
	// set callbacks
	//
	glutDisplayFunc(myGlutDisplay);
	GLUI_Master.set_glutReshapeFunc(myGlutReshape);
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	GLUI_Master.set_glutKeyboardFunc(myGlutKeyboard);
	GLUI_Master.set_glutMouseFunc(myGlutMouse);
	glutMotionFunc(myGlutMotion);


	//
	// create the interface subwindow and add widgets
	//
	glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);


	// initialize live variables
	type_of_surf = 0;

	// quit button
	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	// empty space
	glui->add_statictext("");

	// the object rollout
	surface_rollout = glui->add_rollout("Surface Type");

	// the radio buttons
	radio_tof = glui->add_radiogroup_to_panel(surface_rollout, &type_of_surf, 0, Make);
	glui->add_radiobutton_to_group(radio_tof, "Ellipsoid");
	glui->add_radiobutton_to_group(radio_tof, "Cylinder");
	glui->add_radiobutton_to_group(radio_tof, "Cone");
	glui->add_radiobutton_to_group(radio_tof, "Paraboloid Cylinder");
	glui->add_radiobutton_to_group(radio_tof, "Paraboloid");
	glui->add_radiobutton_to_group(radio_tof, "Hyperboloid");
	glui->add_radiobutton_to_group(radio_tof, "Hyperbolic Paraboloid");

	// empty space
	glui->add_statictext("");

	rollout_modes = glui->add_rollout("Modes");
	radio_mode = glui->add_radiogroup_to_panel(rollout_modes, &mode, 1, Make);
	glui->add_radiobutton_to_group(radio_mode, "Line loop");
	glui->add_radiobutton_to_group(radio_mode, "Lines");
	glui->add_radiobutton_to_group(radio_mode, "Points");
	// rotation and translation controls
	// we need an extra panel to keep things grouped properly
	GLUI_Panel *transform_panel = glui->add_panel_to_panel(surface_rollout, "", GLUI_PANEL_NONE);


	//glui->add_button_to_panel(object_rollout, "Reset Object Transform", CB_RESET, glui_cb);

	// empty space
	glui->add_statictext("");

	rollout_params = glui->add_rollout("Parametrs");
	spinner_params = new GLUI_Spinner(rollout_params, "a:", &_a, 2, Make);
	spinner_params->set_float_limits(0.1f, 10.0f);
	spinner_params = new GLUI_Spinner(rollout_params, "b:", &_b, 3, Make);
	spinner_params->set_float_limits(0.1f, 10.0f);
	spinner_params = new GLUI_Spinner(rollout_params, "c:", &_c, 4, Make);
	spinner_params->set_float_limits(0.1f, 10.0f);
	glui->add_statictext("");
	rollout_segments = glui->add_rollout("Segments");
	spinner_segments = new GLUI_Spinner(rollout_segments, "Segments X:", &segments_x, 5, Make);
	spinner_segments->set_int_limits(6, 150);
	spinner_segments = new GLUI_Spinner(rollout_segments, "Segments Y:", &segments_y, 6, Make);
	spinner_segments->set_int_limits(6, 150);

	glui->add_statictext("");

	rollout_settings = glui->add_rollout("Settings");
	spinner_settings = new GLUI_Spinner(rollout_settings, "Line width: ", &line_width, 7, Make);
	spinner_settings->set_int_limits(1, 5);
	spinner_settings = new GLUI_Spinner(rollout_settings, "Point size: ", &point_size, 8, Make);
	spinner_settings->set_int_limits(1, 5);

	glui->set_main_gfx_window(main_window);

	// initialize the camera
	eye[0] = 0;
	eye[1] = 4;
	eye[2] = 2;
	lookat[0] = 0;
	lookat[1] = 0;
	lookat[2] = 0;

	// initialize gl
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

#pragma region Changes
	surface = new Ellipsoid(_a, _b, _c, segments_x, segments_y, Interval(0, 2 * PI), Interval(0, 2 * PI));
#pragma region shader
	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	CreateVertexBuffer();
	CreateIndexBuffer();

	CompileShaders();

#pragma endregion
#pragma endregion

	// give control over to glut
	glutMainLoop();

	return 0;
}










