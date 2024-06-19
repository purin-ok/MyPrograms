#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define N 50

double g(double y, double z, double x) {
	return x + 6 * y - 5 * z;
}

double f(double y, double z, double x) {
	return z;
}

double true_x(double t) {
	return -2 * exp(-2 * t) - t + 3;
}

double true_y(double t) {
	return exp(t) - exp(-6 * t);
}



int main()
{
	double y[N], z[N];
	double l = 0, r = 2, x = 0;
	int n;
	double dt = (l + r) / N;
	int i;

	y[0] = 0;
	z[0] = 7;

	printf("%.6lf, %.6lf, %.6lf, %.6lf\n", x, y[0], z[0], true_y(x));
	for (i = 1; i <= N; i++) {
		x += dt;
		y[i] = y[i - 1] + f(y[i - 1], z[i - 1], x) * dt;
		z[i] = z[i - 1] + g(y[i - 1], z[i - 1], x) * dt;
		printf("%.6lf, %.6lf, %.6lf, %.6lf\n", x, y[i], z[i], true_y(x));
	}


	return 0;
}
