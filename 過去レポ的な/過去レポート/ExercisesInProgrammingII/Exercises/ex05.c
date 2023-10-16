#include <math.h>
#include <GL/glut.h>

void display(void);
void init(void);
void resize(int w, int h);
static void timer(int dummy);

//int deg = 0;

void display(void)
{
	static int deg = 0;
	int i, num = 5;
	double theta, dt, x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);

	dt = 2.0 * M_PI / num;
	theta = deg / 360.0 * 2.0 * M_PI;
	deg = (deg + 1) % 360;

	//glBegin(GL_TRIANGLES);
	glBegin(GL_POLYGON);

	for (i = 0; i < num; i++)
	{
		x = cos(theta);
		y = sin(theta);
		glVertex2d(x, y);
		theta += dt;
	}

	glEnd();
	glFlush();
}

void init(void)
{
	// Black
	//glClearColor(0.0, 0.0, 0.0, 1.0);

	// Red
	//glClearColor(1.0, 0.0, 0.0, 1.0);

	// Green
	//glClearColor(0.0, 1.0, 0.0, 1.0);

	// Blue
	//glClearColor(0.0, 0.0, 1.0, 1.0);

	// Cyan
	//glClearColor(0.0, 1.0, 1.0, 1.0);

	// Magenta
	//glClearColor(1.0, 0.0, 1.0, 1.0);

	// Yellow
	//glClearColor(1.0, 1.0, 0.0, 1.0);

	// White
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
