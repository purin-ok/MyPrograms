#include <math.h>
#include "NAbasic.h"

#define eps 1e-6

/* 関数f(x)の定義 */
double divf(double x, double y){
	return -x*y + x;
}

/* ホルン法 */
double horun(double x, double y, double h, double b){
	double y_1;
	while(x < b){
	y_1 = divf(x, y);
	y = y + h/2*(y_1 + divf((x + h), (y + h*y_1)));
	x += h;
	}
	
	return y;
}

int main(int argc, char **argv){
	int row, col;
	double x, y, h, b, s;
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

	x = matrix[0][0];	/* xの初期値 */
	h  = matrix[0][1];	/* ステップ幅 */
	b  = matrix[0][2];	/* xの最終値 */
	y = matrix[0][3];	/* yの最終値 */
	
	/* ホルン法 */
	s = horun(x, y, h, b);
		
	printf("ホルン法による結果:%4f", s);
	freeMatrix(matrix);	/* きちんと後処理する。 */

	return EXIT_SUCCESS;
}