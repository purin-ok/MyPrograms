#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

#define NUM 4

GLdouble field[NUM + 1][NUM + 1];
GLdouble field_col[NUM][NUM][3] = {0.0};

#define MaxWindowNum 4

// WindowID
int WindowID[MaxWindowNum];

void display1(void)
{ /* 描画命令 */
  int i, j;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  field_col[2][1][0] = 1.0;
  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_col[i][j]);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
    }
  }
  glEnd();
  glFlush();
}


void display2(void)
{ /* 描画命令 */
  int i, j;
  double theta, dt, x, y;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);
  field_col[2][1][1] = 1.0;
  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_col[i][j]);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
    }
  }
  glEnd();
  glFlush();
}


void init(void)
{
 glClearColor(0.0, 0.0, 1.0, 1.0);
}

int main(int argc, char* argv[])
{
 glutInit(&argc, argv);

 // 1st Window
 glutInitDisplayMode(GLUT_RGBA);
 glutInitWindowSize(640, 480);
 glutInitWindowPosition(0, 0);
 WindowID[1]=glutCreateWindow("Main Window");
 glutDisplayFunc(display1);
 init();

 // 2nd Window
 glutInitDisplayMode(GLUT_RGBA);
 glutInitWindowSize(640, 480);
 glutInitWindowPosition(655, 0);
 WindowID[2] = glutCreateWindow("2nd Window");
 glutDisplayFunc(display2);
 init();

 glutMainLoop();
 return 0;
}