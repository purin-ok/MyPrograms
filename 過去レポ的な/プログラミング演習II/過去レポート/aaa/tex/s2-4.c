
#define KEY_Z 256

//ダンスフラグ
char danceToggle = 0;
//方向転換までの長さ
const int danceLength = 20;
//回転速度
const double rotSpeed = 10;

static void timer(int dummy) {
    //回転方向転換までのタイマー
    static int danceTimer;
    //回転方向
    static short dir_rot[3];
    int i;
    glutTimerFunc(10, timer, 0);
    /*中略*/
    } else if (pressed & KEY_Z) {
        danceToggle = !danceToggle;
        danceTimer = danceLength;
    }
    /*中略*/
    if (danceToggle) {
        if (danceTimer < danceLength) {
            for (i = 0; i < 3; i++) {
                //なめらかに回転(cosをPIシフトして回す)
                rotAng[i] += rotSpeed * dir_rot[i] *
				(cos(danceTimer/(double)danceLength*M_PI*2+M_PI)+1)/10.0;
                //回転角の制限
                if (rotAng[i] > 90) {
                    rotAng[i] = 90;
                } else if (rotAng[i] < -90) {
                    rotAng[i] = -90;
                }
            }
            danceTimer++;
        } else {
            //回転方向の切り替え
            for (i = 0; i < 3; i++) {
                dir_rot[i] = rand() % 2 * 2 - 1;
            }
            danceTimer = 0;
        }
        glutPostRedisplay();
    }
    pressed = 0;
}