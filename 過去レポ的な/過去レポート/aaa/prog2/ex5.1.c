#include<GL/glut.h>
#include<math.h>

void display(){
	
	int i;
	double theta,dt,x,y;
	static double rotAng = 0.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0.0,1.0,1.0);
	dt = 2.0*M_PI/8.0;
	theta = rotAng;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0,0);
	for(i = 0;i < 9;i++){
		x = cos(theta);
		y = sin(theta);
		glVertex2d(x,y);
		theta += dt;
	}
	glEnd();
	glFlush();
	rotAng += 3.0*M_PI/180.0;

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

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glutPostRedisplay();

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
