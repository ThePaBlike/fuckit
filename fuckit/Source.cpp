//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//#include <math.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include "glui.h"
//#include "toInclude.h"
//#include "math_3d.h"
//
//void Make();
//// Buffers
//GLuint VBO;
//GLuint IBO;
//GLuint gWorldLocation;
//
//#pragma region Shaders
//static const char* pVS = "                                                          \n\
//#version 330                                                                        \n\
//                                                                                    \n\
//layout (location = 0) in vec3 Position;                                             \n\
//                                                                                    \n\
//uniform mat4 gWorld;                                                                \n\
//                                                                                    \n\
//out vec4 Color;                                                                     \n\
//                                                                                    \n\
//void main()                                                                         \n\
//{                                                                                   \n\
//    gl_Position = gWorld * vec4(Position, 1.0);                                     \n\
//    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);                                   \n\
//}";
//
//static const char* pFS = "                                                          \n\
//#version 330                                                                        \n\
//                                                                                    \n\
//in vec4 Color;                                                                      \n\
//                                                                                    \n\
//out vec4 FragColor;                                                                 \n\
//                                                                                    \n\
//void main()                                                                         \n\
//{                                                                                   \n\
//    FragColor = vec4(0.5, 0.5, 0.5, 1.0);                                                              \n\
//}";
//#pragma endregion
//
//
//// Поверхность
//Surface * surface;
//
//// Чужое
//float xy_aspect;
//int   last_x, last_y;
//float rotationX = 0.0, rotationY = 0.0;
//int   main_window;
//
//
///** These are the live variables passed into GLUI ***/
//int   wireframe = 1;
//int   type_of_surf = 0, prev_tof = 0;
//int   segments_x = 16, segments_y = 16;
//float _a = 1.0f, _b = 1.0f, _c = 1.0f;
//// Using a char buffer as a live var is also possible, but it is dangerous 
//// because GLUI doesn't know how big your buffer is.  
//// But still, it works as long as text doesn't happen to overflow.
////char  text[200] = {"Hello World!"};
//
//GLUI_Checkbox   *checkbox;
//GLUI_Spinner    *spinner_segments;
//GLUI_Spinner	*spinner_params;
//GLUI_RadioGroup *radio;
//GLUI_Rotation	*rotation;
//float matrix[16];
///**************************************** control_cb() *******************/
///* GLUI control callback                                                 */
//
//void control_cb(int control)
//{
//	/********************************************************************
//	Here we'll print the user id of the control that generated the
//	callback, and we'll also explicitly get the values of each control.
//	Note that we really didn't have to explicitly get the values, since
//	they are already all contained within the live variables:
//	'wireframe',  'segments',  'obj',  and 'text'
//	********************************************************************/
//
//	printf("callback: %d\n", control);
//	printf("             checkbox: %d\n", checkbox->get_int_val());
//	printf("              spinner: %d\n", spinner_segments->get_int_val());
//	printf("          radio group: %d\n", radio->get_int_val());
//	printf("          segm x t: %d\n", segments_x);
//	printf("          segm y s: %d\n", segments_y);
//	printf("          type of surf: %d\n", type_of_surf);
//}
//
//void myGlutIdle(void)
//{
//	/* According to the GLUT specification, the current window is
//	undefined during an idle callback.  So we need to explicitly change
//	it if necessary */
//	if (glutGetWindow() != main_window)
//		glutSetWindow(main_window);
//	
//	glutPostRedisplay();	
//}
//
//void myGlutReshape(int x, int y)
//{
//	xy_aspect = (float)x / (float)y;
//	glViewport(0, 0, x, y);
//	glDepthRange(-1000, 1000);
//	gluPerspective(45, xy_aspect, 0, 100);
//	glutPostRedisplay();
//}
//
//void myGlutDisplay(void)
//{
//	glClearColor(.9f, .9f, .9f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-xy_aspect*.08, xy_aspect*.08, -.08, .08, .1, 15.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0.0f, 0.0f, -1.6f);
//	glRotatef(rotationY, 0.0, 1.0, 0.0);
//	glRotatef(rotationX, 1.0, 0.0, 0.0);
//
//	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, matrix);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//
//	glDrawElements(wireframe? GL_LINE_LOOP : GL_QUADS, surface->GetIndexLength(), GL_UNSIGNED_INT, 0);
//
//	glDisableVertexAttribArray(0);
//
//	glutSwapBuffers();
//
//	/*if (_a != prev_a || _b != prev_b || _c != prev_c ||
//		segments_x != prev_seg_x || segments_y != prev_seg_y ||
//		type_of_surf != prev_tof)
//	{
//		Make();
//	}*/
//}
//
//#pragma region Shaders
//static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
//{
//	GLuint ShaderObj = glCreateShader(ShaderType);
//
//	if (ShaderObj == 0) {
//		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
//		exit(0);
//	}
//
//	const GLchar* p[1];
//	p[0] = pShaderText;
//	GLint Lengths[1];
//	Lengths[0] = strlen(pShaderText);
//	glShaderSource(ShaderObj, 1, p, Lengths);
//	glCompileShader(ShaderObj);
//	GLint success;
//	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		GLchar InfoLog[1024];
//		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
//		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
//		exit(1);
//	}
//
//	glAttachShader(ShaderProgram, ShaderObj);
//}
//
//static void CompileShaders()
//{
//	GLuint ShaderProgram = glCreateProgram();
//
//	if (ShaderProgram == 0) {
//		fprintf(stderr, "Error creating shader program\n");
//		exit(1);
//	}
//
//	AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
//	AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);
//
//	GLint Success = 0;
//	GLchar ErrorLog[1024] = { 0 };
//
//	glLinkProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
//	if (Success == 0) {
//		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
//		exit(1);
//	}
//
//	glValidateProgram(ShaderProgram);
//	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
//	if (!Success) {
//		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//		exit(1);
//	}
//
//	glUseProgram(ShaderProgram);
//
//	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
//	assert(gWorldLocation != 0xFFFFFFFF);
//}
//#pragma endregion
//#pragma region Buffers
//static void CreateVertexBuffer()
//{
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(surface->GetVertexes().at(0)) * surface->GetVertexLength(), surface->GetVertexes().data(), GL_STATIC_DRAW);
//}
//
//static void CreateIndexBuffer()
//{
//	glGenBuffers(1, &IBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(surface->GetIndexes().at(0)) * surface->GetIndexLength(), surface->GetIndexes().data(), GL_STATIC_DRAW);
//}
//#pragma endregion
//
//void Make(int control)
//{
//	if (segments_x % 2 == 1)
//		segments_x++;
//	if (segments_y % 2 == 1)
//		segments_y++;
//	
//	switch (type_of_surf)
//	{
//	case 0: // Ellipsoid
//		surface = new Ellipsoid(_a, _b, _c, segments_x, segments_y, Interval(0, 2 * PI), Interval(0, 2 * PI));
//		break;
//	case 1:	// Cylinder
//		surface = new Cylinder(_a, _b, _c, segments_x, segments_y, Interval(-5, 5), Interval(0, 2 * PI));
//		break;
//	case 2:	// Cone
//		surface = new Cone(_a, _b, _c, segments_x, segments_y, Interval(-5, 5), Interval(0, 2 * PI));
//		break;
//	case 3:	// Thor
//
//		break;
//	case 4:
//
//		break;
//	}
//	
//	CreateVertexBuffer();
//	CreateIndexBuffer();
//	glutPostRedisplay();
//}
//
//int main(int argc, char* argv[])
//{
//	// Создаём элипсоид
//	surface = new Ellipsoid(_a, _b, _c, segments_x, segments_y, Interval(0, 2*PI), Interval(0, 2 * PI));
//
//
//	/****************************************/
//	/*   Initialize GLUT and create window  */
//	/****************************************/
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitWindowPosition(50, 50);
//	glutInitWindowSize(800, 600);
//
//	main_window = glutCreateWindow("Surface Viewer");
//	glutDisplayFunc(myGlutDisplay);
//	glutReshapeFunc(myGlutReshape);
//	glutIdleFunc(myGlutIdle);
//
//	/****************************************/
//	/*       Set up OpenGL lights           */
//	/****************************************/
//
//	GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
//	GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
//	GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
//	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//	/****************************************/
//	/*          Enable z-buferring          */
//	/****************************************/
//
//	glEnable(GL_DEPTH_TEST);
//
//	/****************************************/
//	/*         Here's the GLUI code         */
//	/****************************************/
//
//	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 850, 50); /* name, flags,
//															  x, and y */
//	new GLUI_StaticText(glui, "Control Panel");
//	new GLUI_Separator(glui);	//------------------------------
//	checkbox = new GLUI_Checkbox(glui, "Wireframe", &wireframe, 1, Make);
//	GLUI_Panel *obj_panel = new GLUI_Panel(glui, "Surface Type");
//	radio = new GLUI_RadioGroup(obj_panel, &type_of_surf, 2, Make);
//	new GLUI_RadioButton(radio, "Ellipsoid");
//	new GLUI_RadioButton(radio, "Cylinder");
//	new GLUI_RadioButton(radio, "Cone");
//	new GLUI_RadioButton(radio, "Thor");
//	new GLUI_Separator(glui);	//------------------------------	
//	spinner_params = new GLUI_Spinner(glui, "a:", &_a, 3, Make);
//	spinner_params = new GLUI_Spinner(glui, "b:", &_b, 4, Make);
//	spinner_params = new GLUI_Spinner(glui, "c:", &_c, 5, Make);
//	new GLUI_Separator(glui);	//------------------------------
//	spinner_segments = new GLUI_Spinner(glui, "Segments X:", &segments_x, 6, Make);
//	spinner_segments = new GLUI_Spinner(glui, "Segments Y:", &segments_y, 7, Make);
//
//	rotation = new GLUI_Rotation(glui, "Rotation", matrix, 8, control_cb);
//	rotation->reset();
//
//	new GLUI_Button(glui, "Animate", 0, (GLUI_Update_CB)exit);
//	glui->set_main_gfx_window(main_window);
//
//	/* We register the idle callback with GLUI, *not* with GLUT */
//	GLUI_Master.set_glutIdleFunc(myGlutIdle);
//	GLUI_Master.set_glutIdleFunc(NULL);
//
//	// Wireframe mode
//	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma region shader
//	// Must be done after glut is initialized!
//	GLenum res = glewInit();
//	if (res != GLEW_OK) {
//		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
//		return 1;
//	}
//
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	CreateVertexBuffer();
//	CreateIndexBuffer();
//
//	CompileShaders();
//
//#pragma endregion
//
//	glutMainLoop();
//
//	return EXIT_SUCCESS;
//}