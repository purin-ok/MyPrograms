/*4次のルンゲ・クッタ法によるDEの解法*/
#include "NAbasic.h"
#include<math.h>

/*微分方程式の右辺*/
double F(double x,double y){
  return -x*y + x;
}

/*
DEの解を求める関数
入力
  x0:xの初期値
  h:ステップ幅
  xf:最終値
  y0:yの初期値
*/
void solve_DE(double x0,double h,double xf,double y0){
  double x;
  double y[2],k[4];

  y[1] = y0;

  /*ステップ幅を表示*/
  printf("STEP:%f\n",h);

  /*4次のルンゲ・クッタ法*/
  for(x=x0;x<=xf;x+=h){
    y[0] = y[1];

    k[0] = h*F(x,y[0]);
    k[1] = h*F(x+h/2,y[0]+k[0]/2);
    k[2] = h*F(x+h/2,y[0]+k[1]/2);
    k[3] = h*F(x+h,y[0]+k[2]);

    y[1] = y[0] + (k[0]+2*k[1]+2*k[2]+k[3])/6;

    printf("x=%f, y=%f\n",x,y[0]);
  }
}

int main(int argc, char ** argv){
	FILE *f;
	int row,col;
	double **input;

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
	input = csvRead(&row,&col,f);

	/*入力をチェック*/
	if((col != 4)||(row !=1 )){
		fprintf(stderr, "入力が違います\n");
		return 0;
	}

  /*DEを解く*/
  solve_DE(input[0][0],input[0][1],input[0][2],input[0][3]);

  /*領域の解法*/
  freeMatrix(input);
  free(f);
}
