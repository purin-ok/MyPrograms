#include <math.h>
#include <GL/glut.h>

void display(void);
void init(void);

void display(void)
{
	double theta, dt;

	glClear(GL_COLOR_BUFFER_BIT);

	dt = 2.0 * M_PI / 3;
	theta = 0.0;

	glBegin(GL_POLYGON);

	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(cos(theta), sin(theta));
	theta += dt;
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(cos(theta), sin(theta));
	theta += dt;
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(cos(theta), sin(theta));

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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}
