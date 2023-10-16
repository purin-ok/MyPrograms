#include <GL/glut.h>

void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(void);

GLdouble g_vP[6][3] = {
	{ 1.000,  0.000,  0.000},
	{ 0.000,  1.000,  0.000},
	{ 0.000,  0.000,  1.000},
	{-1.000,  0.000,  0.000},
	{ 0.000, -1.000,  0.000},
	{ 0.000,  0.000, -1.000}
};
int g_tP[8][3] = {
	{0, 1, 2}, {5, 1, 0}, {3, 1, 5}, {2, 1, 3},
	{2, 4, 0}, {0, 4, 5}, {5, 4, 3}, {3, 4, 2}
};
GLfloat g_rotAng[3] = {15, 0, 90};

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotated(g_rotAng[0], 1, 0, 0);
	glRotated(g_rotAng[1], 0, 1, 0);
	glRotated(g_rotAng[2], 0, 0, 1);

	glBegin(GL_TRIANGLES);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 3; j++)
		{
			glNormal3dv(g_vP[g_tP[i][j]]);
			glVertex3dv(g_vP[g_tP[i][j]]);
		}
	}
	glEnd();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 400.0, w / 400.0, -h / 400.0, h / 400.0, -3, 3);
}

void keyin(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'x': g_rotAng[0] += 1.0; glutPostRedisplay(); break;
		case 'X': g_rotAng[0] -= 1.0; glutPostRedisplay(); break;
		case 'y': g_rotAng[1] += 1.0; glutPostRedisplay(); break;
		case 'Y': g_rotAng[1] -= 1.0; glutPostRedisplay(); break;
		case 'z': g_rotAng[2] += 1.0; glutPostRedisplay(); break;
		case 'Z': g_rotAng[2] -= 1.0; glutPostRedisplay(); break;
		case '\033': exit(0);
		default: break;
	}
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutKeyboardFunc(keyin);
	glutMainLoop();

	return 0;
}

