#include <math.h>
#include "NAbasic.h"

//行列とベクトルの積を求める
double *matrix_times_vector(double **matrix, double *vector, int matrix_row, int matrix_col, int vector_len){
	int i, j;
    double *ret = allocVector(vector_len);

    if(matrix_row != vector_len){
        puts("計算できません.");
        return ret;
    }
    for(i = 0; i < matrix_row; i++){
        for(j = 0; j < matrix_col; j++){
            ret[i] += matrix[i][j] * vector[j];
        }
    }
    return ret;
}

//行列を出力
void print_matrix(double **matrix, int row, int col){
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%lf ", matrix[i][j]);
        }
        puts("");
    }
	puts("");
}

//ベクトルを出力
void print_vector(double *vector, int row){
    int i;
    for (i = 0; i < row; i++) {
        printf("%lf ", vector[i]);
    }
	puts("");
}

//行列の行交換
void swap_row(double **matrix, int row, int row1, int row2) {
    if (row1 < 0 || row1 >= row || row2 < 0 || row2 >= row) {
        puts("不適切な値です.");
        return;
    }

    double *tmp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = tmp;
}

//pivot選択
int pivot_selection(double **matrix, int matrix_row, int col){
	int pivot, i;

	//部分pivotに対応させる
	for(pivot = i = col; i < matrix_row - 1; i++){
		if(fabs(matrix[i + 1][col]) > fabs(matrix[pivot][col])){
			pivot = i + 1;
		}
	}
	return pivot;
}


//前進消去
void forward_elimination(double **U, double **L, double **vector, int matrix_row, int col){
	int i, j;
	double elim;

	for(i = col; i < matrix_row - 1; i++){
		elim = U[i + 1][col] / U[col][col];
		for (j = col; j < matrix_row; j++) {
			U[i + 1][j] -= U[col][j] * elim;
		}
		vector[i + 1][0] -= vector[col][0] * elim;
		L[i + 1][col] = elim;
	}
}

//後退代入
void backward_substitution(double **matrix, double **vector, int matrix_row, double *x){
	int i, j;
	double sum;

	//添え字に合わせるために-1
	for(i = matrix_row - 1; i >= 0; i--){
		for(sum = 0, j = matrix_row - 1; j > i; j--){
			sum += matrix[i][j] * x[j];
		}
		x[i] = (vector[i][0] - sum) / matrix[i][i];
	}
	puts("X =");
	print_vector(x, matrix_row);
}

//LU分解 成功したら0を返す
int lu(double **A, double **L, double **U, double **P, double **b, int Arow){
	int i, j, k, pivot;
	double elim;

	//AをUにコピー
	for(i = 0; i < Arow; i++){
		for(j = 0; j < Arow; j++){
			U[i][j] = A[i][j];
		}
	}

	//Lの対角成分は1
	for(i = 0; i < Arow; i++){
		L[i][i] = 1;
	}

	for (i = 0; i < Arow; i++) {
		//pivot選択
		pivot = pivot_selection(U, Arow, i);

		swap_row(A, Arow, i, pivot);
		swap_row(U, Arow, i, pivot);
		swap_row(P, Arow, i, pivot);
		swap_row(b, Arow, i, pivot);

		forward_elimination(U, L, b, Arow, i);

		//ピボット選択後もLU分解できない状態だった場合の対策
		elim = U[i][i];
		if (0 == elim) {
			print_matrix(U, Arow, Arow);
			puts("LU分解できません.");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

//メモリ開放
void free_mems(double **A, double **b, double **L, double **U, double **P, double *matrix, double *vector){
	freeMatrix(A);
	freeMatrix(b);
	freeMatrix(L);
	freeMatrix(U);
	freeMatrix(P);

	freeVector(matrix);
	freeVector(vector);
}

int main(int argc, char **argv) {
	FILE *fin;
	double **A, **b, **L, **U, **P, *x;
	int i, Arow, Acol, brow, bcol;

	//コマンドラインの処理
	if (argc != 3) {
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}
	// Aのcsvファイル読み込み
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	A = csvRead(&Arow, &Acol, fin);

	if (Arow != Acol) {
		puts("A行列が正方行列ではありません.");
		return EXIT_FAILURE;
	}

	// bのcsvファイル読み込み
	if ((fin = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	// csvからデータを読み込み
	b = csvRead(&brow, &bcol, fin);	

	if (1 != bcol) {
		puts("bが列ベクトルではありません.");
		return EXIT_FAILURE;
	}

	// 各変数のメモリ確保
	L = allocMatrix(Arow, Acol);
	U = allocMatrix(Arow, Acol);
	P = allocMatrix(Arow, Acol);
	x = allocVector(Arow);

	// 単位行列P
	for (i = 0; i < Arow; i++) {
		P[i][i] = 1;
	}

	// LU分解が失敗したら終了
	if (lu(A, L, U, P, b, Arow)) {
		puts("LU分解に失敗しました.");
		return EXIT_FAILURE;
	}

	// 各行列の出力
	puts("L =");
	print_matrix(L, Arow, Acol);

	puts("U =");
	print_matrix(U, Arow, Acol);

	puts("P =");
	print_matrix(P, Arow, Acol);

	// 連立方程式解く
	backward_substitution(U, b, Arow, x);

	free_mems(A, b, L, U, P, x);

	return EXIT_SUCCESS;
}