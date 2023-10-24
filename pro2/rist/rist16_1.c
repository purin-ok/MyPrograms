/*
  演習13
  なんかバグってる．別の方法試したほうがいいかも
*/

#include <GL/glut.h>
#include <math.h>

double axisX = 0.0, axisY = 0.0, axisZ = 1.0;

void display() { /* 描画命令 */

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
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2, 2, -2, 2, -2, 2);
}

static void timer(int dummy) { /*タイマコールバック関数*/
  glutTimerFunc(100, timer, 0);
  glMatrixMode(GL_MODELVIEW);
  glRotated(3.0, axisX, axisY, axisZ);
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

    case 'x':
    case 'X':
      axisX = 1.0;
      axisY = 0.0;
      axisZ = 0.0;
      break;

    case 'y':
    case 'Y':
      axisX = 0.0;
      axisY = 1.0;
      axisZ = 0.0;
      break;

    case 'z':
    case 'Z':
      axisX = 0.0;
      axisY = 0.0;
      axisZ = 1.0;
      break;

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