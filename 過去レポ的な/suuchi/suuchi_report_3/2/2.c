#include <stdio.h>
#include <math.h>
#include "NAbasic.h"


double f(double x) {
	return exp(x);
}

double trapezoid(double a, double b, int n) {

	double sum = 0, h = (b - a) / n, x = a;
	int i;
	for (i = 1; i < n; i++) {
		x += h;
		sum += f(x);
	}
	sum += (f(a) + f(b)) / 2;
	sum *= h;
	return sum;
}

double simpson(double a, double b, double n) {

	int i;
	double sum = 0, h = (b - a) / (2 * n), x = a, mid;
	
	for (i = 1; i <= n; i++) {
		mid = x + h;
		sum += (4 * f(mid) + f(x) + f(x + h)) * h / 3;
		x += h * 2;
	//((*func)(a + 2 * k * h) + 4 * (*func)(a + (2 * k + 1) * h) + (*func)(a + (2 * k + 2) * h));
	}
	return sum;
}

double romberg(double a, double b, int n) {
	
	double tmp;
	double r[n + 1][n + 1];
	int i, j, k;

	r[1][1] = (b - a) / 2 * (f(a) + f(b));

	for (k = 2; k <= n; k++) {
		tmp = 0;
		for (i = 1; i <= pow(2, k - 2); i++) {
			tmp = tmp + f(a + (2 * i - 1) * (b - a) / pow(2, k - 1));
		}
		r[k][1] = (r[k - 1][1] + (b - a) / pow(2, k - 2) * tmp) / 2;
	}

	for (k = 2; k <= n; k++) {
		for (j = 2; j <= k; j++) {
			r[k][j] = r[k][j - 1] + (r[k][j - 1] - r[k - 1][j - 1]) / (pow(4, j - 1) - 1);
		}
	}
	return r[n][n];
}



int main()
{
	int n;
	for (n = 1; n <= 25; n++) {
		printf("%d, %.10lf, %.10lf, %.10lf\n", n, 
			fabs(17.367255 - trapezoid(1, 3, n)),
			fabs(17.367255 - simpson(1, 3, n)),
			fabs(17.367255 - romberg(1, 3, n)));
	}

	return 0;
}
