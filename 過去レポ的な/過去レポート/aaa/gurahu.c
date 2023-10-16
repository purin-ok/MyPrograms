#include<math.h>

void display(void) {
	double theta,x, y,c_theta;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin ( GL_LINE_STRIP );
	for (theta = 0.0; theta <= 2*M_PI; theta+=0.05) {
		c_theta=cos(theta);
		x=c_theta*(1+c_theta)*0.2;
		y=sin(theta)*(1+c_theta)*0.2;
		glVertex2d(x,y);
	}
	glEnd();
	glFlush();
}


