#include <GL/glut.h>
#include <math.h>

#define ID_B 100
#define ID_L 101
#define ID_U 102
#define HEIGHT_B 0.3
#define HEIGHT_L 1.8
#define WIDTH_L 0.1
#define HEIGHT_U 1.2
#define WIDTH_U 0.2

#define SPEED 10.0


GLUquadric *myQuad;
GLdouble rotAng[3]={0};
double speed=0;
int isAnime=1;

void display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1,1,1,0,0,0,0,1,0);
	glRotated(rotAng[0],0,1,0);
	glCallList(ID_B);
	glTranslated(0,HEIGHT_B/2.0,0);
	glRotated(rotAng[1],0,0,1);
	glCallList(ID_L);
	glTranslated(-WIDTH_L/2,HEIGHT_L,0);
	glRotated(rotAng[2],0,0,1);
	glCallList(ID_U);
	glutSwapBuffers();
}

void init(void){
	myQuad=gluNewQuadric();
	gluQuadricDrawStyle(myQuad,GLU_LINE);
	glClearColor(1.0,1.0,1.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);
	
	glNewList(ID_B,GL_COMPILE);
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(0.0, HEIGHT_B, 0.0);
	glScalef(0.5,HEIGHT_B,0.5);
	glRotated(90.0,1.0,0.0,0.0);
	gluCylinder(myQuad,1,1,2,50,4);
	glPopMatrix();
	glEndList();
	
	glNewList(ID_L,GL_COMPILE);
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(0.0,0.5*HEIGHT_L,WIDTH_L);
	glScalef(WIDTH_L,HEIGHT_L,WIDTH_L);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();
	
	glNewList(ID_U,GL_COMPILE);
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(0.0,0.5*HEIGHT_U,WIDTH_U);
	glScalef(WIDTH_U,HEIGHT_U,WIDTH_U);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();
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
	if (isAnime==1){
		rotAng[0]+=2.0;
		rotAng[1]=sin(speed)*10.0;
		rotAng[2]=sin(speed*4)*10.0;
		speed+=0.2;
	}
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

