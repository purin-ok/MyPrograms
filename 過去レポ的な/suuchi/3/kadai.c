#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define STEP 20

//f(x)を計算する関数
double f(double x) {
	return exp(x) - 1 / x;
}

//f'(x)を計算する関数
double df(double x) {
	return exp(x) + 1 / (x * x);
}

//二分法を行う関数
void nibun(double a1,double a2) {

	int i;
	double mid;

	printf("二分法の実行結果\n");

	for (i = 1; i <= STEP; i++) {

		mid = (a1 + a2) / 2.0;

		printf("試行回数: %2d, x=%.9lf\n", i, mid);

		if (0 > f(a1) * f(mid)) {
			a2 = mid;
		}
		else {
			a1 = mid;
		}
	}
}

//ニュートン法を行う関数
void newton(double a1, double a2) {

	int i;
	double x = (a1 + a2) / 2.0;

	printf("ニュートン法の実行結果\n");
	for (i = 1; i <= STEP; i++) {

		x = x - f(x) / df(x);

		printf("試行回数: %2d, x=%.9lf\n", i, x);
	}
}

int main(int argc, char* argv[]) {
	FILE* fin;
	double** matrix;
	double a1, a2;
	int row, col;
	char c[sizeof(double)], file_name[256];
	
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
	matrix = csvRead(&row, &col, fin);

	// 数値をコピー
	a1 = matrix[0][0];
	a1 = 0.0001;
	a2 = matrix[0][1];
	
	//二分法の実行
	nibun(a1, a2);

	putchar('\n');

	//ニュートン法の実行
	newton(a1, a2);

	
	free(matrix);

	return EXIT_SUCCESS;
}