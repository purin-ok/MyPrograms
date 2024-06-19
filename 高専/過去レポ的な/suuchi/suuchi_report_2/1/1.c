#include <math.h>
#include "NAbasic.h"

#define BUF 80
#define DIM 3

int main() {
	FILE* fin;
	int i, j, k, m, n, dim, maxline;
	float temp, alpha, reserve, sum1, sum2;
	//float A[DIM][DIM], L[DIM][DIM], U[DIM][DIM];
    double** A, ** L, ** U;
	//float b[DIM], x[DIM], y[DIM];
    double **b, *x, *y;
    char c[sizeof(double)], file_name1[256], file_name2[256];

    int Arow, Acol, brow, bcol;


	printf("A CSV File Name<< ");
	scanf("%s", file_name1);
	puts("");

	// Aのcsvファイル読み込み
	if (NULL == (fin = fopen(file_name1, "r"))) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	// csvからデータを読み込み
	A = csvRead(&Arow, &Acol, fin);

    L = allocMatrix(Arow, Acol);
    U = allocMatrix(Arow, Acol);
    x = allocVector(Arow);
    y = allocVector(Arow);

	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			L[i][j] = 0.0;
			U[i][j] = 0.0;
		}
	}

	printf("b CSV File Name<< ");
	scanf("%s", file_name2);
	puts("");

	// yのcsvファイル読み込み
	if (NULL == (fin = fopen(file_name2, "r"))) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	// csvからデータを読み込み
	b = csvRead(&brow, &bcol, fin);

    printf("A\n");
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            printf(" %f ", A[i][j]);
        }
        printf("\n");
    }

    printf("B\n");
    for (i = 0; i < DIM; i++) {
        printf(" %f \n", b[i][0]);
    }
    //  -------------------------------------------------------
    //  LU ----------------------------------------------------
    for (i = 0; i < DIM; i++) {
        L[i][i] = 1.0;
    }
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            if (i <= j) {
                sum1 = 0.0;
                for (m = 0; m <= i - 1; m++) {
                    sum1 += L[i][m] * U[m][j];
                }
                U[i][j] = A[i][j] - sum1;
            }
            else if (i > j) {
                sum2 = 0.0;
                for (n = 0; n <= j - 1; n++) {
                    sum2 += L[i][n] * U[n][j];
                }
                L[i][j] = (A[i][j] - sum2) / U[j][j];
            }
        }
    }
    //  -------------------------------------------------------
    //  output for LU------------------------------------------
    //  L------------------------------------------------------
    printf("L\n");
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            printf(" %f ", L[i][j]);
        }
        printf("\n");
    }
    //  U------------------------------------------------------
    printf("U\n");
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            printf(" %f ", U[i][j]);
        }
        printf("\n");
    }
    //  -------------------------------------------------------
    //  solve the problem--------------------------------------
    //  Ly = b-------------------------------------------------
    for (i = 0; i < DIM; i++) {
        y[i] = b[i][0];
    }

    for (j = 0; j < DIM - 1; j++) {
        for (i = j + 1; i < DIM; i++) {
            y[i] -= y[j] * L[i][j];
        }
    }

    //  Ux = y
    for (i = 0; i < DIM; i++) {
        x[i] = y[i];
    }

    for (j = DIM - 1; j >= 0; j--) {
        x[j] /= U[j][j];
        for (i = 0; i <= j - 1; i++) {
            x[i] -= U[i][j] * x[j];
        }
    }
    //  -------------------------------------------------------
    //  output x-----------------------------------------------
    printf("x\n");
    for (i = 0; i < DIM; i++) {
        printf("x[%d] = %f\n", i + 1, x[i]);
    }

    return 0;
}
