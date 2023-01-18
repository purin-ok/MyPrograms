#include <math.h>
#include "NAbasic.h"

#define EPS 1e-10

//行列とベクトルの積を求める
double *matrix_times_vector(double **matrix, double *vector, int matrix_row, int matrix_col, int vector_len){
	int i, j;
    double *times = allocVector(vector_len);

    if(matrix_row != vector_len){
        puts("計算できません.");
        return times;
    }
    for(i = 0; i < matrix_row; i++){
        for(j = 0; j < matrix_col; j++){
            times[i] += matrix[i][j] * vector[j];
        }
    }
    return times;
}

//ベクトルの内積
double inner_product(double *x, double *y, int len){
	int i;
	double in_pro = 0;

	for(i = 0; i < len; i++){
		in_pro += x[i] * y[i];
	}
	return in_pro;
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

//行列の行交換
void swap_row(double **matrix, int row, int row1, int row2){
	double *tmp;

    if(row1 >= row || row1 < 0 || row2 >= row || row2 < 0){
        puts("不適切な値です.");
        return;
    }

    tmp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = tmp;
}

//1次元の行交換
void swap_row_1(double *vector, int row, int row1, int row2){
	double tmp;

    if(row1 >= row || row1 < 0 || row2 >= row || row2 < 0){
        puts("不適切な値です.");
        return;
    }

    tmp = vector[row1];
    vector[row1] = vector[row2];
    vector[row2] = tmp;
}

//前進消去
void forward_elimination(double **U, double **L, double *vector, int matrix_row, int col){
	int i, j;
	double elim;

	for(i = col; i < matrix_row - 1; i++){
		elim = U[i + 1][col] / U[col][col];
		for (j = col; j < matrix_row; j++) {
			U[i + 1][j] -= U[col][j] * elim;
		}
		vector[i + 1] -= vector[col] * elim;
		L[i + 1][col] = elim;
	}
}

//後退代入
void backward_substitution(double **matrix, double *vector, int matrix_row, double *x){
	int i, j;
	double sum;

	//添え字に合わせるために-1
	for(i = matrix_row - 1; i >= 0; i--){
		for(sum = 0, j = matrix_row - 1; j > i; j--){
			sum += matrix[i][j] * x[j];
		}
		x[i] = (vector[i] - sum) / matrix[i][i];
	}
}

//LU分解
int lu(double **A, double **L, double **U, double **P, double *b, int Arow){
	int i, j, pivot;
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

	for(i = 0; i < Arow; i++){
		//pivot選択
		pivot = pivot_selection(U, Arow, i);

		swap_row(A, Arow, i, pivot);
		swap_row(U, Arow, i, pivot);
		swap_row(P, Arow, i, pivot);
		swap_row_1(b, Arow, i, pivot);

		forward_elimination(U, L, b, Arow, i);
	}

	return EXIT_SUCCESS;
}

//ベクトルの正規化
int normalize(double *vector, int len){
	double norm = 0; //ベクトルのノルム
	int i;

	//ノルム計算
	norm = inner_product(vector, vector, len);
	norm = sqrtf(norm);

	//各要素をノルムで割る
	for(i = 0; i < len; i++){
		vector[i] /= norm;
	}
	return EXIT_SUCCESS;
}

//最大固有値
void Max_Eigenvalue(double **A, double *y, double *y_1, double lambda, double lambda_1, int Arow, int Acol){
	int i;
	
	//yを適当なベクトルに設定する
	for(i = 0; i < Arow; i++){
		y[i] = 1;
	}

	do{
			memcpy(y_1, y, sizeof(double) * Arow);
			y = matrix_times_vector(A, y_1, Arow, Acol, Arow);
			lambda_1 = lambda;
			lambda = inner_product(y, y, Arow) / inner_product(y, y_1, Arow);
			normalize(y, Arow);
		}while (fabs((lambda - lambda_1) / lambda_1) > EPS);

		printf("最大固有値: %.1lf\n", lambda);
	}

//最小固有値
void Min_Eigenvalue(double **A, double **L, double **U, double **P, double *temp, double *y, double *y_1, double lambda, double lambda_1, int Arow, int Acol){
	int i;

	//yを適当なベクトルに設定する
	for(i = 0; i < Arow; i++){
		y[i] = 1;
	}

	do{
		memcpy(y_1, y, sizeof(double) * Arow);
		memcpy(temp, y_1, sizeof(double) * Arow);
		lu(A, L, U, P, temp, Arow);
		backward_substitution(U, temp, Arow, y);
		lambda_1 = lambda;
		lambda = inner_product(y, y_1, Arow) / inner_product(y, y, Arow);
		normalize(y, Arow);
	}while(fabs((lambda - lambda_1) / lambda_1) > EPS);

	printf("最小固有値: %.1lf\n", lambda);
}

int main(int argc, char **argv){
	FILE *fin;
	double **A, **L, **U, **P, *y, *y_1, *temp, lambda = 10e10, lambda_1;
	int i, Arow, Acol;

	//コマンドラインの処理
	if(argc != 2){
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}
	//Aのcsvファイル読み込み
	if((fin = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	//ファイルから行列読み込み
	A = csvRead(&Arow, &Acol, fin);

	//変数のメモリ確保
	y = allocVector(Arow);
	y_1 = allocVector(Arow);

	//最大固有値を求める
	Max_Eigenvalue(A, y, y_1, lambda, lambda_1, Arow, Acol);

	//LU分解用のメモリ確保
	L = allocMatrix(Arow, Acol);
	U = allocMatrix(Arow, Acol);
	P = allocMatrix(Arow, Acol);
	temp = allocVector(Arow);

	// 単位行列P
	for(i = 0; i < Arow; i++){
		P[i][i] = 1;
	}

	//最小固有値を求める
	Min_Eigenvalue(A, L, U, P, temp, y, y_1, lambda, lambda_1, Arow, Acol);

	return EXIT_SUCCESS;
}