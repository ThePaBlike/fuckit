#include <GL/glut.h>

void changeSize(int w, int h) {
	// ����������� ������� �� ����
	// ���� ���� ������ ���������� �����
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// ���������� ������� ��������
	glMatrixMode(GL_PROJECTION);

	// Reset �������
	glLoadIdentity();

	// ���������� ���� ���������
	glViewport(0, 0, w, h);

	// ���������� ���������� �����������.
	gluPerspective(45, ratio, 1, 1000);

	// ��������� � ������
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.5, -1.5, -5.0);
	glVertex3f(0.0, 1.5, -5.0);
	glVertex3f(1.5, -1.5, -5.0);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// �������������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("���� 2");

	// �����������
	glutDisplayFunc(renderScene);

	// ����� ������� ��������� �������� ����
	glutReshapeFunc(changeSize);

	// �������� ����
	glutMainLoop();
}