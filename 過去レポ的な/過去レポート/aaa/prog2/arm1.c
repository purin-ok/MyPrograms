#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define ID_B 1
#define ID_L 2
#define ID_U 3

#define HEIGHT_B 1.0
#define WIDTH_B 3.0

#define HEIGHT_L 3.0
#define WIDTH_L 1.0

#define HEIGHT_U 2.0
#define WIDTH_U 1.0

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -2.0, 8.0, -10.0, 10.0);
}

void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(1, -1, -1, 0, 1, 1, 0, 0, 1);

	glNewList(ID_B, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.5 * HEIGHT_B, 0.0);
	glScalef(WIDTH_B, HEIGHT_B, WIDTH_B);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();

	glNewList(ID_L, GL_COMPILE);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.5 * HEIGHT_L, 0.0);
	glScalef(WIDTH_L, HEIGHT_L, WIDTH_L);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();

	glNewList(ID_U, GL_COMPILE);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.5 * HEIGHT_U, 0.0);
	glScalef(WIDTH_U, HEIGHT_U, WIDTH_U);
	glutWireCube(1.0);
	glPopMatrix();
	glEndList();
}

static void timer(int dummy) {
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

//stat 0:í‚é~Å@1;âÒì]Å@-1:ãtâÒì]Å@
GLfloat rotAng[3];
int b_stat = 0, l_stat = 0, u_stat = 0, pause = 0;

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 1.5, 0, 0, 0, 0, 1, 0);
	glRotated(rotAng[0], 0, 1, 0);

	glRotated(rotAng[0], 0, 1, 0);
	glCallList(ID_B);

	//ë‰ç¿
	if (pause == 0) {
		if (b_stat == 1) rotAng[0] += 3.0;
		if (b_stat == -1) rotAng[0] -= 3.0;
	}

	//â∫òr
	glTranslated(0, HEIGHT_B, 0);
	glRotated(rotAng[1], 0, 0, 1);
	glCallList(ID_L);

	if (pause == 0) {
		if (l_stat == 1) rotAng[1] += 3.0;
		if (l_stat == -1) rotAng[1] -= 3.0;
	}
	
	//è„òr
	glTranslated(0, HEIGHT_L, 0);
	glRotated(rotAng[2], 0, 0, 1);
	glCallList(ID_U);

	if (pause == 0) {
		if (u_stat == 1) rotAng[2] += 3.0;
		if (u_stat == -1) rotAng[2] -= 3.0;
	}

	glutSwapBuffers();

}

void keyin(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':exit(0); break;
	case 'w':b_stat = 1;; break;
	case 'e':b_stat = -1; break;
	case 'r':b_stat = 0; break;
	case 's':l_stat = 1; break;
	case 'd':l_stat = -1; break;
	case 'f':l_stat = 0; break;
	case 'x':u_stat = 1; break;
	case 'c':u_stat = -1; break;
	case 'v':u_stat = 0; break;
	case 'z': {dance = !dance; b_stat = 0;
		l_stat = 0; u_stat = 0; break;
	}
	case 'p':pause = !pause; break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100, timer, 0);
	init();
	glutKeyboardFunc(keyin);
	glutMainLoop();
	return 0;
}
