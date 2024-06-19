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

typedef struct materialStruct
{
	GLfloat ambient[4], diffuse[4], specular[4];
	GLfloat shininess;
} materialStruct;

void materials(materialStruct *m);
void display(void);
void resize(int w, int h);
void keyin(unsigned char key, int x, int y);
void init(void);

materialStruct g_brassMaterials = {
	{ 0.33, 0.22, 0.03, 1 }, { 0.78, 0.57, 0.11, 1 }, { 0.99, 0.91, 0.81, 1 }, 27.8
};
materialStruct g_redPlasticMaterials = {
	{ 0.3, 0.0, 0.0, 1 }, { 0.6, 0.0, 0.0, 1 }, { 0.8, 0.6, 0.6, 1 }, 32.0
};
materialStruct g_greenPlasticMaterials = {
	{ 0.0, 0.3, 0.0, 1 }, { 0.0, 0.6, 0.0, 1 }, { 0.6, 0.8, 0.6, 1 }, 32.0
};
GLUquadric *g_quad;
GLfloat g_rotAng[3] = {0.0};

void materials(materialStruct *m)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);

	glRotated(g_rotAng[0], 0, 1, 0);
	glCallList(ID_B);

	glTranslatef(0.0, HEIGHT_B, 0.0);
	glRotated(g_rotAng[1], 0, 0, 1);
	glCallList(ID_L);

	glTranslatef(0.0, HEIGHT_L, 0.0);
	glRotated(g_rotAng[2], 0, 0, 1);
	glCallList(ID_U);

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
	GLfloat IP1[4] = {0.0, 1.0, 2.0, 1.0};
	GLfloat IC1[4] = {1.0, 1.0, 0.0, 1.0};

	glClearColor(1.0, 1.0, 1.0, 1.0);
	g_quad = gluNewQuadric();
	gluQuadricDrawStyle(g_quad, GLU_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glNewList(ID_B, GL_COMPILE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	materials(&g_brassMaterials);
	gluCylinder(g_quad, RADIUS_B, WIDTH_L, HEIGHT_B, 12, 5);
	glPopMatrix();
	glEndList();

	glNewList(ID_L, GL_COMPILE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	materials(&g_redPlasticMaterials);
	gluCylinder(g_quad, WIDTH_L, WIDTH_L, HEIGHT_L, 12, 5);
	glPopMatrix();
	glEndList();

	glNewList(ID_U, GL_COMPILE);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	materials(&g_greenPlasticMaterials);
	gluCylinder(g_quad, WIDTH_U, 0.0, HEIGHT_U, 12, 5);
	glPopMatrix();
	glEndList();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutKeyboardFunc(keyin);
	glutMainLoop();

	return 0;
}
