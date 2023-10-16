#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>

int rotate = 0;

void display(){

	int i,j;
	GLdouble p[4][3];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glColor3d(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(0,1,0);
	glColor3d(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1);
	glEnd();
	
	glutWireTeapot(1);
	
	glFlush();

}

void init(){

	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);

}

void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5,5,-5,5,-5,5);

}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glMatrixMode(GL_MODELVIEW);
	switch(rotate){
		case 1:glRotated(3.0,1.0,0.0,0.0);break;
		case 2:glRotated(3.0,0.0,1.0,0.0);break;
		case 3:glRotated(3.0,0.0,0.0,1.0);break;
		default:break;
	}
	glutPostRedisplay();

}

void keyin(
	unsigned char key,int x, int y
){
	switch(key){
		case 'p': rotate = 0;break;
		case 'x': rotate = 1;break;
		case 'y': rotate = 2;break;
		case 'z': rotate = 3;break;
		case 'q': exit(0);
		default: break;
	}
}

int main(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutTimerFunc(100,timer,0);
	glutKeyboardFunc(keyin);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;

}
