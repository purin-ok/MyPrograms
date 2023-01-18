#include <stdio.h>
#include <math.h>
#include "NAbasic.h"
#define n 10                       //未知数の個数
#define MAX 100                //繰り返し最大回数
#define eps 1.0e-9           //最小誤差許容範囲

int main()
{

	FILE *fin1, *fin2;
	double **a, **b;

	int i, j, k, l;
	int row1, col1, row2, col2;
	
	double err;
	double pre_x[n] = { 1.0,1.0,1.0 }, x[n];

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


	for (k = 0; k < MAX; k++) {
		for (l = 0; l < n; l++) {
			printf("%lf ", pre_x[l]);
		}
		printf("\n");
		err = 0.0;                        //誤差のリセット
		for (i = 0; i < n; i++) {
			x[i] = *b[i];
			for (j = 0; j < n; j++) {
				if (j != i) {
					x[i] -= a[i][j] * pre_x[j];
				}
			}
			x[i] = x[i] / a[i][i];
		}

		/*各解の誤差を足し、古い解は捨て配列xoldに新しい解を入れる*/
		for (i = 0; i < n; i++) {
			err += fabs(pre_x[i] - x[i]);
			pre_x[i] = x[i];
		}

		/*足しあわされた誤差が許容範囲内だったら
		計算終了とし解が求まったとする*/
		if (err < eps) break;
	}

	/*求まった解を出力する*/
	for (i = 0; i < n; i++) {
		printf("%8.4f\n", x[i]);
	}

	/*繰り返し回数が最大回数の値だったら
	正確な解が求まっていない可能性大なので注意*/
	printf("繰り返し回数は %d\n", k + 1);

	return 0;
}
