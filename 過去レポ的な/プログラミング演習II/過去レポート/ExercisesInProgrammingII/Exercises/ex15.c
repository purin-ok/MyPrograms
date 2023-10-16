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

GLUquadric *obj;
double rS =3.0, rX = 0.0,rY = 0.0,rZ = 0.0;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	dispXYZ();

	//gluSphere(obj, 1.0, 8, 8);
	//gluCylinder(obj, 0.5, 0.7, 0.8, 10, 4);
	//gluDisk(obj, 0.3, 0.8, 10, 2);
	gluPartialDisk(obj, 0.3, 0.8, 10, 2, 180.0, 90.0);

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

	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
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
