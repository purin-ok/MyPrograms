#include <GL/glut.h>
#include <math.h>

void display(void){
	int i;
	double theta,dt,x,y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0,0.0,0.0);
	dt=2.0*M_PI/4.0;
	theta=0.0;
	glBegin(GL_QUADS);
	for (i=0;i<6;i++){
		x=cos(theta);
		y=sin(theta);
		glVertex2d(x,y);
		theta+=dt;
	}
	glEnd();
	glFlush();
}

void init(void){
	glClearColor(0.0,0.0,0.0,1.0);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<h) gluOrtho2D(-1.0,1.0,-(double)h/w,(double)h/w);
		else gluOrtho2D(-(double)w/h,(double)w/h,-1.0,1.0);
}

void idle(void){
	glutPostRedisplay();
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}