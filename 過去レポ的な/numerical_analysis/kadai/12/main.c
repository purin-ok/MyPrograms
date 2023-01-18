#include "NAbasic.h"
#define df(x, y) (-1 * x * y + x)

//Euler method
void Euler_method(double x, double h, double xn, double y){
	for(; x <= xn; x += h){
		printf("x = %f, y = %f\n", x, y);
		y += df(x, y) * h;
	}
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

	printf("STEP : %f\n", a[0][1]);
	puts("Answer");
	Euler_method(a[0][0], a[0][1], a[0][2], a[0][3]);

	return EXIT_SUCCESS;
}