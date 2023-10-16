#include <GL/glut.h>
#include <math.h>

GLUquadric *myQuad;
int isAnime=1;

void display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	glutWireTeapot(1.0);
	glEnd();
	glutSwapBuffers();
}

void init(void){
	myQuad=gluNewQuadric();
	gluQuadricDrawStyle(myQuad,GLU_LINE);
	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3,3,-3,3,-3,3);
}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glMatrixMode(GL_MODELVIEW);
	if (isAnime==1) glRotated(3.0,0.0,0.0,1.0);
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y){
	if((btn==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)) {
		if (isAnime==0) isAnime=1;
			else isAnime=0;
	}
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(700,300);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100,timer,0);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}

