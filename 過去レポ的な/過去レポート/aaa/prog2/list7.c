#include<GL/glut.h>
#include<math.h>

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(0,1);
	glVertex2d(0,0);
	glVertex2d(1,0);
	glEnd();
	glColor3d(1.0,1.0,0.0);
	glRasterPos2d(0,0);
	glutBitmapCharacter(
		GLUT_BITMAP_8_BY_13,'9'
	);
	glFlush();	

}

void init(){

	glClearColor(0.0,0.0,0.0,1.0);

}
void resize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(
		-w/200.0,w/200.0,
		-h/200.0,h/200.0
	);
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
