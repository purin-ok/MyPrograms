#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

double norm(double *vec, int n){
	int i;
	double s = 0.0;

	for (i = 0; i < n; i++) {
		s += vec[i] * vec[i];
	}
	return sqrt(s);
}

double **matrix_product(double **a, int a_row, int a_col,
	double **b, int b_row, int b_col) {

	double **res = allocMatrix(a_row, b_col);
	int i, j, k;

	if (a_row != b_col || a_col != b_row) {
		puts("演算できません");
		return res;
	}

	for (i = 0; i < a_row; i++) {
		for (j = 0; j < b_col; j++) {
			for (k = 0; k < a_col; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return res;
}

double calc_angle(double **a, int a_row, int a_col,
			   		  double **b, int b_row, int b_col) {

	if (a_row != 1 || b_col != 1 || a_col != b_row) {
		puts("演算できません");
		return -1;
	}
	int n = a_row * a_col;
	double **p = matrix_product(a, a_row, a_col, b, b_row, b_col);

	return acos(p[0][0]/norm(matrix2colVector(a,a_row,a_col), n) / norm(matrix2colVector(b, b_row, b_col), n));
}


int main(int argc, char* argv[]) {
	FILE *fin1, *fin2;
	double **matrix1, **matrix2, **res;
	double a1, a2;
	int row1, col1, row2, col2;
	char c[sizeof(double)], file_name1[256], file_name2[256];
	
	// csvファイルの入力
	printf("ファイル名を入力してください：");
	scanf("%s", file_name1);
	putchar('\n');
	printf("ファイル名を入力してください：");
	scanf("%s", file_name2);
	putchar('\n');

	// csvファイル読み込み
	if ((fin1 = fopen(file_name1, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しませsん.\n");
		return EXIT_FAILURE;
	}
	if ((fin2 = fopen(file_name2, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	matrix1 = csvRead(&row1, &col1, fin1);
	
	matrix2 = csvRead(&row2, &col2, fin2);
	

	printf("result : %f[rad]\n", calc_angle(matrix1, row1, col1, matrix2, row2, col2));
	
	free(matrix1);
	free(matrix2);

	return EXIT_SUCCESS;
}