#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 4
#define MaxWindowNum 4

GLdouble field_ans[NUM][NUM][3] = {0.0};
GLdouble field_col[NUM][NUM][3] = {0.0};
int color_table[NUM][NUM] = {0.0};

// WindowID
int WindowID[MaxWindowNum];

void display1() { /* お手本画面の描画命令 */
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);

  // 四角形の描画
  glBegin(GL_QUADS);
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      glColor3dv(field_ans[i][j]);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 0.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 1.0) / NUM - 1.0);
      glVertex2d(2.0 * (i + 1.0) / NUM - 1.0, 2.0 * (j + 0.0) / NUM - 1.0);
    }
  }
  glEnd();

  // 外枠
  // glBegin(GL_QUAD_);
  // glEnd();
  glFlush();
}

void display2() { /* 操作画面の描画命令 */
  int i, j;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1.0, 0.0, 0.0);

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

  // glBegin(GL_QUAD_)

  glFlush();
}

void resize(int w, int h) {  // 画面の大きさ調整
  double wd, hd;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  wd = (double)w;
  hd = (double)h;
  (w < h) ? gluOrtho2D(-wd / wd, wd / wd, -hd / wd, hd / wd)
          : gluOrtho2D(-wd / hd, wd / hd, -hd / hd, hd / hd);
}

void idle() { /*コールバック関数*/
  glutPostRedisplay();
}

void check() {
  int i, j, k, isAnsFlag = 1;
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      for (k = 0; k < 3; k++) {
        // お手本と操作画面を見比べて，完全一致でなければ発動
        if (field_col[i][j][k] != field_ans[i][j][k]) {
          isAnsFlag = 0;
        }
      }
    }
  }
  // 最後まで完全一致なら発動
  // なにか処理を入れたい
  if (isAnsFlag) {
    printf("Congratulations!");
    Sleep(3000);
    exit(0);
  }
}

void keyin(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
    case 'A':
      check();
      break;

    default:
      break;
  }
}

void mouse(int btn, int state, int x, int y) {
  int i, j, k;
  double lx, ly;

  if ((btn == GLUT_LEFT_BUTTON) &&
      (state == GLUT_DOWN)) {  // 左クリックで色変更
    // カーソルのデバイス座標から処理内のどこの色を変えたいのか読み取る
    // このままだと画面サイズ変更に対応していない．resizeあたりと同じ考え方を使えば行けるはず．
    // 横方向
    i = (x / 480.0) * NUM;
    // 縦方向，デバイス座標系はy軸下向きが，ワールド座標系はy軸上向きが正なのでその補正．
    j = ((480.0 - y) / 480.0) * NUM;
    // printf("%d,%d,%d,%d\n", j, i, x, y);

    // 4色バージョン//できてない
    // // 色情報変化させるやつ
    // color_table[i][j] = (color_table[i][j] + 1) % 4;
    // // 対応する場所の色変更
    // field_col[i][j][(color_table[i][j] + 2) % 4] = 0.0;
    // if (color_table[i][j]) {
    //   field_col[i][j][color_table[i][j] - 1] = 1.0;
    // }

    // 8色バージョン
    // 色情報を変化させるやつ
    color_table[i][j] = (color_table[i][j] + 1) % 8;

    // 対応する場所の色変更
    field_col[i][j][0] = color_table[i][j] % 2;
    field_col[i][j][1] = (color_table[i][j] / 2) % 2;
    field_col[i][j][2] = color_table[i][j] / 4;

    glutIdleFunc(idle);
  }

  if ((btn == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {  // 右クリックで終了
    exit(0);
  }
}

void init() { /* 初期化命令 */
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
  int i, j, k;
  srand((unsigned int)time(NULL));

  // 値の作成
  for (i = 0; i < NUM; i++) {
    for (j = 0; j < NUM; j++) {
      // 4色やる方
      // k = rand() % 4;
      // if (k) {
      //   field_ans[i][j][k - 1] = 1.0;
      // }

      // 8色やる方
      for (k = 0; k < 3; k++) {
        field_ans[i][j][k] = rand() % 2;
      }
    }
  }

  glutInit(&argc, argv);

  // お手本画面
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  WindowID[1] = glutCreateWindow("Model Window");
  glutDisplayFunc(display1);
  glutReshapeFunc(resize);
  init();

  // 操作画面
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(480, 480);
  glutInitWindowPosition(655, 0);
  WindowID[2] = glutCreateWindow("Player Window");
  glutDisplayFunc(display2);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyin);
  glutMouseFunc(mouse);
  init();

  glutMainLoop();

  return 0;
}