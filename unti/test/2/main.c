#include "NAbasic.h" 

/*
calcMatrix(double **mat1,int row1,int col1, double **mat2, int row2, int col2)
  2つの行列の積を計算し2次元配列に結果を格納する

  入力
	mat1: 一つ目の行列
	row1,col1 : mat1の行数と列数
	mat2: 一つ目の行列
	row2,col2 : mat2の行数と列数
  出力
	mat3:
*/

double** calcMatrix(double **mat1,int row1,int col1, double **mat2, int row2, int col2){

	int i,j,k;
	double **mat3;
	
	/*計算可能かを判定*/
	if(col1 != row2){
		printf("計算できません");
		exit(EXIT_FAILURE);
	}

	/*計算結果格納用配列を用意*/
	mat3 = allocMatrix(row1,col2);

	/*行列を計算*/
	for(i=0;i<row1;i++){
		for(j=0;j<col2;j++){
			mat3[i][j]=0;
			for(k=0;k<col1;k++){
				mat3[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}

	return mat3;
}

int main(int argc, char ** argv){

	FILE *fin1,*fin2; 
	double **matrix1,**matrix2,**ans;
	int row1,col1,row2,col2;
	
	if(argc != 3){
		fprintf(stderr,"Usage: %s infile1 infile2 \n", argv[0]);
		return EXIT_FAILURE;
	}

	
	/*1つ目のファイルの読み込み*/
	if((fin1  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	matrix1 = csvRead(&row1,&col1,fin1);
	
	/*2つ目のファイルの読み込み*/
	if((fin2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	matrix2 = csvRead(&row2,&col2,fin2);
	
	/*行列の積を計算*/
	ans = calcMatrix(matrix1,row1,col1,matrix2,row2,col2);

	/*結果を表示*/
	showMatrix((const double**)ans, row1 , col2);

	/*領域の開放*/
	freeMatrix(ans);
	freeMatrix(matrix1);
	freeMatrix(matrix2);
	
	return 0;
}
