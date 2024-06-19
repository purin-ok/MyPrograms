#include <GL/glut.h>
#include <math.h>

void display(void) {
	int i;
	GLdouble p[8][3];
	p[1][0] = p[2][0] = p[5][0] = p[6][0] = \
	p[4][1] = p[5][1] = p[6][1] = p[7][1] = \
	p[0][2] = p[1][2] = p[4][2] = p[5][2] = 1 / sqrt(3);
	p[0][0] = p[3][0] = p[4][0] = p[7][0] = \
	p[0][1] = p[1][1] = p[2][1] = p[3][1] = \
	p[2][2] = p[3][2] = p[6][2] = p[7][2] = -p[1][0];
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < 4; i++) {
		glVertex3dv(p[i]);
	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	for(i = 4; i < 8; i++) {
		glVertex3dv(p[i]);
	}
	glEnd();
	
	glBegin(GL_LINES);
	for(i = 0; i < 4; i++) {
		glVertex3dv(p[i]);
		glVertex3dv(p[i + 4]);
	}
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
	gluLookAt(0.5, 0.7, 1, 0, 0, 0, 0, 1, 0);
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