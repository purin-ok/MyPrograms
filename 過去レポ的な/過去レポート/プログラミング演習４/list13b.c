#include <GL/glut.h>
#include <math.h>

void display(void) {
	GLdouble p[6][3] = {0};
	p[2][0] = p[5][1] = p[1][2] = 1;
	p[0][0] = p[4][1] = p[3][2] = -1;
	
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[0]);
	glVertex3dv(p[1]);
	glVertex3dv(p[2]);
	glVertex3dv(p[3]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[0]);
	glVertex3dv(p[5]);
	glVertex3dv(p[2]);
	glVertex3dv(p[4]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[1]);
	glVertex3dv(p[5]);
	glVertex3dv(p[3]);
	glVertex3dv(p[4]);
	glEnd();

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