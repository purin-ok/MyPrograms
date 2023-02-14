/*ニュートン法による補完*/
#include "NAbasic.h"

/*
補完した式の値を求める関数
入力
  matrix:計測データ
  row,col:計測データの行数、列数
  size:補完に使用するデータ数
  x:x座標
出力
  result:xでの値
*/
double N_interpolation(double **matrix,int row,int col,int size,int x){
  int i,j;
  double product,result=0;
  double **table; /*差分商表*/
  table = allocMatrix(size,size);

  /*表を作成*/
  for(i=0;i<size;i++) table[i][0] = matrix[i][1];

  for(i=1;i<size;i++){
    for(j=0;j<size-i;j++){
      table[j][i] = (table[j+1][i-1]-table[j][i-1])/(matrix[j+i][0]-matrix[j][0]);
    }
  }

  /*値を求める*/
  for(i=0;i<size;i++){
    product = 1;
    for(j=0;j<i;j++){
      product*=x-matrix[j][0];
    }
    result+=product*table[0][i];
  }

  return result;
}

int main(int argc, char ** argv){
  int x;
	FILE *f;
	int row,col;
  double result;
	double **matrix;

	/*コマンドライン引数の確認*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s file.CSV\n", argv[0]);
		return EXIT_FAILURE;
	}

	/*行列のCSVファイルの読み込み*/
	if((f  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	matrix = csvRead(&row,&col,f);

	/*入力をチェック*/
	if(col != 2){
		fprintf(stderr, "入力が違います\n");
		return 0;
	}

  /*入力を要求*/
  printf("xを入力");
  scanf("%d",&x);

  result = N_interpolation(matrix,row,col,3,x);
  printf("3点で補完==> y = %f\n",result);

  result = N_interpolation(matrix,row,col,4,x);
  printf("4点で補完==> y = %f\n",result);
}
