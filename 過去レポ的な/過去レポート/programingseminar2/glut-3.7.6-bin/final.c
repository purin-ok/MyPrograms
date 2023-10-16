#include <GL/glut.h>
#include <math.h>
#define NUM 3 //点電荷の数
#define MOVABLE 3//動ける点電荷の数
#define COULOMB 9.0*0.000000001//クーロン定数
#define RATE 10//リフレッシュレート

int isAnime=1;
double x[NUM]={1,-1,0}
	,y[NUM]={0,0,1}
	,z[NUM]={0,0,0}
	,q[NUM]={-1.602*10000,-1.602*10000,1.602*2000 }
	,m[NUM]={1,1,1}
	,vx[MOVABLE]={0},vy[MOVABLE]={0},vz[MOVABLE]={0}
	,ax[MOVABLE],ay[MOVABLE],az[MOVABLE];

double dist(int i,int j){
	return sqrt((x[j]-x[i])*(x[j]-x[i])+(y[j]-y[i])*(y[j]-y[i])+(z[j]-z[i])*(z[j]-z[i]));
}


void display(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_LINES);
	glColor3d(1,0,0);
	glVertex3d(-0.3,0,0);
	glVertex3d(1,0,0);
	glColor3d(0,1,0);
	glVertex3d(0,-0.3,0);
	glVertex3d(0,1,0);
	glColor3d(0,0,1);
	glVertex3d(0,0,-0.3);
	glVertex3d(0,0,1);
	glEnd();

	glLoadIdentity();
	for(j=0;j<MOVABLE;j++){
		for(i=0;i<NUM;i++){
			if (i==j) continue;
			ax[j]=COULOMB*q[j]*q[i]*(x[j]-x[i])/(dist(j,i)*dist(j,i)*dist(j,i)*m[j]);
			ay[j]=COULOMB*q[j]*q[i]*(y[j]-y[i])/(dist(j,i)*dist(j,i)*dist(j,i)*m[j]);
			az[j]=COULOMB*q[j]*q[i]*(z[j]-z[i])/(dist(j,i)*dist(j,i)*dist(j,i)*m[j]);
			vx[j]+=ax[j]*RATE/1000.0;
			vy[j]+=ay[j]*RATE/1000.0;
			vz[j]+=az[j]*RATE/1000.0;
			x[j]+=vx[j]*RATE/1000.0;
			y[j]+=vy[j]*RATE/1000.0;
			z[j]+=vz[j]*RATE/1000.0;
		}
	}
	
	gluLookAt(1,1,1,0,0,0,0,1,0);
	for(i=0;i<NUM;i++){
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glColor3f(q[i]>0,0,q[i]<0);
		glTranslated(x[i],y[i],z[i]);
		glutWireSphere(0.1,10,10);
		glPopMatrix();
	}
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
	glOrtho(-4,4,-4,4,-4,4);
}

static void timer(int dummy){
	glutTimerFunc(RATE,timer,0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}


int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(1280,960);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutTimerFunc(100,timer,0);
	init();
	glutMainLoop();
	return 0;
}

