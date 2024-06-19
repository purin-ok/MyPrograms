#include "NAbasic.h"
#define DX 0.001 /*増分*/
#define N 11 /*2分法の繰り返し回数*/

double func(double x){
	return x*x*x*x - 3*x*x + 5*x -9;
}

/*2文法による解法*/

int main(int argc, char ** argv){

	FILE *fin;
	int row,col,i;
	double **matrix;
	double a1,a2,f1,f2,x,mid;

	/*入力の確認*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s infile\n", argv[0]);
		return EXIT_FAILURE;
	}

	/*ファイルの読み込み*/
	if((fin  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	matrix = csvRead(&row,&col,fin);

	/*区間の読み込み*/

	a1 = matrix[0][0];
	a2 = matrix[0][1];

	f1 = func(a1);

	/*2分法で解を近似*/
	for(i=0;i<=N;i++){
		mid = (a1+a2)/2.0;
		if(func(mid)*func(a1)<0) a2 = mid;
		else a1 = mid;
		printf("%d回目:%0.10f\n",i,mid);
	}

	return 0;
}
