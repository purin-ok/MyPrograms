#include <math.h>
#include "NAbasic.h"

#define EPS 1e-9
#define f_num 3

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
        D[l] = fabs(A[l][k]);//絶対値
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
	show_2(f_num, A);
    	printf("\n");
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
	int i, j, z, k, h;
	double zfai1, zfai2;
	FILE *fin;
	double **matrix;
	int row, col;
	double A[f_num][f_num];
	double B[f_num];
	double X[f_num];

	if (argc != 2) {
		fprintf(stderr, "NO\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "NO\n");
		return EXIT_FAILURE;
	}

	/* 行列を取り出す */
	matrix = csvRead(&row, &col, fin);

	/*
	for(i=0; i<f_num; i++){
		B[i] = 0;
		for(k=0, zfai1=1; k<row; k++){
			for(j=0; j<i; j++){
				zfai1 *= matrix[k][0];
			}
			B[i] += matrix[k][1] * zfai1;
		}
	}

	for(i=0; i<f_num; i++){
		for(j=0; j<f_num; j++){
			A[i][j] = 0;
			for(z=0, zfai1=1, zfai2=1; z<row; z++){
				for(k=0; k<i; k++){
					zfai1 *= matrix[z][0];
				}
				for(h=0; h<j; h++){
					zfai2 *= matrix[z][0];
				}
			A[i][j] += zfai1 * zfai2;
			}
		}
	}
	*/

	for (i = 0; i < f_num; i++) {
        	for (j = 0; j < row; j++) {
            		B[i] += matrix[j][1] * pow(matrix[j][0], i);
        	}
    	}

    	for (i = 0; i < f_num; i++) {
        	for (j = i; j < f_num; j++) {
            		for (k = 0; k < row; k++) {
                		A[i][j] += pow(matrix[k][0], i + j);
            		}
            		A[j][i] = A[i][j];
        	}
    	}
	

	//printf("%f\n", matrix[1][0]);

     
	show_2(f_num, A);
    	printf("\n");
  	show_1(f_num, B);
    	printf("\n");
    	printf("三角化\n");
    	delete(f_num, A, B);
     
    	show_2(f_num, A);
    	printf("\n");
    	show_1(f_num, B);
    	printf("\n");
    
    	ans(f_num, A, B, X);
    	printf("解\n");
    	show_1(f_num, X);

	freeMatrix(matrix);
 
	return EXIT_SUCCESS;
}