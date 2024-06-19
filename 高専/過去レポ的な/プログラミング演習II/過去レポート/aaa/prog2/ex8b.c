#include<GL/glut.h>
#include<math.h>

void display(){

	int i,j;
	GLdouble p[6][3];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glColor3d(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(0,1,0);
	glColor3d(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1);
	glEnd();
	
	glColor3d(1,1,1);
	p[0][0] = p[0][2] = p[1][0] = p[1][2] = p[2][1] = p[2][2] = p[3][0] = p[3][1] = p[4][1] = p[4][2] = p[5][0] =p[5][1] =  0.0;
	p[1][1] = p[3][2] = p[4][0] = 1;
	p[0][1] = p[2][0] = p[5][2] = -1;
	glBegin(GL_LINE_LOOP);
	for(i=2;i<6;i++){
			glVertex3dv(p[i]);

	}
	glEnd();
	glBegin(GL_LINES);
	for(i=0;i<2;i++){
		for(j=2;j<6;j++){
				glVertex3dv(p[i]);
				glVertex3dv(p[j]);
		}
	}
	glEnd();
	glFlush();

}

void init(){

	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);

}

void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3,3,-3,3,-3,3);

}


int main(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;

}
