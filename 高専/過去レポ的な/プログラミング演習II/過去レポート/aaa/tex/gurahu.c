#include<GL/glut.h>
#include<math.h>


void display(void) {
	double theta,x, y,c_theta;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin ( GL_LINE_STRIP );
	for (theta = 0.0; theta <= 2*M_PI; theta+=0.05) {
		c_theta=cos(theta);
		x=c_theta*(1+c_theta)*0.2;
		y=sin(theta)*(1+c_theta)*0.2;
		glVertex2d(x,y);
	}
	glEnd();
	glFlush();
}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glutPostRedisplay();
}


void init(){

	glClearColor(0.0,0.0,0.0,1.0);

}

void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		if(w>=h){
		gluOrtho2D(
			-(double)(w)/h,(double)(w)/h,
			-1.0,1.0
			);
		}else{
		gluOrtho2D(
			-1.0,1.0,
			-(double)(h)/w,(double)(h)/w
			);
		}

}


int main(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutTimerFunc(100,timer,0);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;

}
