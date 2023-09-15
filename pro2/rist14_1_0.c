#include <GL/glut.h>
#include <math.h>
void display() { /* 描画命令 */
  int i, j;
  GLdouble p[4][3];
  p[0][0] = 1.0;
  p[0][1] = p[0][2] = p[1][2] = 0.0;
  p[1][0] = p[2][0] = p[3][0] = -1.0 / 3;
  p[2][1] = p[3][1] = -sqrt(2.0) / 3;
  p[1][1] = -2.0 * p[2][1];
  p[2][2] = sqrt(6.0) / 3.0;
  p[3][2] = -p[2][2];

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

  for (i = 0; i < 3; i++) {
    for (j = i + 1; j < 4; j++) {
      glVertex3dv(p[i]);
      glVertex3dv(p[j]);
    }
  }
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
  // gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
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