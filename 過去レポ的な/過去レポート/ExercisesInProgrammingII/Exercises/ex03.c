#include <math.h>
#include <GL/glut.h>

void display(void);
void init(void);

void display(void)
{
	int i, num = 8;
	double theta, dt, x, y;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);

	dt = 2.0 * M_PI / num;
	theta = 0.0;

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
