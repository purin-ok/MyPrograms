#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 4

GLdouble field_ans[NUM][NUM][3] = {0.0};
GLdouble field_col[NUM][NUM][3] = {0.0};

// WindowID
int WindowID[MaxWindowNum];

void display1() { /* お手本画面の描画命令 */
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  field_ans[2][1][0] = 1.0;
  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_ans[i][j]);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
    }
  }
  glEnd();
  glFlush();
}

void display2() { /* 操作画面の描画命令 */
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  field_col[2][2
  ][1] = 1.0;
  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_col[i][j]);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
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
  wd = (double)w;
  hd = (double)h;
  (w < h) ? gluOrtho2D(-wd / wd, wd / wd, -hd / wd, hd / wd)
          : gluOrtho2D(-wd / hd, wd / hd, -hd / hd, hd / hd);
}

void init() { /* 初期化命令 */
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  // お手本画面
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  WindowID[1] = glutCreateWindow("お手本画面");
  glutDisplayFunc(display1);
  init();

  // 操作画面
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(655, 0);
  WindowID[2] = glutCreateWindow("2nd Window");
  glutDisplayFunc(display2);
  glutReshapeFunc(resize);
  init();

  glutMainLoop();

  return 0;
}