#include <GL/glut.h>

void changeSize(int w, int h) {
	// предупредим деление на ноль
	// если окно сильно перет€нуто будет
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определ€ем окно просмотра
	glViewport(0, 0, w, h);

	// установить корректную перспективу.
	gluPerspective(45, ratio, 1, 1000);

	// вернутьс€ к модели
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

	// инициализаци€
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("”рок 2");

	// регистраци€
	glutDisplayFunc(renderScene);

	// Ќова€ функци€ изменени€ размеров окна
	glutReshapeFunc(changeSize);

	// основной цикл
	glutMainLoop();
}