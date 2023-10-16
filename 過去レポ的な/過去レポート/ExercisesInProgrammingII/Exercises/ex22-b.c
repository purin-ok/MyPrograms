#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include "vect.h"

void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void mouse(int btn, int state, int x, int y);
void init(void);

GLdouble vP[8][3]={
	{-0.577, -0.577,  0.577},
	{ 0.577, -0.577,  0.577},
	{ 0.577, -0.577, -0.577},
	{-0.577, -0.577, -0.577},
	{-0.577,  0.577,  0.577},
	{ 0.577,  0.577,  0.577},
	{ 0.577,  0.577, -0.577},
	{-0.577,  0.577, -0.577},
};
int tP[6][4]={
	{3, 2, 1, 0}, {0, 1, 5, 4}, {1, 2, 6, 5},
	{4, 5, 6, 7}, {3, 7, 6, 2}, {0, 4, 7, 3}
};
GLdouble nV[6][3];

void display(void)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++)
	{
		glNormal3dv(nV[i]);
		for (j = 0; j < 4; j++)
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
		case 'x': glRotated(1, 1, 0, 0);glutPostRedisplay();break;
		case 'X': glRotated(1, -1, 0, 0);glutPostRedisplay();break;
		case 'y': glRotated(1, 0, 1, 0);glutPostRedisplay();break;
		case 'Y': glRotated(1, 0, -1, 0);glutPostRedisplay();break;
		case 'z': glRotated(1, 0, 0, 1);glutPostRedisplay();break;
		case 'Z': glRotated(1, 0, 0, -1);glutPostRedisplay();break;
		//case 'l': glOrtho(-2, 2, -2, 2, -3, 3);glutPostRedisplay();break;
		//case 'u': glOrtho(-0.5, 0.5, -0.5, 0.5, -3, 3);glutPostRedisplay();break;
		case '\033': exit(0);
		default: break;
	}
}

void mouse(int btn, int state, int x, int y)
{
	if(btn == GLUT_LEFT_BUTTON)
	{
		//rS *= 1.25;
	}
	if(btn == GLUT_RIGHT_BUTTON)
	{
		//rS /= 1.25;
	}
}

void init(void)
{
	GLdouble n;
	GLdouble v1[3], v2[3];
	GLdouble tmp[3];
	int i;
	GLfloat IP1[4] = {0.0, 1.0, 2.0, 1.0};
	GLfloat IC1[4] = {1.0, 1.0, 0.0, 1.0};

	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_POSITION, IP1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, IP1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, IP1);
	glEnable(GL_LIGHT1);

	for (i = 0; i < 6; i++)
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
	printf("(%f, %f, %f)\n", nV[4][0], nV[4][1], nV[4][2]);
	printf("(%f, %f, %f)\n", nV[5][0], nV[5][1], nV[5][2]);
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
	//glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
