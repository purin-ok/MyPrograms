#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 8.0

void display() { /* 描画命令 */
  static double rotAng = 0.0;
  int i;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);

  // n角形の表示,n=3
  dt = 2.0 * M_PI / NUM;  // 定義されてます
  theta = rotAng;
  glBegin(GL_POLYGON);
  for (i = 0; i < NUM; i++) {
    x = cos(theta);
    y = sin(theta);
    glVertex2d(x, y);
    theta += dt;
  }

  glEnd();
  glFlush();
  rotAng += 3.0 * M_PI / 180;
}

void resize(int w, int h) { /*リサイズ*/
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

static void timer(int dummy) { /*タイマコールバック関数*/
  glutTimerFunc(100, timer, 0);
  glutPostRedisplay();
}

void idle() { /*コールバック関数*/

  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(idle);
  glutTimerFunc(100, timer, 0);
  glutReshapeFunc(resize);

  init();
  glutMainLoop();

  return 0;
}