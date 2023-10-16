#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define KEY_X 1
#define KEY_Y 2
#define KEY_Z 4
#define KEY_W 8
#define KEY_S 16

char pressed = 0;
double scale = 2;

GLfloat lP1[] = {0.0,1.0,2.0,1.0};
GLfloat lC1[] = {1.0,1.0,0.0,1.0};

GLdouble vP[4][3] = {{1.000, 0.0000, 0.000},
                     {-0.333, 0.943, 0.000},
                     {-0.333, -0.471, 0.816},
                     {-0.333, -0.471, -0.816}};

GLdouble nV[4][3];
GLdouble vert_n[4][3];

int tP[4][3] = {{0, 1, 2}, {0, 3, 1}, {0, 2, 3}, {1, 3, 2}};
int reversTP[4][3] = {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}};

void cross(GLdouble v1[], GLdouble v2[], GLdouble ret[]){
    ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
    ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void vect_sum(GLdouble v1[], GLdouble v2[], GLdouble ret[]){
    int i;
    for(i=0; i<3; i++){
        ret[i] = v2[i] + v1[i];
    }
}

void vect_sub(GLdouble v1[], GLdouble v2[], GLdouble ret[]){
    int i;
    for(i=0; i<3; i++){
        ret[i] = v2[i] - v1[i];
    }
}

GLdouble vect_norm(GLdouble v[]){
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

void vect_scale(GLdouble s, GLdouble v[], GLdouble ret[]){
    int i;
    for(i=0; i<3; i++){
        ret[i] = s*v[i];
    }
}

void display(void) {
  int i, j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_TRIANGLES);
  for(i=0; i<4; i++){
      for(j=0; j<3; j++){
          glNormal3dv(vert_n[tP[i][j]]);
          glVertex3dv(vP[tP[i][j]]);
      }
  }
  glEnd();
  glutSwapBuffers();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-scale, scale, -scale, scale, -10, 10);
}

void init(void) {
  int i, j;
  GLdouble v1[3], v2[3], tmp[3];
  GLdouble n;
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluLookAt(scale, scale, scale, 0, 0, 0, 0, 1, 0);

  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT1, GL_POSITION, lP1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lC1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lC1);
  glEnable(GL_LIGHT1);

  glEnable(GL_SMOOTH);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);

  for(i=0; i<4; i++){
    vect_sub(vP[tP[i][0]], vP[tP[i][1]], v1);
    vect_sub(vP[tP[i][1]], vP[tP[i][2]], v2);
    cross(v1, v2, tmp);
    n = vect_norm(tmp);
    vect_scale(1.0/n, tmp, nV[i]);
  }
  for(i=0; i<4; i++){
    vect_sum(nV[reversTP[i][0]], nV[reversTP[i][1]], tmp);
    vect_sum(tmp, nV[reversTP[i][2]], tmp);
    n = vect_norm(tmp);
    vect_scale(1.0/n, tmp, vert_n[i]);
  }
}

static void timer(int dummy) {
  glutTimerFunc(10, timer, 0);

  if (pressed & KEY_S) {
    scale += 0.1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-scale, scale, -scale, scale, -10, 10);
    glutPostRedisplay();
    pressed = 0;
  } else if (pressed & KEY_W) {
    scale -= 0.1;
    if (scale <= 0)
      scale = 0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-scale, scale, -scale, scale, -10, 10);
    glutPostRedisplay();
    pressed = 0;
  } else if (pressed) {
    glMatrixMode(GL_MODELVIEW);
    glRotated(5.0, pressed & KEY_X, pressed & KEY_Y, pressed & KEY_Z);
    glutPostRedisplay();
    pressed = 0;
  }
}

void keyin(unsigned char key, int x, int y) {
  switch (key) {
  case 'x':
    pressed |= KEY_X;
    break;
  case 'y':
    pressed |= KEY_Y;
    break;
  case 'z':
    pressed |= KEY_Z;
    break;
  case 'w':
    pressed |= KEY_W;
    break;
  case 's':
    pressed |= KEY_S;
    break;
  case 'q':
  case 'Q':
    exit(0);
  default:
    break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyin);
  init();
  timer(0);
  glutMainLoop();
  return 0;
}

