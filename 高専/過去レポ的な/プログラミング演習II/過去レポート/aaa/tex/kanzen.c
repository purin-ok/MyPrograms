#include<GL/glut.h>
#include<math.h>

#define Vertex_Num 7
double rotAng = 0.0;

void display(void) {
	int i;
	double theta, dt, x, y,delta;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	dt = 2.0 * M_PI / Vertex_Num;
	glBegin ( GL_LINE_STRIP );
	for (i = 0; i < Vertex_Num -1; i++) {
		theta = rotAng + dt*i;
		for (delta = i+1; delta <Vertex_Num ; delta++) {
			x = cos( theta );
			y = sin( theta );
			glVertex2d (x, y);
			x = cos(theta - delta *dt );
			y = sin(theta - delta *dt );
			glVertex2d (x, y);
		}
	}
	glEnd();
	glFlush();
	rotAng += M_PI / 120;
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
