#include<stdlib.h>
#include <GL/glut.h>
#include <math.h>

double rotAng=0,zoom=2.0;
int selectedaxis=2;

void display(void){
	int i,j,axis1=0,axis2=1;
	double tmp1,tmp2;
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLdouble p[4][3];
	p[0][0]=1.0;
	p[0][1]=p[0][2]=p[1][2]=0.0;
	p[1][0]=p[2][0]=p[3][0]=-1.0/3.0;
	p[2][1]=p[3][1]=-sqrt(2.0)/3;
	p[1][1]=-2.0*p[2][1];
	p[2][2]=sqrt(6.0)/3.0;
	p[3][2]=-p[2][2];
	
	if (selectedaxis==0){
		axis1=1;
		axis2=2;
	}
	if (selectedaxis==1){
		axis1=2;
		axis2=0;
	}
	for (i=0;i<4;i++){
		tmp1=p[i][axis1];
		tmp2=p[i][axis2];
		p[i][axis1]=tmp1*cos(rotAng)+tmp2*sin(rotAng);
		p[i][axis2]=-tmp1*sin(rotAng)+tmp2*cos(rotAng);
	}
	
	rotAng+=3.0*M_PI/180.0;
	
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
	
	for(i=0;i<3;i++){
		for(j=i+1;j<4;j++){
			glVertex3dv(p[i]);
			glVertex3dv(p[j]);
		}
	}
	glEnd();
	glutSwapBuffers();
}

void init(void){
	glClearColor(0.0,0.0,0.0,1.0);
	gluLookAt(1,1,1,0,0,0,0,1,0);
}

void resize(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-zoom,zoom,-zoom,zoom,-zoom,zoom);
}

static void timer(int dummy){
	glutTimerFunc(100,timer,0);
	glutPostRedisplay();
}

void keyin(unsigned char key,int x,int y){
	switch(key){
		case '\033':
		case 'q':
		case'Q':
			exit(0);
		case 'x':
		case 'X':
			selectedaxis=0;
			break;
		case 'y':
		case 'Y':
			selectedaxis=1;
			break;
		case 'z':
		case 'Z':
			selectedaxis=2;
			break;
		case 'i':
		case 'I':
			zoom+=0.1;
			resize(2000,1000);
			break;
		case 'o':
		case 'O':
			zoom-=0.1;
			resize(2000,1000);
			break;
		
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
	glutKeyboardFunc(keyin);
	glutTimerFunc(100,timer,0);
	init();
	glutMainLoop();
	return 0;
}

