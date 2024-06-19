#include <math.h>
#include <GL/glut.h>

void display(void);
void dispXYZ(void);
void dispOctahedron(double a);
void resize(int w, int h);
static void timer(int dummy);
void init(void);

void display(void)
{
	static double a = 0.0;
	glClear(GL_COLOR_BUFFER_BIT);

	dispXYZ();
	dispOctahedron(a);

	a += M_PI / 60;

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

void dispOctahedron(double a)
{
	int i;

	GLdouble p[6][3] = {0.0};

	p[2][0] = cos(a);
	p[2][1] = -sin(a);
	p[0][0] = -p[2][0];
	p[0][1] = -p[2][1];

	p[5][0] = sin(a);
	p[5][1] = cos(a);
	p[4][0] = -p[5][0];
	p[4][1] = -p[5][1];

	p[1][2] = 1.0;
	p[3][2] = -1.0;

	/* X */
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[0]);
	glVertex3dv(p[1]);
	glVertex3dv(p[2]);
	glVertex3dv(p[3]);
	glEnd();

	/* Y */
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[1]);
	glVertex3dv(p[4]);
	glVertex3dv(p[3]);
	glVertex3dv(p[5]);
	glEnd();

	/* Z */
	glBegin(GL_LINE_LOOP);
	glVertex3dv(p[0]);
	glVertex3dv(p[4]);
	glVertex3dv(p[2]);
	glVertex3dv(p[5]);
	glEnd();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
}

static void timer(int dummy)
{
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(0.5, 0.6, 0.8, 0, 0, 0, 0, 1, 0);
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
	glutMainLoop();

	return 0;
}
