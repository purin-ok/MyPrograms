#define N_VERTEX 7
double rotAng = 0.0;

void display(void) {
	int i;
	double theta, dt, x, y,delta;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	dt = 2.0 * M_PI / N_VERTEX;
	glBegin ( GL_LINE_STRIP );
	for (i = 0; i < N_VERTEX -1; i++) {
		theta = rotAng + dt*i;
		for (delta = i+1; delta < N_VERTEX; delta++) {
			x = cos( theta );
			y = sin( theta );
			glVertex2d (x, y);
			x = cos(theta - delta *dt );
			y = sin(theta - delta *dt );
			glVertex2d (x, y);
		}
	}
	glEnd();
	glFlush();
	rotAng += M_PI / 120;
}

