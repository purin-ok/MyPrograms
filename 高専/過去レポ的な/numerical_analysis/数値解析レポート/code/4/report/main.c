#include "NAbasic.h"

#define df(x, y, t) (x + (6 * y) + t - 10)
#define dg(x, y, t) (x + t - 3)

//Euler method
void Euler_method(double t, double dt, double tn, double x0, double y0){
	int i;
	double n=(tn - t) / dt;
	double *x, *y;

	x = (double*)malloc(sizeof(double) * n);
	y = (double*)malloc(sizeof(double) * n);

	x[0] = x0;
	y[0] = y0;
	printf("%f, %f, %f\n",t , x[0], y[0]);

	for(i = 1; t <= tn; i++){
		x[i] = x[i - 1] + df(x[i - 1], y[i - 1], t) * dt;
		y[i] = y[i - 1] + dg(x[i - 1], y[i - 1], t) * dt;
		t += dt;
		printf("%f, %f, %f\n",t , x[i], y[i]);
	}

	free(x);
	free(y);
}

int main(int argc, char **argv){
	FILE *fin;
	double **a;
	int arow, acol;

	//Checking the command line
	if(argc != 2){
		fprintf(stderr, "ERROR: invalid command line usage\n");
		return EXIT_FAILURE;
	}

	//Open the csv file
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ERROR: the file does not exist\n");
		return EXIT_FAILURE;
	}

	//Read data from csv
	a = csvRead(&arow, &acol, fin);
	if (1 != arow) {
		puts("ERROR: there is an error in your input\n");
		return EXIT_FAILURE;
	}

	Euler_method(a[0][0], a[0][1], a[0][2], a[0][3], a[0][4]);

	return EXIT_SUCCESS;
}