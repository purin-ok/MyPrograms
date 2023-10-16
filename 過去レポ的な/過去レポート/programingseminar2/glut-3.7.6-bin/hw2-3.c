#include <GL/glut.h>

#define ID_B 1
#define ID_L 2
#define ID_U 3
#define RADIUS_B 0.5
#define HEIGHT_B 0.3
#define WIDTH_L 0.2
#define HEIGHT_L 0.8
#define WIDTH_U 0.2
#define HEIGHT_U 0.5

GLfloat g_rotAng[3] = {0.0};
GLUquadric *g_quad;

void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(void);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

	glRotated(g_rotAng[0], 0, 1, 0);
	glCallList(ID_B);

	glTranslated(0, HEIGHT_B, 0);
	glRotated(g_rotAng[1], 0, 0, 1);
	glCallList(ID_L);

	glTranslated(0, HEIGHT_L, 0);
	glRotated(g_rotAng[2], 0, 0, 1);
	glCallList(ID_U);

	glutSwapBuffers();

	//glFlush();
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
	switch (key)
	{
		case 'b': g_rotAng[0] += 1.0; glutPostRedisplay(); break;
		case 'B': g_rotAng[0] -= 1.0; glutPostRedisplay(); break;
		case 'l': g_rotAng[1] += 1.0; glutPostRedisplay(); break;
		case 'L': g_rotAng[1] -= 1.0; glutPostRedisplay(); break;
		case 'u': g_rotAng[2] += 1.0; glutPostRedisplay(); break;
		case 'U': g_rotAng[2] -= 1.0; glutPostRedisplay(); break;
		case '\033': exit(0);
		default: break;
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	g_quad = gluNewQuadric();
	gluQuadricDrawStyle(g_quad, GLU_LINE);

	glNewList(ID_B, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, HEIGHT_B, 0.0);
	glScalef(RADIUS_B, HEIGHT_B, RADIUS_B);
	glRotatef(90, 1, 0, 0);
	gluCylinder(g_quad, 1, 1, 1, 12, 6);
	glPopMatrix();
	glEndList();

	glNewList(ID_L, GL_COMPILE);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEIGHT_L, 0.0);
	glScalef(WIDTH_L, HEIGHT_L, WIDTH_L);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();

	glNewList(ID_U, GL_COMPILE);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEIGHT_U, 0.0);
	glScalef(WIDTH_U, HEIGHT_U, WIDTH_U);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyin);

	init();
	glutMainLoop();

	return 0;
}
