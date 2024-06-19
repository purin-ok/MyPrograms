#include <GL/glut.h>
#include <math.h>

void display(void){
	int i;
	double theta,dt,x,y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0,0.0,0.0);
	dt=2.0*M_PI/3.0;
	theta=0.0;
	glBegin(GL_POLYGON);
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

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}