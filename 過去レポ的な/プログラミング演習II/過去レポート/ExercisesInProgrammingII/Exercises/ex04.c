#include <GL/glut.h>

#define WCS_L -3.0
#define WCS_R 3.0
#define WCS_B -2.0
#define WCS_T 2.0
#define MARGIN 0.2

void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(0.5, 0.5, 0.5);
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glVertex2d(WCS_L, WCS_B);
	glVertex2d(WCS_R, WCS_B);
	glVertex2d(WCS_R, WCS_T);
	glVertex2d(WCS_L, WCS_T);
	glEnd();

	glFlush();
}

void resize(int w, int h)
{
	GLdouble l, r, b, t, tmp1, tmp2;
	GLdouble wcs_w = WCS_R - WCS_L, wcs_h = WCS_T - WCS_B;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if ((wcs_h * w) < (wcs_w * h))
	{
		tmp1 = WCS_B + WCS_T;
		tmp2 = wcs_w * h / w;
		l = WCS_L;
		r = WCS_R;
		b = (tmp1 - tmp2) / 2;
		t = (tmp1 + tmp2) / 2;
	}
	else
	{
		tmp1 = WCS_L + WCS_R;
		tmp2 = wcs_h * w / h;
		l = (tmp1 - tmp2) / 2;
		r = (tmp1 + tmp2) / 2;
		b = WCS_B;
		t = WCS_T;
	}
	gluOrtho2D(l, r, b, t);
}

void keyin(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '\033': exit(0);
		default: break;
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutKeyboardFunc(keyin);
	glutMainLoop();

	return 0;
}
