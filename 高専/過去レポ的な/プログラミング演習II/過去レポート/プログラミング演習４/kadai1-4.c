#include <GL/glut.h>
#include <math.h>
#define NUM 6

double rotAng = 0.0;

void display(void) {
	int i, j;
	double theta, dt;
	GLdouble p[NUM][2];
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 1.0, 0.0);

	dt = 2.0*M_PI/NUM;
	theta = rotAng;
	for(i=0; i<NUM; i++){
		p[i][0] = cos(theta);
		p[i][1] = sin(theta);
		theta += dt;
	}
	
	glBegin(GL_LINES);
	
	for(i = 0; i< NUM - 1; i++) {
		for(j = i + 1; j < NUM; j++){
			glVertex2dv(p[i]);
			glVertex2dv(p[j]);
		}
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

static void timer(int dummy) {
	glutTimerFunc(50, timer, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	timer(0);
	init();
	glutMainLoop();
	return 0;
}
