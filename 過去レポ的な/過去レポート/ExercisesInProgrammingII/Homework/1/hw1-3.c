#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#define N 7
#define M 3

void display(void);
void dispStarPolygon(int n, int m, double theta);
void init(void);
void resize(int w, int h);
static void timer(int dummy);

void display(void)
{
	static double rotAng = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0.0, 0.0, 0.0);
	dispStarPolygon(N, M, rotAng);

	glFlush();

	rotAng += M_PI / 180;
}

void dispStarPolygon(int n, int m, double theta)
{
	int i;
	double dt;

	dt = 2.0 * M_PI * m / n;

	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; i++)
	{
		glVertex2d(cos(theta), sin(theta));
		theta += dt;
	}
	glEnd();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w < h)
	{
		gluOrtho2D(-1.0, 1.0, -(double)h / w, (double)h / w);
	}
	else
	{
		gluOrtho2D(-(double)w / h, (double)w / h, -1.0, 1.0);
	}
}

static void timer(int dummy)
{
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
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
