#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define ID_B 1
#define ID_L 2
#define ID_U 3

#define HEIGHT_B 0.8
#define WIDTH_B 3.0

#define HEIGHT_L 3.5
#define WIDTH_L 1.0

#define HEIGHT_U 2.5
#define WIDTH_U 1.0

GLfloat rotAng[3];
int b_stat=0,l_stat=0,u_stat=0,pause=0,dance=0;

typedef struct materialStruct{
  GLfloat ambient[4],diffuse[4],
          speculer[4];
  GLfloat shininess;
}materialStruct;

materialStruct brassMaterials={
  {0.33,0.22,0.03,1},
  {0.78,0.57,0.11,1},
  {0.99,0.91,0.81,1},
  27.8
};
materialStruct redPlasticMaterials={
  {0.3,0.0,0.0,1},
  {0.6,0.0,0.0,1},
  {0.8,0.6,0.6,1},
  32.0
};
materialStruct greenPlasticMaterials={
  {0.0,0.3,0.0,1},
  {0.0,0.6,0.0,1},
  {0.6,0.8,0.6,1},
  32.0
};
GLUquadric *myQuad;

GLfloat lP1[] = { 0.0,1.0,2.0,1.0 };
GLfloat lC1[] = { 1.0,1.0,1.0,1.0 };

void materials(materialStruct *m)
{
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_AMBIENT,
               m->ambient);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE,
               m->diffuse);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR,
               m->speculer);
  glMaterialf(GL_FRONT_AND_BACK,
              GL_SHININESS,
              m->shininess);
}

void init(void) {
	myQuad = gluNewQuadric();
	gluQuadricDrawStyle(myQuad, GLU_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_POSITION, lP1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lC1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lC1);
	glEnable(GL_LIGHT1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluLookAt(1,-1,-1, 0,1,1, 0,0,1);
//台座
	glNewList(ID_B, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEIGHT_L, 0.0);
	glScalef(WIDTH_B, HEIGHT_B, WIDTH_B);
	glRotated(90, 1.0, 0, 0);
	materials(&brassMaterials);
	gluCylinder(myQuad,1,1,2,10,5);
	glPopMatrix();
	glEndList();
//下腕
	glNewList(ID_L, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEIGHT_L, 0.0);
	glScalef(WIDTH_L, HEIGHT_L, WIDTH_L);
	materials(&redPlasticMaterials);
	glutSolidCube(1.0);
	glPopMatrix();
	glEndList();
//上腕
	glNewList(ID_U, GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.0, 0.5*HEIGHT_L, 0.0);
	glScalef(WIDTH_U, HEIGHT_U, WIDTH_U);
	materials(&greenPlasticMaterials);
	glutSolidCube(1.0);
	glPopMatrix();
	glEndList();
}

void resize(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-6.0,6.0, -3.0,9.0, -6.0,6.0);
}

static void timer(int dummy)
{
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();

}

void Dance()
{
	int i;

  if(pause==0){
    for(i=0;i<3;i++){
	     srand((unsigned)time(NULL));
       rotAng[i] += rand()%18;
  	}
	}
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	gluLookAt(1,1,1.5, 0,0,0, 0,1,0);

  glRotated(rotAng[0],0,1,0);
  glCallList(ID_B);
	glTranslated(0,HEIGHT_B,0);

	if(pause==0){
		if(b_stat==1) rotAng[0]+=3.0;
		if(b_stat==-1) rotAng[0]-=3.0;
	}/*台座の回転角の制御*/

  glRotated(rotAng[1],0,0,1);
  glCallList(ID_L);
  glTranslated(0,HEIGHT_L,0);

	if(pause==0){
		if(l_stat==1) rotAng[1]+=3.0;
		if(l_stat==-1) rotAng[1]-=3.0;
	}/*下腕の回転角の制御*/

  glRotated(rotAng[2],0,0,1);
  glCallList(ID_U);

	if(pause==0){
		if(u_stat==1) rotAng[2]+=3.0;
		if(u_stat==-1) rotAng[2]-=3.0;
	}/*上腕の回転角の制御*/

  if(dance==1) Dance();
  //danceフラグが成立したらランダムに回転角を制御

	glLoadIdentity();
	glutSwapBuffers();

}

void keyin(unsigned char key,int x,int y)
{
	switch (key) {
		case 'q':
		case 'Q':exit(0);break;//exit
		case 'w':b_stat=1;;break;//台座回転
		case 'e':b_stat=-1;break;//台座逆回転
		case 'r':b_stat=0;break;//台座回転停止
		case 's':l_stat=1;break;//下腕回転
		case 'd':l_stat=-1;break;//下腕逆回転
		case 'f':l_stat=0;break;//下腕回転停止
		case 'x':u_stat=1;break;//上腕回転
		case 'c':u_stat=-1;break;//上腕逆回転
		case 'v':u_stat=0;break;//上腕回転停止
		case 'z':dance=!dance;b_stat=0;l_stat=0;u_stat=0;break;//ランダムに回転
		case 'p':pause=!pause;break;//全体一時停止
	}
}


int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(512,512);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutTimerFunc(100,timer,0);
  init();
	glutKeyboardFunc(keyin);
  glutMainLoop();
  return 0;
}
