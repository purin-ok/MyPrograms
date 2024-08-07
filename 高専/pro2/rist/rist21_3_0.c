#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 3.0
void display() { /* 描画命令 */
  int i;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);


  // n角形の表示,n=3
  dt = 2.0 * M_PI / NUM;  // 定義されてます
  theta = 0.0;
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0);
    x = cos(theta);
    y = sin(theta);
    glVertex2d(x, y);
    theta += dt;
  glColor3d(0.0, 1.0, 0.0);
    x = cos(theta);
    y = sin(theta);
    glVertex2d(x, y);
    theta += dt;
  glColor3d(0.0, 0.0, 1.0);
    x = cos(theta);
    y = sin(theta);
    glVertex2d(x, y);
    theta += dt;

  glEnd();
  glFlush();
}

void init() { /* 初期化命令 */

  glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();

  return 0;
}