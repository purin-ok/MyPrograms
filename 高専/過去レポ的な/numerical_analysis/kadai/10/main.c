#include <math.h>
#include "NAbasic.h"

//関数fx
double fx(double x){
	return x * x;
}

//台形公式  ( 分割数a0, 積分範囲[a1, a2] )
double trapezoid(double a0, double a1, double a2){
	double k, h, sum = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += h){
		sum += fx(k);
	}

	return (h / 2.0) * (fx(a1) + fx(a2) + (2.0 * sum));
}

//シンプソン公式
double simpson(double a0, double a1, double a2){
	double k, h, sum1 = 0, sum2 = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += (2 * h)){
		sum1 += fx(k);
	}

	for(k = a1 + (2 * h); k < a2; k += (2 * h)){
		sum2 += fx(k);
	}

	return (h / 3.0) * (fx(a1) + fx(a2) + (4.0 * sum1) + (2.0 * sum2));
}

int main(int argc, char **argv){
	FILE *fin;
	double a0, a1, a2;
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

	a0 = a[0][0];
	a1 = a[0][1];
	a2 = a[0][2];

	printf("S = %f\n", trapezoid(a0, a1, a2));
	printf("S = %f\n", simpson(a0, a1, a2));

	return EXIT_SUCCESS;
}