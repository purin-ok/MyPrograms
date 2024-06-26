#include <GL/glut.h>
#include <math.h>

int isAnime=0;

GLdouble vP[4][3]={{1.0,0.0,0.0},{-0.333,0.943,0.0},{-0.333,-0.471,0.816},{-0.333,-0.471,-0.816}};
int tP[4][3]={{0,1,2},{0,3,1},{0,2,3},{1,3,2}};


void display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			glVertex3dv(vP[tP[i][j]]);
			glNormal3dv(vP[tP[i][j]]);
		}
	}
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();

}

void init(void){
	glClearColor(1.0,1.0,1.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3,3,-3,3,-3,3);
}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glMatrixMode(GL_MODELVIEW);
	if (isAnime==1) glRotated(3.0,0.0,0.0,1.0);
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y){
	if((btn==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)) {
		if (isAnime==0) isAnime=1;
			else isAnime=0;
	}
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
		case 'l': glOrtho(-2, 2, -2, 2, -3, 3);glutPostRedisplay();break;
		case 'u': glOrtho(-0.5, 0.5, -0.5, 0.5, -3, 3);glutPostRedisplay();break;
		case '\033': exit(0);
		default: break;
	}
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(700,300);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100,timer,0);
//	glutMouseFunc(mouse);
	glutKeyboardFunc(keyin);
	init();
	glutMainLoop();
	return 0;
}

