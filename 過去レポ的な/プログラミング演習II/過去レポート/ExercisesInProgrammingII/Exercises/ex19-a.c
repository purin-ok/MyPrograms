#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void display(void);
void dispXYZ(void);
void resize(int w, int h);
static void timer(int dummy);
void keyin(unsigned char key, int x, int y);
void mouse(int btn, int state, int x, int y);
void init(void);

GLdouble vP[8][3]={
	{-0.577, -0.577,  0.577},
	{ 0.577, -0.577,  0.577},
	{ 0.577, -0.577, -0.577},
	{-0.577, -0.577, -0.577},
	{-0.577,  0.577,  0.577},
	{ 0.577,  0.577,  0.577},
	{ 0.577,  0.577, -0.577},
	{-0.577,  0.577, -0.577},
};
int tP[6][4]={
	{3, 2, 1, 0}, {0, 1, 5, 4}, {1, 2, 6, 5},
	{4, 5, 6, 7}, {3, 7, 6, 2}, {0, 4, 7, 3}
};
GLdouble cP[6][3]={
	{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}
};

double rS =3.0, rX = 0.0,rY = 0.0,rZ = 0.0;

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT);

	//dispXYZ();

	glEnable(GL_CULL_FACE);
	for (i = 0; i < 6; i++)
	{
		glBegin(GL_POLYGON);
		glColor3dv(cP[i]);
		for (j = 0; j < 4; j++)
		{
			glVertex3dv(vP[tP[i][j]]);
		}
		glEnd();
	}

	glFlush();
}

void dispXYZ(void)
{
	glBegin(GL_LINES);

	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);

	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);

	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);

	glEnd();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -3, 3);
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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(0.5, 1, 1, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
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
