/*
  演習13
  なんかバグってる．別の方法試したほうがいいかも
*/

#include <GL/glut.h>
#include <math.h>

char axis;
int isAnime = 1;

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
      axis = 'x';
      break;

    case 'y':
    case 'Y':
      axis = 'y';
      break;

    case 'z':
    case 'Z':
      axis = 'z';
      break;

    default:
      break;
  }
}

void mouse(int btn, int state, int x, int y) {
  if (btn == GLUT_LEFT_BUTTON) {
    isAnime = 0;
  } else if (btn == GLUT_RIGHT_BUTTON) {
    isAnime = 1;
  }
}

static void timer(int dummy) { /*タイマコールバック関数*/

  if (isAnime == 1) {  // isAnime==1と同じ意味
    glutTimerFunc(100, timer, 0);
  } else if (isAnime == 0) {
    glutTimerFunc(100, NULL, 0);
  }
  glMatrixMode(GL_MODELVIEW);
  if (axis == 'x') {
    glRotated(3.0, 1.0, 0.0, 0.0);
  } else if (axis == 'y') {
    glRotated(3.0, 0.0, 1.0, 0.0);
  } else if (axis == 'z') {
    glRotated(3.0, 0.0, 0.0, 1.0);
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(idle);
  if (isAnime == 1) {  // isAnime==1と同じ意味
    glutTimerFunc(100, timer, 0);
  } else if (isAnime == 0) {
    glutTimerFunc(100, NULL, 0);
  }

  glutReshapeFunc(resize);
  glutKeyboardFunc(keyin);
  glutMouseFunc(mouse);

  init();
  glutMainLoop();

  return 0;
}