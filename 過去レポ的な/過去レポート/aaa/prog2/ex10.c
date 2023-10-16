#include<GL/glut.h>
#include<math.h>

void display(){

	int i,j;
	static double theta = 0.0;
	GLdouble p[4][3];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(cos(theta),-sin(theta),0);
	glColor3d(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(sin(theta),cos(theta),0);
	glColor3d(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1);
	glEnd();
	glutSwapBuffers();
	
	theta += 3.0*M_PI/180.0;

}

void init(){

	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);

}

void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3,3,-3,3,-3,3);

}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glutPostRedisplay();

}


int main(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutTimerFunc(100,timer,0);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;

}
