#include <stdio.h>
#include <math.h>
#include "NAbasic.h"
#define n 10                       //未知数の個数
#define MAX 100                //繰り返し最大回数
#define eps 1.0e-9           //最小誤差許容範囲
#define EPS 1.0e-9           //最小誤差許容範囲

int main()
{

	FILE *fin1, *fin2;
	double **a, **b;

	int i, j, k, l;
	int row1, col1, row2, col2;
	double dx, absx, sum, new;

	double err;
	double x[n];
	for (i = 0; i < n; i++) {
		x[i] = 0;
	}

	char c[sizeof(double)], file_name1[256], file_name2[256];


	// 係数行列csvファイルの入力
	printf("係数行列のファイル名を入力してください：");
	scanf("%s", file_name1);
	putchar('\n');

	// csvファイル読み込み
	if ((fin1 = fopen(file_name1, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	// ベクトルycsvファイルの入力
	printf("ベクトルbのファイル名を入力してください：");
	scanf("%s", file_name2);
	putchar('\n');

	// csvファイル読み込み
	if ((fin2 = fopen(file_name2, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	a = csvRead(&row1, &col1, fin1);
	b = csvRead(&row2, &col2, fin2);

	do {                                // 反復計算のループ
		dx = 0.0;
		absx = 0.0;
		
		for (i = 0; i < n; i++) {
		    sum = 0;
			for (j = 0; j < n; j++) {
				if (i != j) {
					sum += a[i][j] * x[j];
				}
			}
			new = 1.0 / a[i][i] * (b[i][0] - sum);   // 反復計算後の近似解
			dx += fabs(new - x[i]);           // 近似解の変化量を加算
			absx += fabs(new);              // 近似解の総和計算
			x[i] = new;                     // 新しい近似解を代入
		}
	} while (dx / absx > EPS);

	/*求まった解を出力する*/
	for (i = 0; i < n; i++) {
		printf("%8.4f\n", x[i]);
	}

	/*繰り返し回数が最大回数の値だったら
	正確な解が求まっていない可能性大なので注意*/
	//printf("繰り返し回数は %d\n", k + 1);

	return 0;
}
