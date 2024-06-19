#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define BUF 80
#define EPS 1e-12

//行列とベクトルの積を求める
double* matrix_times_vector(double** x, double* y, int xrow, int xcol, int ylen) {
	int i, j;
	double* ret = allocVector(ylen);

	if (xrow != ylen) {
		puts("error at matrix_times_vector()");
		return ret;
	}

	for (i = 0; i < xrow; i++) {
		for (j = 0; j < xcol; j++) {
			ret[i] += x[i][j] * y[j];
		}
	}

	return ret;
}

//前進消去
void forward_elimination(double** L, double* y, double* Pb, int Arow) {
	int i, j;

	for (i = 0; i < Arow; i++) {
		y[i] = Pb[i] / L[i][i];
		for (j = 0; j < i; j++) {
			y[i] -= y[j] * L[i][j] / L[i][i];
		}
	}
}

//後退代入
void backward_substitution(double** U, double* x, double* y, int Arow) {
	int i, j;

	for (i = Arow - 1; i >= 0; i--) {
		x[i] = y[i] / U[i][i];
		for (j = i + 1; j < Arow; j++) {
			x[i] -= x[j] * U[i][j] / U[i][i];
		}
	}
}

//行列のx行目とy行目を入れ替える
void swap_row(double** a, int row, int x, int y) {
	if (x < 0 || x >= row || y < 0 || y >= row) {
		puts("error at swap_row()");
		return;
	}
	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

//LU分解を行う関数
int LU(double** A, double** L, double** U, double** P, int Arow) {
	int i, j, k, pivot;
	double q;

	for (i = 0; i < Arow; i++) {
		for (pivot = j = i; j < Arow; j++) {
			if (fabs(A[j][i]) > fabs(A[pivot][i])) {
				pivot = j;
			}
		}

		swap_row(A, Arow, i, pivot);
		swap_row(L, Arow, i, pivot);
		swap_row(U, Arow, i, pivot);
		swap_row(P, Arow, i, pivot);

		q = A[i][i];

		// LU分解不可能であればエラー
		if (0 == q) {
			puts("error at LU()");;
			return EXIT_FAILURE;
		}
		for (j = i; j < Arow; j++) {
			L[j][i] = A[j][i];
			A[i][j] /= q;
		}

		for (k = i + 1; k < Arow; k++) {
			q = A[k][i];
			for (j = i; j < Arow; j++) {
				A[k][j] -= A[i][j] * q;
			}
		}

		for (j = i; j < Arow; j++) {
			U[i][j] = A[i][j];
		}
	}

	return EXIT_SUCCESS;
}

//ベクトルどうしの内積を計算する
double inner_product(double* x, double* y, int n) {
	int i;
	double ret = 0;

	for (i = 0; i < n; i++) {
		ret += x[i] * y[i];
	}
	return ret;
}

//ベクトルを単位ベクトルにする
int normalize(double* x, int n) {
	double norm = 0; 
	int i;

	for (i = 0; i < n; i++) {
		norm += x[i] * x[i];
	}

	norm = pow(norm, 0.5);

	//零ベクトルの時はエラー
	if (0 == norm) {
		puts("error at normalize()");
		return EXIT_FAILURE;
	}

	for (i = 0; i < n; i++) {
		x[i] /= norm;
	}

	return EXIT_SUCCESS;
}



int main(int argc, char* argv[]) {

	FILE *fin;
	double **A, **L, **U, **P;
	double *y, *pre_y, *z;
	double lambda = 10e9, pre_lambda;//ラムダには充分大きい値を入れておく
	int row, col;
	int i, j;
	char file_name[256];
	
	// csvファイルの入力
	printf("行列のファイル名を入力してください：");
	scanf("%s", file_name);
	putchar('\n');

	// csvファイル読み込み
	if ((fin = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	A = csvRead(&row, &col, fin);


	y     = allocVector(row);
	pre_y = allocVector(row);

	//yを適当な行列にする
	for (i = 0; i < row; i++) {
		y[i] = 1;
	}

	do {
		pre_lambda = lambda;
		memcpy(pre_y, y, sizeof(double) * row);

		y = matrix_times_vector(A, pre_y, row, col, row);
		lambda = inner_product(y, y, row) / inner_product(y, pre_y, row);
		normalize(y, row);
		

	} while (fabs((pre_lambda - lambda) / pre_lambda) > EPS);
	
	printf("最大固有値 = %.10lf\n", lambda);

	//LU分解用のメモリを確保
	L = allocMatrix(row, col);
	U = allocMatrix(row, col);
	P = allocMatrix(row, col);
	z = allocVector(row);

	//Pを単位行列にする
	for (i = 0; i < row; i++) {
		P[i][i] = 1;
	}

	//LU分解で失敗したら終了
	if (LU(A, L, U, P, row)) {
		return 0;
	}

	//yを適当な行列にする
	for (i = 0; i < row; i++) {
		y[i] = 1;
	}

	// 最小固有値を求める
	do {
		pre_lambda = lambda;
		memcpy(pre_y, y, sizeof(double) * row);

		forward_elimination(L, z, pre_y, row);
		backward_substitution(U, y, z, row);

		lambda = inner_product(y, pre_y, row) / inner_product(y, y, row);

		normalize(y, row);
	} while (fabs((lambda - pre_lambda) / pre_lambda) > EPS);

	printf("最小固有値 = %.10lf\n", lambda);

	//メモリの解放
	freeMatrix(A);
	freeMatrix(L);
	freeMatrix(U);
	freeMatrix(P);
	freeVector(z);
	freeVector(pre_y);
	freeVector(y);
	

	return EXIT_SUCCESS;
}