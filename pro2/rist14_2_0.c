#include <GL/glut.h>
#include <math.h>

GLUquadric* myQuad;

void display() { /* 描画命令 */
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(1, 0, 0);
  glColor3d(0, 1, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 1, 0);
  glColor3d(0, 0, 1);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, 1);
  glEnd();

  glColor3d(0, 1, 1);

  glBegin(GL_LINES);

  gluSphere(myQuad, 1.0, 100, 100);

  glEnd();
  glFlush();
}

void resize(int w, int h) {
  double wd, hd;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-2, 2, -2, 2, -2, 2);
}

void init() { /* 初期化命令 */
  glClearColor(0.0, 0.0, 0.0, 1.0);

  myQuad = gluNewQuadric();
  gluQuadricDrawStyle(myQuad, GLU_LINE);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();

  return 0;
}