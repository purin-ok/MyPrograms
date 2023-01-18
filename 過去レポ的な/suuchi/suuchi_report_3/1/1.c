#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define DATANUM 4


void exp_approxmation(double *a, double* X, double* Y) {
	
	int i;
	double x = 0, y = 0, xx = 0, xy = 0, n = DATANUM;

	for (i = 0; i < n; i++) {
		Y[i] = log(Y[i]);
	}

	for (i = 0; i < n; i++) {
		x += X[i];
		y += Y[i];
		xx += X[i] * X[i];
		xy += X[i] * Y[i];
	}

	a[0] = (y * xx - x * xy) / (n * xx - x * x);
	a[1] = (n * xy - x * y) / (n * xx - x * x);

	a[0] = exp(a[0]);
	return;
}


int main()
{
	
	double a[2];
	double i;
	double x[] = { 1.5, 2.0, 2.5, 3.0 };
	double y[] = { 8.96, 14.78, 24.36, 40.17 };

	exp_approxmation(a, x, y);

	//printf("\n%.10lf\n", a[0]);
	//printf("%.10lf\n", a[1]);
	for (i = 0; i <= 5; i += 0.01) {
		printf("%lf, %lf\n", i, a[0] * exp(a[1] * i));
	}

	return 0;
}
