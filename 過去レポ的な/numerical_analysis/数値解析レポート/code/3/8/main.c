#include <math.h>
#include "NAbasic.h"

#define A_NUM 2
#define DATA_NUM 4

// 行列とベクトルの積を求める
double *matrix_times_vector(double **matrix, double *vector, int matrix_row, int matrix_col, int vector_len) {
    int i, j;
    double *ret = allocVector(vector_len);

    if (matrix_row != vector_len) {
        puts("計算できません.");
        return ret;
    }

    for (i = 0; i < matrix_row; i++) {
        for (j = 0; j < matrix_col; j++) {
            ret[i] += matrix[i][j] * vector[j];
        }
    }

    return ret;
}

// 行列を出力
void print_matrix(double **matrix, int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%lf ", matrix[i][j]);
        }
        puts("");
    }
	puts("");
}

// ベクトルを出力
void print_vector(double *vector, int row) {
    int i;
    for (i = 0; i < row; i++) {
        printf("%lf ", vector[i]);
		puts("");
    }
	puts("");
}

// 行列の行交換
void swap_row(double **matrix, int row, int row1, int row2) {
    if (row1 < 0 || row1 >= row || row2 < 0 || row2 >= row) {
        puts("不適切な値です.");
        return;
    }

    double *tmp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = tmp;
}

// LU分解 成功したら0を返す
int lu(
	double **A,
	double **L,
	double **U,
	double **P,
	int Arow,
	double *b
) {
	int i, j, k, pivot;
	double elim, bb[2] = {0};

	for (i = 0; i < Arow; i++) {
		//pivot選択
		for (pivot = j = i; j < Arow; j++) {
			if (fabs(A[j][i]) > fabs(A[pivot][i])) {
				pivot = j;
			}
		}

		swap_row(A, Arow, i, pivot);
		swap_row(L, Arow, i, pivot);
		swap_row(U, Arow, i, pivot);
		swap_row(P, Arow, i, pivot);

		elim = A[i][i];
		if (0 == elim) {
			print_matrix(A, Arow, Arow);
			puts("LU分解できません.");
			return EXIT_FAILURE;
		}
		//Lを決める
		for (j = i; j < Arow; j++) {
			L[j][i] = A[j][i];
			L[j][i] /= elim;
		}

		//Uを決める
		for (j = i; j < Arow; j++) {
			U[i][j] = A[i][j];
		}

		//二次元配列前進消去
		for (k = i+1; k < Arow; k++) {
			elim = L[k][i];
			for (j = i; j < Arow; j++) {
				A[k][j] -= A[i][j] * elim;
			}
		}
	}
	bb[0] = b[0];
	bb[1] = b[1];

	b[0] = bb[1];
	b[1] = bb[0] - ((bb[1] * 4) / 9);

	return EXIT_SUCCESS;
}

// 前進消去
void forward_elimination(
	double **L,
	double *vector,
	double *Pb,
	int Arow
) {
	int i, j;

	for (i = 0; i < Arow; i++) {
		vector[i] = Pb[i] / L[i][i];
		for (j = 0; j < i; j++) {
			vector[i] -= vector[j] * L[i][j] / L[i][i];
		}
	}
}

// 後退代入
void backward_substitution(
	double **matrix,
	double *vector,
	int matrix_row,
	double *x
) {
	int i, j;
	double sum;

	for(i = matrix_row - 1; i >= 0; i--){
		for(sum = 0, j = matrix_row - 1; j > i; j--){
			sum += matrix[i][j] * x[j];
		}
		x[i] = (vector[i] - sum) / matrix[i][i];
	}
}


//ガウスの消去法
void gauss_elim(double *a, double *b, double **A){
	double **L, **U, **P;
	int i;

	L = allocMatrix(2, 2);
	U = allocMatrix(2, 2);
	P = allocMatrix(2, 2);

	// 単位行列P
	for (i = 0; i < 2; i++) {
		P[i][i] = 1;
	}

	// LU分解が失敗したら終了
	if (lu(A, L, U, P, 2, b)) {
		puts("LU分解に失敗しました.");
	}

	// 連立方程式解く
	backward_substitution(U, b, 2, a);
}

//指数近似
void exp_app(double *x, double *y, double *a){
	double *b = allocVector(A_NUM), **A = allocMatrix(A_NUM, A_NUM);
	int i, j, k;

	//左辺
	for(j = 0; j < A_NUM; j++){
		for(k = 0; k < DATA_NUM; k++){
			b[j] += log(y[k]) * pow(x[k], j);
		}
	}

	//右辺
	for(j = 0; j < A_NUM; j++){
		for(i = j; i < A_NUM; i++){
			for(k = 0; k < DATA_NUM; k++){
				A[j][i] += pow(x[k], (j + i));
			}
		}
	}
	A[j - 1][i - 2] = A[i - 2][j - 1];

	//ガウスの消去法
	gauss_elim(a, b, A);

	a[0] = exp(a[0]);
}

int main() {
	double a[2] = {0};
	double x[4] = {1.5, 2.0, 2.5, 3.0};
	double y[4] = {8.96, 14.78, 24.36, 40.17};

	exp_app(x, y, a);

	printf("%f, %f", a[0], a[1]);

	return EXIT_SUCCESS;
}