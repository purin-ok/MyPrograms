#define N_VERTEX 7
double rotAng = 0.0;

void display(void) {
	int i;
	double theta, dt, x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	dt = 2.0 * M_PI / N_VERTEX;
	theta = rotAng;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < N_VERTEX; i++) {
		x = cos(theta);
		y = sin(theta);
		glVertex2d(x, y);
		theta += dt * 2;
	}
	glEnd();
	glFlush();
	rotAng += 2 * M_PI / 120;
}

static void timer(int dummy) {
    glutTimerFunc(10, timer, 0);
    glutPostRedisplay();
}
