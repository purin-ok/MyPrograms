#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double g_xmin = -1.0, g_xmax = 1.0, g_ymin = -1.0, g_ymax = 1.0, g_margin = 0.5, g_xsize, g_ysize;
double g_xtics[3] = {-1.0, 1.0, 1.0}, g_ytics[3] = {-1.0, 1.0, 1.0};
double g_width = 1.0, g_height = 1.0;

double funcX(double theta);
double funcY(double theta);
void display(void);
void dispGraph(void);
void init(void);
void setRange(double left, double right, double bottom, double top);
void setXtics(double left, double right, double interval);
void setYtics(double bottom, double top, double interval);
void setRatio(double w, double h);
void drawXtics(double left, double right, double interval);
void drawYtics(double bottom, double top, double interval);
void resize(int w, int h);

double funcX(double theta)
{
	return theta - sin(theta);
}

double funcY(double theta)
{
	return 1 - cos(theta);
}

void display(void)
{
	double x, y, theta;

	glClear(GL_COLOR_BUFFER_BIT);

	dispGraph();

	glFlush();
}

void dispGraph(void)
{
	double x, y, theta;

	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(g_xmin, 0.0);
	glVertex2d(g_xmax, 0.0);
	glVertex2d(0.0, g_ymin);
	glVertex2d(0.0, g_ymax);
	glEnd();

	glRasterPos2d(g_xmax, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');
	glRasterPos2d(0.0, g_ymax);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');
	glEnd();

	glColor3d(0.0, 0.0, 0.0);
	drawXtics(g_xtics[0], g_xtics[1], g_xtics[2]);
	drawYtics(g_ytics[0], g_ytics[1], g_ytics[2]);

	glColor3d(0.0, 0.0, 0.0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (theta = 0; theta < 2 * M_PI; theta += 0.05)
	{
		glVertex2d(funcX(theta), funcY(theta));
	}
	glEnd();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void setRange(double left, double right, double bottom, double top)
{
	g_xmin = left;
	g_xmax = right;
	g_ymin = bottom;
	g_ymax = top;
}

void setXtics(double left, double right, double interval)
{
	g_xtics[0] = left;
	g_xtics[1] = right;
	g_xtics[2] = interval;
}
void setYtics(double bottom, double top, double interval)
{
	g_ytics[0] = bottom;
	g_ytics[1] = top;
	g_ytics[2] = interval;
}

void setRatio(double w, double h)
{
	g_width = w;
	g_height = h;
}

void drawXtics(double left, double right, double interval)
{
	int num, i;
	double x, l;
	char str[16];

	glLineWidth(1);
	glBegin(GL_LINES);
	l = 8 * g_ysize / glutGet(GLUT_WINDOW_HEIGHT);
	for (x = left; x <= right; x += interval)
	{
		glVertex2d(x, -l);
		glVertex2d(x, l);
	}
	glEnd();

	for (x = left; x <= right; x += interval)
	{
		num = sprintf(str, "%6.2f", x);
		glRasterPos2d(
			x - 4 * num * g_xsize / glutGet(GLUT_WINDOW_WIDTH),
			-8 * g_ysize / glutGet(GLUT_WINDOW_HEIGHT) - l
		);
		for (i = 0; i < num; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		}
	}
	glEnd();
}

void drawYtics(double bottom, double top, double interval)
{
	int num, i;
	double y, l;
	char str[16];

	glLineWidth(1);
	glBegin(GL_LINES);
	l = 8 * g_xsize / glutGet(GLUT_WINDOW_WIDTH);
	for (y = bottom; y <= top; y += interval)
	{
		glVertex2d(-l, y);
		glVertex2d(l, y);
	}
	glEnd();

	for (y = bottom; y <= top; y += interval)
	{
		num = sprintf(str, "%6.2f", y);
		glRasterPos2d(
			-8 * num * g_xsize / glutGet(GLUT_WINDOW_WIDTH) - l,
			y - 4 * g_ysize / glutGet(GLUT_WINDOW_HEIGHT)
		);
		for (i = 0; i < num; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
		}
	}
	glEnd();
}

void resize(int w, int h)
{
	double l, r, b, t;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (g_height * w < g_width * h)
	{
		l = g_xmin - g_margin;
		r = g_xmax + g_margin;
		b = ((g_ymin - g_margin) * h / w) * (g_width / g_height);
		t = ((g_ymax + g_margin) * h / w) * (g_width / g_height);
	}
	else
	{
		l = ((g_xmin - g_margin) * w / h) * (g_height / g_width);
		r = ((g_xmax + g_margin) * w / h) * (g_height / g_width);
		b = g_ymin - g_margin;
		t = g_ymax + g_margin;
	}
	gluOrtho2D(l, r, b, t);
	g_xsize = r - l;
	g_ysize = t - b;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	setRange(-1.7, 7.5, -0.5, 3.0);
	setXtics(0.0, 6.28, 3.14);
	setYtics(0.0, 2.0, 1.0);
	setRatio(5, 4);

	init();
	glutMainLoop();

	return 0;
}
