#include <GL/glut.h>
#include <math.h>

void display(void){
   displayBall(void);
}

void displayBall(void){
    int i, n = 200;
    double dt = 1;
    double x, y, r = 0.5;
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xACF3);
    glBegin(GL_POLYGON);
    glColor4f(0.7, 0.2, 0.2, 0.0);  // 円の色(RGBA)
    for (i = 0; i < n; i++) {
			x = r * cos(2.0 * 3.14 * ((double)i/n) );
			y = r * sin(2.0 * 3.14 * ((double)i/n) );
			glVertex3f(x, y, 0.0);		// 頂点の座標
	}
    glTranslatef(0, -dt, 0);
    glEnd();
    glFlush();
    dt += 1;
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Reshaape(int w, int h){
    glutReshapeWindow(1000, 1000);
}

void idle(void){
    glutPostRedisplay();
}

static void timer(int dummy){
    glutTimerFunc(100, timer, 0);
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutInit(&argc, argv);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    init();
    glutReshapeFunc(Reshaape);
    glutMainLoop();
    return 0;
}