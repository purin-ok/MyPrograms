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

GLdouble vP[4][3]={
	{ 1.000,  0.000,  0.000},
	{-0.333,  0.943,  0.000},
	{-0.333, -0.471,  0.816},
	{-0.333, -0.471, -0.816}
};
int tP[4][3]={
	{0, 1, 2}, {0, 3, 1},
	{0, 2, 3}, {1, 3, 2}
};
GLdouble cP[4][3]={
	{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}
};

GLfloat rotAng[3] = {0};

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	dispXYZ();

	glBegin(GL_TRIANGLES);
	for (i = 0; i < 4; i++)
	{
		glColor3dv(cP[i]);
		for (j = 0; j < 3; j++)
		{
			glVertex3dv(vP[tP[i][j]]);
		}
	}
	glEnd();

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
		case 'x': glRotated(1, 1, 0, 0);glutPostRedisplay();break;
		case 'X': glRotated(1, -1, 0, 0);glutPostRedisplay();break;
		case 'y': glRotated(1, 0, 1, 0);glutPostRedisplay();break;
		case 'Y': glRotated(1, 0, -1, 0);glutPostRedisplay();break;
		case 'z': glRotated(1, 0, 0, 1);glutPostRedisplay();break;
		case 'Z': glRotated(1, 0, 0, -1);glutPostRedisplay();break;
		//case 'l': glOrtho(-2, 2, -2, 2, -3, 3);glutPostRedisplay();break;
		//case 'u': glOrtho(-0.5, 0.5, -0.5, 0.5, -3, 3);glutPostRedisplay();break;
		case '\033': exit(0);
		default: break;
	}
}

void mouse(int btn, int state, int x, int y)
{
	if(btn == GLUT_LEFT_BUTTON)
	{
		//rS *= 1.25;
	}
	if(btn == GLUT_RIGHT_BUTTON)
	{
		//rS /= 1.25;
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
	glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	//timer(0);
	init();
	glutKeyboardFunc(keyin);
	//glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
