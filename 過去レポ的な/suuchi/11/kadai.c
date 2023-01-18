#include <stdio.h>
#include <math.h>
#include "NAbasic.h"


double f(double x) {
	return exp(x) - x*x*x + 5*sin(x);
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

	for (k = 1; k <= n; k++) {
		for (j = 2; j <= k; j++) {
			r[k][j] = r[k][j - 1] + (r[k][j - 1] - r[k - 1][j - 1]) / (pow(4, j - 1) - 1);
		}
	}
	for (j = 1; j <= n; j++) {
		for (k = 0; k <= j; k++) {
			printf("%.10lf ", r[j][k]);
		}
		printf("\n");
	}
	return r[n][n];
}


int main()
{
	int n;
	printf("%d, %.10lf\n", 5, romberg(-2, 3, 7));
	

	return 0;
}
