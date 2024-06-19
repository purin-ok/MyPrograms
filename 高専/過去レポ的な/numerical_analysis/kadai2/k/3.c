#include <math.h>
#include "NAbasic.h"

// 関数f
double f(double x) {
	return (pow(x, 4)) - (3 * pow(x, 2)) + (5 * x) - 9;
}

// 微分した関数df
double df(double x) {
	return (4 * pow(x, 3)) - (6 * x) + 5;
}

// 2分法
void Bisection(
	double a1,
	double a2,
	double (*f)(double x)
){
	int i;
	double mid;

	puts("2分法");

	for (i = 1; 10 >= i; ++i) {
		//区間両端から開始
		mid = (a1 + a2) / 2.0;

		printf("%2d: x=%.9f\n", i, mid);

		//f(a1)とf(中間値)の符号を比べ，a1またはa2の値を中間値に変える
		if (0 > f(a1) * f(mid)) {
			a2 = mid;
		} else {
			a1 = mid;
		}
	}
}

// ニュートン法
void Newton(
	double a1,
	double a2,
	double(*f)(double x),
	double(*df)(double x)
) {
	int i;
	double x = (a1 + a2) / 2.0;

	puts("ニュートン法");

	for (i = 1; 10 >= i; ++i) {
		x = x - (f(x) / df(x));

		printf("%2d: x=%.9f\n", i, x);
	}
}

int main(int argc, char **argv) {
	FILE *fin;
	double **matrix, a1, a2;
	int row, col;

	//コマンドラインの処理
	if (argc != 2) {
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	matrix = csvRead(&row, &col, fin);

	// 範囲を初期化
	a1 = matrix[0][0];
	a2 = matrix[0][1];

	// 2分法
	Bisection(a1, a2, f);
	puts("");

	// ニュートン法
	Newton(a1, a2, f, df);

	return EXIT_SUCCESS;
}