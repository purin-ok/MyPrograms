#include <math.h>
#include <GL/glut.h>

#define SCALE 60

void display(void);
void second(void);
void minute(void);
void hour(void);
void resize(int w, int h);
static void timer(int dummy);

int sec = 17340;

void display(void)
{
	int i, num = 5;
	double theta, dt, x, y;

	glClear(GL_COLOR_BUFFER_BIT);

	second();
	minute();
	hour();

	sec = (sec + 1) % 43200;

	glEnd();
	glFlush();
}

void second(void)
{
	double theta;

	glColor3d(1.0, 0.0, 0.0);
	theta = (M_PI / 2.0) - (sec * M_PI / 30);

	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.9*cos(theta), 0.9*sin(theta));
}

void minute(void)
{
	double theta;

	glColor3d(0.0, 1.0, 0.0);
	theta = (M_PI / 2.0) - (sec * M_PI / 30 / 60);

	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(cos(theta), sin(theta));
}

void hour(void)
{
	double theta;

	glColor3d(0.0, 0.0, 1.0);
	theta = (M_PI / 2.0) - (sec * M_PI / 30 / 60 / 12);

	glBegin(GL_LINES);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.5*cos(theta), 0.5*sin(theta));
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
	//gluOrtho2D(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0);
	gluOrtho2D(-2000.0 / h, 2000.0 / h, -2000.0 / w, 2000.0 / w);
}

static void timer(int dummy)
{
	glutTimerFunc(1000.0 / SCALE, timer, 0);
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
