#include <math.h>
#include <GL/glut.h>
#include "vect.h"

void display(void);
void resize(int w, int h);
static void timer(int dummy);
void keyin(unsigned char key, int x, int y);
void mouse(int btn, int state, int x, int y);
void init(void);

double rS =3.0, rX = 0.0,rY = 0.0,rZ = 0.0;

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	//glutSolidTeapot(2.0);
	glutSolidSphere(1.0, 10, 10);
	//glutWireTeapot(2.0);
	//glutWireSphere(2.0, 10, 10);

	glEnd();

	glFlush();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
}

static void timer(int dummy)
{
	glutTimerFunc(100, timer, 0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void keyin(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'x': glRotated(rS, 1, 0, 0);break;
		case 'X': glRotated(rS, -1, 0, 0);break;
		case 'y': glRotated(rS, 0, 1, 0);break;
		case 'Y': glRotated(rS, 0, -1, 0);break;
		case 'z': glRotated(rS, 0, 0, 1);break;
		case 'Z': glRotated(rS, 0, 0, -1);break;
		case 'l': glOrtho(-2, 2, -2, 2, -3, 3);break;
		case 'u': glOrtho(-0.5, 0.5, -0.5, 0.5, -3, 3);break;
		case '\033': exit(0);
		default: glRotated(3.0, 0, 0, 0);break;
	}
}

void mouse(int btn, int state, int x, int y)
{
	if(btn == GLUT_LEFT_BUTTON)
	{
		rS *= 1.25;
	}
	if(btn == GLUT_RIGHT_BUTTON)
	{
		rS /= 1.25;
	}
}

void init(void)
{
	GLfloat IP1[4] = {0.0, 1.0, 2.0, 1.0};
	GLfloat IC1[4] = {1.0, 1.0, 0.0, 1.0};

	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(0.5, 1, 1, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_POSITION, IP1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, IC1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, IC1);
	glEnable(GL_LIGHT1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	timer(0);
	init();
	glutKeyboardFunc(keyin);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
