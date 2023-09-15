#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 8.0

void display() { /* 描画命令 */
  static double rotAng = 0.0;
  int i, j;
  double theta, dt, x, y;

  // 図形の表示
  theta = rotAng;
  glBegin(GL_PROJECTION);

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(cos(theta), -sin(theta), 0);
  glColor3d(0, 1, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(sin(theta), cos(theta), 0);
  glColor3d(0, 0, 1);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, 1);

  glEnd();
  glFlush();
  rotAng += 3.0 * M_PI / 180;

  glFlush();
}

void resize(int w, int h) {
  double wd, hd;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2, 2, -2, 2, -2, 2);
}

static void timer(int dummy) { /*タイマコールバック関数*/
  glutTimerFunc(100, timer, 0);
  glutPostRedisplay();
}

void idle() { /*コールバック関数*/

  glutPostRedisplay();
}

void init() { /* 初期化命令 */

  glClearColor(0.0, 0.0, 0.0, 1.0);
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