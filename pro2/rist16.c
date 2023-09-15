/*
  演習12
*/

#include <GL/glut.h>
#include <math.h>
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

  glutWireTetrahedron();

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

static void timer(int dummy) { /*タイマコールバック関数*/
  glutTimerFunc(100, timer, 0);
  glMatrixMode(GL_MODELVIEW);
  glRotated(3.0, 0.0, 0.0, 1.0);
  glutPostRedisplay();
}

void idle() { /*コールバック関数*/

  glutPostRedisplay();
}

void init() { /* 初期化命令 */
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void keyin(unsigned char key, int x, int y) {
  switch (key) {
    case '\033':
    case 'q':
    case 'Q':
      exit(0);

    default:
      break;
  }
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
  glutKeyboardFunc(keyin);

  init();
  glutMainLoop();

  return 0;
}