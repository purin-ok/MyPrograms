#include<GL/glut.h>
#include<stdio.h>


#define ID_B 1
#define ID_L 2
#define ID_U 3

#define RADIUS_B 0.5
#define HEIGHT_B 0.3
#define WIDTH_L 0.2
#define HEIGHT_L 0.8
#define WIDHT_U 0.2
#define HEIGHT_U 0.5

typedef struct materialStruct{
  GLfloat ambient[4],diffuse[4],speculer[4];
  GLfloat shininess;
}materialStruct;

materialStruct brassMaterials={
  {0.33,0.22,0.03,1},{0.78,0.57,0.11,1},{0.99,0.91,0.81,1},27.8
};
materialStruct redPlasticMaterials={
  {0.3,0.0,0.0,1},{0.6,0.0,0.0,1},{0.8,0.6,0.6,1},32.0
};
materialStruct greenPrasticMaterials={
  {0.0,0.3,0.0,1},{0.0,0.6,0.0,1},{0.6,0.8,0.6,1},32.0
};

GLUquadric *myQuad;

GLfloat lP1[] = { 0.0,1.0,2.0,1.0 };
GLfloat lC1[] = { 1.0,1.0,1.0,1.0 };

void materials(materialStruct *m)
{
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m->ambient);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m->diffuse);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m->speculer);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m->shininess);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(1.0,1.0,1.0, 0.0,0.5,0.0, 0.0,1.0,0.0);

  glCallList(ID_B);
  glTranslatef(0.0,HEIGHT_B,0.0);

  glCallList(ID_L);
  glTranslatef(0.0,HEIGHT_L,0.0);

  glCallList(ID_U);

  glutSwapBuffers();
  }

  void resize(int w,int h)
  {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0,2.0, -2.0,2.0, -4.0,4.0);
  }

  static void timer(int dummy)
  {
  	glutTimerFunc(100, timer, 0);
  	glutPostRedisplay();
  }

void init(void)
{
  glClearColor(0.0,0.0,0.0,0.0);
  myQuad=gluNewQuadric();
  gluQuadricDrawStyle(myQuad,GLU_FILL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT1, GL_POSITION, lP1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lC1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lC1);
  glEnable(GL_LIGHT1);

  glNewList(ID_B,GL_COMPILE);
  glPushMatrix();
  glRotatef(-90.0,1.0,0.0,0.0);
  materials(&brassMaterials);
  gluCylinder(myQuad,RADIUS_B,WIDTH_L,HEIGHT_B,12,5);
  glPopMatrix();
  glEndList();

  glNewList(ID_L,GL_COMPILE);
  glPushMatrix();
  glRotatef(-90.0,1.0,0.0,0.0);
  materials(&redPlasticMaterials);
  gluCylinder(myQuad,WIDTH_L,WIDTH_L,HEIGHT_L,12,5);
  glPopMatrix();
  glEndList();

  glNewList(ID_U,GL_COMPILE);
  glPushMatrix();
  glRotatef(-90.0,1.0,0.0,0.0);
  materials(&greenPrasticMaterials);
  gluCylinder(myQuad,WIDHT_U,0.0,HEIGHT_U,12,5);
  glPopMatrix();
  glEndList();
}

int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(512,512);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutTimerFunc(100, timer, 0);
  init();
  glutMainLoop();

  return 0;
}
