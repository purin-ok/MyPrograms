#include <math.h>
#include "NAbasic.h"

/* k=4とし、分割数を16とする。m=4とし、次数を4とする。 */
#define eps 1e-6
#define k 4
#define m 4

/* 関数f(x)の定義 */
double f(double x){
	return exp(x);
}

/* ロンバーグ法 */
double romberg(double a1, double a2){
	int i, j, n, x, y;
	double h, sum;
	double T[k+1][m+1];
	/* 初項を求める。 */
	h = a2 - a1;
	T[0][0] = h * (f(a1) + f(a2))/2;

	for(i=1, n=1; i<=k; i++){
		h /= 2;
		for(j=1, sum=0; j<=n; j++){
			sum += f(a1 + (2*j-1)*h);
		}
		T[i][0] = T[i-1][0]/2 + h*sum;

		if(m >= i){
			for(x=1, y=4; x<=i; x++){
				T[i][x] = T[i][x-1] + (T[i][x-1] - T[i-1][x-1])/(y - 1);
				if(fabs(T[i][x] - T[i][x-1]) < eps) break;
				y *= 4;
			}
		}
		if(fabs(T[i][0] - T[i-1][0]) < eps) break;
		n *= 2;
	}
	
	return T[i-1][x-1];
}

int main(int argc, char **argv){
	int n, div = 1, deg = 1;
	int row, col;
	double a1, a2, s;
	double **matrix;
	FILE *fin;

	/* 適切なコマンドライン引数が与えられていないときに警告する。 */
	if(argc != 2){
		fprintf(stderr, "Usage: %s difficult\n", argv[0]);
		return EXIT_FAILURE;
	}
	if((fin = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "File: %s cannot open\n", argv[1]);
		return EXIT_FAILURE;
	}

	matrix = csvRead(&row, &col, fin); /* データ読み込み */

	/* 範囲はa1からa2まで */
	a1 = matrix[0][0];
	a2 = matrix[0][1];

	/* ロンバーグ法 */
	s = romberg(a1, a2);
	
	/* 分割数を計算 */
	for(n=1; n<=k; n++){
		div *= 2;
	}
	/* 次数を計算 */
	for(n=1; n<=m; n++){
		deg *= 2;
	}
		
	printf("ロンバーグ法による積分結果:%4f, 分割数:%4d, 次数:%4d\n", s, div, deg);
	freeMatrix(matrix);	/* きちんと後処理する。 */

	return EXIT_SUCCESS;
}