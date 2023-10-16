#include <GL/glut.h>
#include <math.h>

GLUquadric *myQuad;

void display(void) {
	glutWireSphere(10, 0, 0);
	glFlush();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, -4, 4);
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
	myQuad = gluNewQuadric();
	gluQuadricDrawStyle(myQuad, GLU_LINE);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}