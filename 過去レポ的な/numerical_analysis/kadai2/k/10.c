#include <math.h>
#include "NAbasic.h"

//関数fx
double fx(double x){
	return x * x;
}

//台形公式  ( 分割数a0, 積分範囲[a1, a2] )
double trapezoid(double **a){
	double i, h, sum = 0;

	h = (a[0][2] - a[0][1]) / a[0][0];

	for(i = a[0][1] + h; i < a[0][2]; i += h){
		sum += fx(i);
	}

	return (h / 2.0) * (fx(a[0][1]) + fx(a[0][2]) + (2.0 * sum));
}

int main(int argc, char **argv){
	FILE *fin;
	double **a;
	int arow, acol;

	//コマンドラインの処理
	if(argc != 2){
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}

	//aのcsvファイル読み込み
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	//csvからデータを読み込み
	a = csvRead(&arow, &acol, fin);

	if (1 != arow) {
		puts("入力が不適です．\n");
		return EXIT_FAILURE;
	}

	printf("S = %f\n", trapezoid(a));

	return EXIT_SUCCESS;
}