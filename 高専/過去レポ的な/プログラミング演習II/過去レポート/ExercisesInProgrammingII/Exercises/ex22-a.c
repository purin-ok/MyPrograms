#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "vect.h"

void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(void);

GLdouble vP[4][3]={
	{ 1.000,  0.000,  0.000},
	{-0.333,  0.943,  0.000},
	{-0.333, -0.471, -0.816},
	{-0.333, -0.471,  0.816}
};
int tP[4][3]={
	{0, 2, 1}, {0, 1, 3}, {0, 3, 2}, {1, 2, 3}
};
GLdouble nV[4][3];
GLfloat g_rotAng[3] = {0.0};

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
	for (i = 0; i < 4; i++)
	{
		glNormal3dv(nV[i]);
		for (j = 0; j < 3; j++)
		{
			glVertex3dv(vP[tP[i][j]]);
		}
	}
	glEnd();

	glFlush();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -3, 3);
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
	GLdouble n;
	GLdouble v1[3], v2[3];
	GLdouble tmp[3];
	int i;
	//GLfloat IP1[4] = {0.0, 1.0, 2.0, 1.0};
	//GLfloat IC1[4] = {1.0, 1.0, 0.0, 1.0};

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT1, GL_POSITION, IP1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, IP1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, IP1);
	//glEnable(GL_LIGHT1);

	for (i = 0; i < 4; i++)
	{
		vect_sub(vP[tP[i][1]], vP[tP[i][0]], v1);
		vect_sub(vP[tP[i][2]], vP[tP[i][0]], v2);
		vect_outerproduct(v1, v2, tmp);
		n = vect_norm(tmp);
		vect_scale(1.0 / n, tmp, nV[i]);
	}
	printf("(%f, %f, %f)\n", nV[0][0], nV[0][1], nV[0][2]);
	printf("(%f, %f, %f)\n", nV[1][0], nV[1][1], nV[1][2]);
	printf("(%f, %f, %f)\n", nV[2][0], nV[2][1], nV[2][2]);
	printf("(%f, %f, %f)\n", nV[3][0], nV[3][1], nV[3][2]);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutKeyboardFunc(keyin);
	glutMainLoop();

	return 0;
}
