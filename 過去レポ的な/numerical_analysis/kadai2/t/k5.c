#include "NAbasic.h"
#include <math.h>

void pivot_select(double **A,int *P,int row,int n){
	double amax;
	double *atemp;
	int pivot,temp,k;
	amax = fabs(A[0][0]);
	pivot = n;
	for(k=n+1;k<row;k++){
		if(fabs(A[k][0]) > amax){
			amax = fabs(A[k][0]);
			pivot = k;
		}
	}
	
	if(pivot != n){
		temp = P[n];
		P[n] = P[pivot];
		P[pivot] = temp;

		atemp = A[n];
		A[n] = A[pivot];
		A[pivot] = atemp;
	}
}

void LU(double **L,double **U,double **A,int* P,int row,int col){
	int i,j,k;
	double temp=0.0;
	L[0][0] = L[1][1] = L[2][2] = 1.0;
	L[0][1] = L[0][2] = L[1][2] = U[1][0] = U[2][0] = U[2][1]= 0.0;

	for(i = 0 ;i < row ;i++){
		if(i<2)	pivot_select(A,P,row,i);
		for(j = 0 ;j < i ;j++){
			if(j > 0) for(k = 0 ;k < j ;k++) temp += L[i][k]*U[k][j];
			L[i][j] = (A[i][j] - temp) / U[j][j];
			temp = 0.0;
			
		}
		for(j = 0 ;j < col ;j++){
			if(i > 0) for(k = 0 ;k < i ;k++) temp += L[i][k]*U[k][j];
			U[i][j] = A[i][j] - temp;
			temp = 0.0;
		}
	}
}

void inverse(double **L,double **U,int row,int col,double **outP,double **_L,double **_U,double **_A){
	int i,j,k;
	double E[3][3]={{1,0,0},
			{0,1,0},
			{0,0,1}};
	double temp=0.0;
	double **_LU;
	_LU = allocMatrix(row,col);

//Lの逆行列
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			for(k = 0; k < i; k++) temp += L[i][k] * _L[k][j];
			_L[i][j] = E[i][j] - temp;
			temp = 0.0;
		}
	}
//Uの逆行列
	for(i = row-1; i >= 0; i--){
		for(j = 0; j < col; j++){
			for(k = i; k <= row-1; k++) temp += U[i][k] * _U[k][j];
			_U[i][j] = (E[i][j] - temp) / U[i][i];
			temp = 0.0;
		}
	}
//Aの逆行列
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			_LU[i][j] = 0;
			for(k = 0; k < col; k++){
				_LU[i][j] += (_U[i][k] * _L[k][j]);
			}
		}
	}
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			_A[i][j] = 0;
			for(k = 0; k < col; k++){
				_A[i][j] += (_LU[i][k] * outP[k][j]);
			}
		}
	}
}

int main(int argc, char **argv){
	double **A,**b,**L,**U,**outP;
	double **_L,**_U,**_A;
	double x[3]={0},y[3]={0},xt[3]={0};
	int P[3]={0,1,2};

	FILE *fp1,*fp2;
	int row1,col1,row2,col2;
	int i,j,k;
	

	if((fp1=fopen(argv[1],"r"))==NULL){
		fprintf(stderr,"ファイルが存在しません.");
		return EXIT_FAILURE;
	}
	if((fp2=fopen(argv[2],"r"))==NULL){
		fprintf(stderr,"ファイルが存在しません.");
		return EXIT_FAILURE;
	}

	A = csvRead(&row1, &col1, fp1);
	b = csvRead(&row2, &col2, fp2);
	L = allocMatrix(row1,col1);
	U = allocMatrix(row1,col1);
	outP = allocMatrix(row1,col1);

	_L = allocMatrix(row1,col1);
	_U = allocMatrix(row1,col1);
	_A = allocMatrix(row1,col1);

	LU(L,U,A,P,row1,col1);
	
	puts("L行列\n");
	showMatrix((const double**)L,row1,col1);
	puts("U行列\n");
	showMatrix((const double**)U,row1,col1);

	for(i = 0; i < row1; i++){
		y[i] = b[P[i]][0];
		for(j = 0; j < i; j++) y[i] -= y[j] * L[i][j];
	}
	puts("y\n");
	for(i = 0; i < row1; i++) printf("%f\n",y[i]);
	
	if((U[2][0]==0.0)&&(U[2][1]==0.0)&&(U[2][2]==0.0)){
		for(i = row1-1; i >= 0; i--){
			if(i==row1-1){
				 xt[i] = 1;
			}else{
				 x[i] = y[i];
				for(j = i+1; j <= row1-1; j++){
					xt[i] -= xt[j] * U[i][j];
					x[i] -= x[j] * U[i][j];
				}
				xt[i] = xt[i]/U[i][i];
				x[i] = x[i]/U[i][i];
			}	
		}
	}else{
		for(i = row1-1; i >= 0; i--){
			x[i] = y[i];
			for(j = i+1; j <= row1-1; j++) x[i] -= x[j] * U[i][j];
			x[i] = x[i]/U[i][i];
		}
	}
	puts("P行列\n");
	for(i = 0; i < row1; i++){
		for(j = 0; j < col1; j++){
			if(j == P[i]) outP[i][j] = 1;
			else outP[i][j] = 0;
		}
	}
	showMatrix((const double**)outP,row1,col1);

	puts("x\n");
	if((U[2][0]==0)&&(U[2][1]==0)&&(U[2][2]==0)){
		for(i = 0; i < row1; i++) printf("%f + %f t\n",x[i],xt[i]);
		puts("(tは任意定数)");
	}else for(i = 0; i < row1; i++) printf("%f\n",x[i]);

	inverse(L,U,row1,col1,outP,_L,_U,_A);
	showMatrix((const double**)_L,row1,col1);
	showMatrix((const double**)_U,row1,col1);


	freeMatrix(A);
	freeMatrix(b);
	freeMatrix(L);
	freeMatrix(U);
	freeMatrix(outP);
	freeMatrix(_U);
	freeMatrix(_L);
	freeMatrix(_A);
	fclose(fp1);
	fclose(fp2);
	return EXIT_SUCCESS;
}