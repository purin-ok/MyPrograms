#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define N 5

double f(double x, double y, double t) {
	return x + 6 * y + t - 10;
}

double g(double x, double y, double t) {
	return x + t - 3;
}

double true_x(double t) {
	return -2 * exp(-2 * t) - t + 3;
}

double true_y(double t) {
	return exp(-2 * t) + 1;
}



int main()
{
	double x[N], y[N];
	double l = 0, r = 2, t = 0;
	int n;
	double dt = (l + r) / N;
	int i;

	x[0] = 1;
	y[0] = 2;

	printf("%.6lf, %.6lf, %.6lf, %.6lf, %.6lf\n", t, x[0], y[0], true_x(t), true_y(t));
	for (i = 1; i <= N; i++) {
		t += dt;
		x[i] = x[i - 1] + f(x[i - 1], y[i - 1], t) * dt;
		y[i] = y[i - 1] + g(x[i - 1], y[i - 1], t) * dt;
		printf("%.6lf, %.6lf, %.6lf, %.6lf, %.6lf\n", t, x[i], y[i], true_x(t), true_y(t));
	}


	return 0;
}
