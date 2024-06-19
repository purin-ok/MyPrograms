#include <GL/glut.h>
#include <math.h>

double rotAng = 0.0;

void display(void) {
	int i;
	double theta, dt, x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	dt = 2.0*M_PI/3.0;
	theta = rotAng;
	glBegin(GL_TRIANGLES);
	for(i=0; i<3; i++){
		x = cos(theta);
		y = sin(theta);
		glVertex2d(x, y);
		theta += dt;
	}
	glEnd();
	glFlush();
	rotAng += 3.0*M_PI/180.0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void idle(void){
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}

