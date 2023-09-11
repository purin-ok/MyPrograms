#include <GL/glut.h>

void display() { /* 描画命令 */

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  glBegin(GL_LINE_STRIP);
  glVertex2d(0, 1);
  glVertex2d(0, 0);
  glVertex2d(1, 0);
  glEnd();
  glColor3d(0.0, 1.0, 0.0);
  glRasterPos2d(0, 0);
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
  glFlush();
}

void init() { /* 初期化命令 */

  glClearColor(0.0, 0.0, 1.0, 1.0);
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