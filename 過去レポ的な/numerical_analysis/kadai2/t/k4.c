#include <math.h>
#include "NAbasic.h"

#define EPS 1e-9

void show_2(int N, double A[N][N]){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%f ",A[i][j]);
        }
        printf("\n");
    }
}

void show_1(int N, double B[N]){
    int i;
    for(i=0; i<N; i++){
        printf("%f\n",B[i]);
    }
}

int pibot(int N, double A[N][N], int k){
    double D[N];
    int p = 0;
    
    for(int l=k; l<N; l++){
        D[l] = A[l][k]*A[l][k];//絶対値で最大値を探すので二乗する
    }
    
    //最大値を探して保存
    double m = D[0];
    for(int a=1; a<N; a++)
        if(m<D[a]){
            m=D[a];
        }
    
    if(m==0){
          printf("解が一意に定まりません");
          exit(0);//exit関数を用いてきプログラムを終了する
      }
      
    
    for(int b=0; b<N; b++)
        if(m==D[b])
            p = b;//保存した最大値と同じ値をもつ添字を保存する
    
    
    return p;
}

void change(int N, double A[N][N], double B[N], int k, int p){
    int i;
    double S;
    double T;
    
    T = B[k];
    B[k] = B[p];
    B[p] = T;
    
    for(i=0; i<N; i++){
        S = A[k][i];
        A[k][i] = A[p][i];
        A[p][i] = S;
    }
    
}

void dash(int N, double A[N][N], double B[N], int k, int i){
    int l;
    double r = A[i][k]/A[k][k];
    
    for(l=k; l<N; l++){
        A[i][l] = A[i][l] - r*A[k][l];
    }
    
    B[i] = B[i] - r*B[k];
}

void delete(int N, double A[N][N], double B[N]){
    int k;
    int p=0;
    for(k=0; k<N-1; k++){
        p = pibot(N,A,k);
        change(N, A, B, k, p);
        for(int i=k+1; i<N; i++){
            dash(N, A, B, k, i);
        }
    }
}

void ans(int N, double A[N][N], double B[N], double X[N]){
    int i,j;
    X[N-1] = B[N-1]/A[N-1][N-1];
    
    for(i=N-2; i>=0; i--){
        
        double S=0;
        for(j=i+1; j<N; j++)
            S = S + A[i][j] * X[j];
        
        X[i] = (B[i]-S)/A[i][i];
    }
    
}


int main(int argc, char** argv) {
	int i, j;
	FILE *fin;
	double **matrix1, **matrix2;
	int row, col;

	if (argc != 3) {
		fprintf(stderr, "NO\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "NO\n");
		return EXIT_FAILURE;
	}

	/* 行列を取り出す */
	matrix1 = csvRead(&row, &col, fin);

	if ((fin = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "NO\n");
		return EXIT_FAILURE;
	}

	/* 行列を取り出す */
	matrix2 = csvRead(&row, &col, fin);

 	double A[row][row];
    	double B[row];
  	double X[row];

	for(i=0; i<row; i++){
		B[i] = matrix2[i][0];
		for(j=0; j<row; j++){
			A[i][j] = matrix1[i][j];
		}
	}
     
	show_2(row, A);
    	printf("\n");
  	show_1(row, B);
    	printf("\n");
    	printf("三角化\n");
    	delete(row, A, B);
     
    	show_2(row, A);
    	printf("\n");
    	show_1(row, B);
    	printf("\n");
    
    	ans(row, A, B, X);
    	printf("解\n");
    	show_1(row, X);

	freeMatrix(matrix1);
	freeMatrix(matrix2);
 
	return EXIT_SUCCESS;
}