#include <GL/glut.h>
#include <math.h>

GLdouble vP[4][3] = {{1.000, 0.000, 0.000},
                     {-0.333, 0.943, 0.000},
                     {-0.333, -0.471, 0.816},
                     {-0.333, -0.471, -0.816}};

int tP[4][3] = {{0, 1, 2}, {0, 3, 1}, {0, 2, 3}, {1, 3, 2}};

GLdouble cP[4][3] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}};

char axis;

void display() { /*????*/
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);

  // glBegin(GL_LINES);
  // glColor3d(1, 0, 0);
  // glVertex3d(0, 0, 0);
  // glVertex3d(1, 0, 0);
  // glColor3d(0, 1, 0);
  // glVertex3d(0, 0, 0);
  // glVertex3d(0, 1, 0);
  // glColor3d(0, 0, 1);
  // glVertex3d(0, 0, 0);
  // glVertex3d(0, 0, 1);
  // glEnd();

  glBegin(GL_TRIANGLES);
  for (i = 0; i < 4; i++) {
    glColor3dv(cP[i]);
    for (j = 0; j < 3; j++) {
      glVertex3dv(vP[tP[i][j]]);
    }
  }
  glEnd();
  glutSwapBuffers();
}

void resize(int w, int h) {
  double wd, hd;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-3, 3, -3, 3, -3, 3);
}

void init() { /* ‰Šú‰»–½—ß */
  gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
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

static void timer(int dummy) { /*???????????*/
  glutTimerFunc(100, timer, 0);
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

void idle() { /*????????*/

  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutTimerFunc(100, timer, 0);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyin);

  init();
  glutMainLoop();

  return 0;
}