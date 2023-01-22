#include "NAbasic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*いぷしろん*/
#define EPS 1e-10

/*内積求める（おんなじとこ同士で掛算して全部足すだけ）*/
double inpro(double **x, double **y, int len)
{
    int i;
    double ans=0;
    for(i = 0; i < len; i++)
    {
		ans += x[i][0] * y[i][0];
	}

    return ans;
}

/*行列A * 行列x 　Aは任意の列と行　xは列ベクトル
行列Aのポインタ,行列xのポインタ,次の行列x_nのポインタ,Aの行数,Aの列数*/
double** Ax(double **A, double **y, double **y_n, int row, int col)
{
    int i, j;
    for(i = 0; i < row; i++)
    {
        y_n[i][0] = 0;
        for(j = 0; j < col; j++)
        {
        y_n[i][0] += A[i][j] * y[j][0];

        }
        
    }

    return y_n;
}
/*ベクトルを正規化*/
int normalize(double **x, int len) {
	double norm = 0; // ベクトルのノルム
	int i;

	/*normをもとめる*/
	for (i = 0; i < len; i++) {
		norm += x[i][0] * x[i][0];
	}
	norm = sqrtf(norm);

	/*normで割る*/
	for (i = 0; i < len; i++) {
		x[i][0] /= norm;
	}

	return EXIT_SUCCESS;
}

/*行列を表示する関数*/
void printmat(double **matrixX,int row, int col)
{
    int i,j;
    for(i = 0; i < row; i++)
    {
    printf("|");
        for(j = 0; j < col; j++)
        {
            printf("%lf  ", matrixX[i][j]);

        }
    printf("|\n");
    }
}

/*行列の行を入れ替える*/
int swap_row(double **a, int row, int x, int y) {
	double *tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;

	return EXIT_SUCCESS;
}

/*LU分解*/
int lu (double **A, double **L, double **U, double **P, int rowA)
{
	int i, j, k, pivot;
	double q;

	for (i = 0; i < rowA; i++) {
		// ピボット抽出
		for (pivot = j = i; j < rowA; j++) {
			if (fabs(A[j][i]) > fabs(A[pivot][i])) {
				pivot = j;
			}
		}

		// ピボットに基づいて行交換
		swap_row(A, rowA, i, pivot);
		swap_row(L, rowA, i, pivot);
		swap_row(U, rowA, i, pivot);
		swap_row(P, rowA, i, pivot);

		q = A[i][i];
		if (0 == q) {
			// LU分解不可能であればエラー
			puts("Defective A Data!");
			return EXIT_FAILURE;
		}
		for (j = i; j < rowA; j++) {
			L[j][i] = A[j][i];
			A[i][j] /= q;
		}

		for (k = i + 1; k < rowA; k++) {
			q = A[k][i];
			for (j = i; j < rowA; j++) {
				A[k][j] -= A[i][j] * q;
			}
		}

		for (j = i; j < rowA; j++) {
			U[i][j] = A[i][j];
		}
	}

	return EXIT_SUCCESS;
}

/*前進消去*/
void forward_erase(double **L, double **y, double **Pb, int Arow)
{
	int i, j;
	for (i = 0; i < Arow; i++) {
		y[i][0] = Pb[i][0] / L[i][i];
		for (j = 0; j < i; j++) {
			y[i][0] -= y[j][0] * L[i][j] / L[i][i];
		}
	}
}


/*後退代入*/
void backward_erase(double **U, double **x, double **y, int Arow)
{
	int i, j;
	for (i = Arow - 1; i >= 0; i--) {
		x[i][0] = y[i][0] / U[i][i];
		for (j = i + 1; j < Arow; j++) {
			x[i][0] -= x[j][0] * U[i][j] / U[i][i];
		}
	}
}

/*main*/
int main (int argc, char** argv)
{
    FILE *finA;
	double **matrixA, **y, **y_next, **L, **U, **P, **z;
    double lambda = 1, last_lambda;
	int rowA, colA, i;


    /*  CSVから対象データを読み込む */
	if (((finA = fopen(argv[1], "r")) == NULL))
	{
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

    /*読み込んだCSVファイルを行列Aに入れる*/
    matrixA = csvRead(&rowA, &colA, finA);

    /*読み込んだCSVファイルの行列を出力*/
    printf("A=\n");
    printmat(matrixA,rowA,colA);

    /*列ベクトルyを作り、適当な値を入れる(ここでは1)行列Aの行または列の数作る(正則だから)*/
	y = allocMatrix(rowA,1);
    y_next = allocMatrix(rowA,1);

	for (i = 0; i < rowA; i++)
    {
		y[i][0] = 1;
	}

    /*最大固有値を求める*/
    while((fabs(lambda - last_lambda) / fabs(last_lambda)) >= EPS){
        last_lambda = lambda;
        y_next = Ax(matrixA,y,y_next,rowA,colA);
        lambda = inpro(y_next, y_next, rowA) / inpro(y_next,y,rowA);

        normalize(y_next, rowA);

        for(i = 0; i < rowA; ++ i)
        {
           y[i][0] = y_next[i][0];
        }
    }

    printf("最大固有値: %lf\n", lambda);
    
    /*LU分解用のメモリ確保*/
	L = allocMatrix(rowA, colA);
	U = allocMatrix(rowA, colA);
	P = allocMatrix(rowA, colA);
	z = allocMatrix(rowA, colA);

	/*とりあえずPは単位行列にする*/
	for (i = 0; i < rowA; i++) {
		P[i][i] = 1;
	}

	/*列ベクトルyを作り、適当な値を入れる(ここでは1)行列Aの行または列の数作る(正則だから)*/
	for (i = 0; i < rowA; i++) {
		y[i][0] = 1;
	}

    /*行列AをLU分解する*/
	if (lu(matrixA, L, U, P, rowA)) {
		return EXIT_FAILURE;
	}
    /*whileの条件満たすように値入れとく
    do whileでよかったかも*/
    lambda = 100000 ;
    last_lambda = 1;

    /*最小固有値を求める*/
    while((fabs(lambda - last_lambda) / fabs(last_lambda)) >= EPS){
        last_lambda = lambda;
        forward_erase(L, z, y, rowA);
        backward_erase(U, y_next, z, rowA);
        lambda = inpro(y_next, y, rowA) / inpro(y_next,y_next,rowA);
        normalize(y_next, rowA);
        for(i = 0; i < rowA; ++ i)
        {
           y[i][0] = y_next[i][0];
        }
    }

    printf("最小固有値: %lf\n", lambda);

    /*メモリばいばい*/
    freeMatrix(matrixA);
    freeMatrix(y);
    freeMatrix(y_next);
    freeMatrix(L);
    freeMatrix(U);
    freeMatrix(P);
    freeMatrix(z);
    return EXIT_SUCCESS;
}