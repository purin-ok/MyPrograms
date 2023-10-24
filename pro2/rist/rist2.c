#include <GL/glut.h>

void display() { /* 描画命令 */ }

void init() { /* 初期化命令 */ }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}