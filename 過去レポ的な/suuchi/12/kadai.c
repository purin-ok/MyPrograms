#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

//関数f(x, y)の計算を行う関数
double f(double x, double y) {
	return -x * y + x;
}

//オイラー法を行う関数
void Euler(double x_0, double step, double x_fin, double y_0) {

	double x = x_0, y = y_0;

	printf("STEP = %.10lf\n", step);
	printf("Answer : \n");
	printf("x = %.10lf, y = %.10lf\n", x, y);

	while (x <= x_fin) {

		y = y + step * f(x, y);
		x = x + step;

		printf("x = %.10lf, y = %.10lf\n", x, y);
	}

	return;
}

int main(int argc, char* argv[]) {

	FILE *fin;
	char file_name[256];

	double **a;
	int row, col, i;
	
	// csvファイルの入力
	printf("ファイル名を入力してください：");
	scanf("%s", file_name);
	putchar('\n');

	// csvファイル読み込み
	if ((fin = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	a = csvRead(&row, &col, fin);

	//オイラー法を行う
	Euler(a[0][0], a[0][1], a[0][2], a[0][3]);

	fclose(fin);
	free(a);

	return EXIT_SUCCESS;
}