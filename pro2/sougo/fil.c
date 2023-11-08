#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 4

GLdouble field[NUM + 1][NUM + 1];
GLdouble field_col[NUM][NUM][3] = {0};

void display() { /* 描画命令 */
  int i, j;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(0.0, 0.0, 0.0);

  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_col[i][j]);
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

  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();

  return 0;
}