/*キーID*/
#define KEY_D 1
#define KEY_F 2
#define KEY_G 4

#define KEY_W 8
#define KEY_S 16

#define KEY_E 32
#define KEY_R 64
#define KEY_T 128

//押されたキーフラグ
unsigned short pressed = 0;

static void timer(int dummy) {
  glutTimerFunc(10, timer, 0);

  if (pressed & KEY_S) {
    scale += 0.1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-scale, scale, -scale, scale, -10, 10);
    glutPostRedisplay();
    pressed = 0;
  } else if (pressed & KEY_W) {
    scale -= 0.1;
    if (scale <= 0) scale = 0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-scale, scale, -scale, scale, -10, 10);
    glutPostRedisplay();
    pressed = 0;
  } else if (pressed) {
    //押されたボタンに応じて1度ずつ回転
    rotAng[0] += (pressed & KEY_D) != 0 ? 1 : 0;
    rotAng[1] += (pressed & KEY_F) != 0 ? 1 : 0;
    rotAng[2] += (pressed & KEY_G) != 0 ? 1 : 0;
    rotAng[0] -= (pressed & KEY_E) != 0 ? 1 : 0;
    rotAng[1] -= (pressed & KEY_R) != 0 ? 1 : 0;
    rotAng[2] -= (pressed & KEY_T) != 0 ? 1 : 0;
    glutPostRedisplay();
    pressed = 0;
  }
}

//フラグセット
void keyin(unsigned char key, int x, int y) {
  switch (key) {
    case 'd':
      pressed |= KEY_D;
      break;
    case 'f':
      pressed |= KEY_F;
      break;
    case 'g':
      pressed |= KEY_G;
      break;
    case 'e':
      pressed |= KEY_E;
      break;
    case 'r':
      pressed |= KEY_R;
      break;
    case 't':
      pressed |= KEY_T;
      break;
    case 'w':
      pressed |= KEY_W;
      break;
    case 's':
      pressed |= KEY_S;
      break;
    case 'q':
    case 'Q':
      exit(0);
    default:
      break;
  }
}
