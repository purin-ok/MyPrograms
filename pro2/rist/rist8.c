#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 4.0
void display() { /* 描画命令 */
  int i;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);

  // n角形の表示,n=3
  dt = 2.0 * M_PI / NUM;  // 定義されてます
  theta = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i < NUM; i++) {
    x = cos(theta);
    y = sin(theta);
    glVertex2d(x, y);
    theta += dt;
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

  glClearColor(0.0, 0.0, 1.0, 1.0);
}

void idle() {
  int a;
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(idle);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();

  return 0;
}