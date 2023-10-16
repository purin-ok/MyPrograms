#include <GL/glut.h>
#include <math.h>

void display(void){
	double theta,x,y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(-0.5,0.0);
	glVertex2d(3.2,0.0);
	glVertex2d(0.0,-M_PI);
	glVertex2d(0.0,M_PI);
	for(x=0;x<=3;x+=1){
		glVertex2d(x,-0.05);
		glVertex2d(x,0.05);
	}
	for(y=-1.5;y<=1.5;y+=0.5){
		glVertex2d(-0.05,y);
		glVertex2d(0.05,y);
	}
	glEnd();
	glColor3d(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	for(theta=0;theta<2*M_PI;theta+=0.02*M_PI){
		x=cos(theta)*(1+cos(theta));
		y=sin(theta)*(1+cos(theta));
		glVertex2d(x,y);
	}
	glEnd();
	glFlush();
}

void init(void){
	glClearColor(1.0,1.0,1.0,1.0);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.5,6.5,-1.5,1.5);
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(700,300);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}

/*
カージオイド

		
サイクロイド(ウインドウの中に入らなかったから潰した)
		x=theta-sin(theta);
		y=1-cos(theta);
		y/=1.5;


4尖点の内サイクロイド
		x=cos(theta)*cos(theta)*cos(theta);
		y=sin(theta)*sin(theta)*sin(theta);
*/