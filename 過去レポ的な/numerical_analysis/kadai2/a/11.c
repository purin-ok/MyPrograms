/*ロンバーグ積分*/
#include "NAbasic.h"
#include<math.h>
//#define F(x) pow(M_E,(x)) /*積分する関数*/
#define F(x) (exp(x) - (x*x*x) + 5*sin(x)) /*積分する関数*/
#define N 5 /*分割数*/

/*
ロンバーグ法によって積分を計算する関数
入力
  n:分割数
  a1,a2:積分区間
出力
  result:積分値
*/
double Romberg(double a1,double a2){
  int i,k,m,n,p;
  double h,sum;
  double T[20][20];

  T[0][0]=(a2-a1)*(F(a2)+F(a1))/2;

  n=1;

  for(k=1;k<N;k++){
    /*分割数を増やす*/
    n*=2;
    h=(a2-a1)/n;
    sum=0;
    for(i=1;i<=n;i++)
      if(i%2==1) sum+=F(a1+i*h);

    T[k][0] = T[k-1][0]/2 + h*sum;

    /*次数を増やす*/
    p=1;
    for(m=1;m<=k;m++){
      p*=2;
      T[k][m] = T[k][m-1] + (T[k][m-1] - T[k-1][m-1])/(p*p-1);
    }
  }

  /*結果を表示*/
  printf("分割数:%d　次数:%d\n",n,p);
  puts("Romberg Table");
  for(k=0;k<N;k++){
    for(m=0;m<=k;m++){
      printf("%.10f  ",T[k][m]);
    }
    putchar('\n');
  }

  printf("積分値%f\n",T[N-1][N-1]);

  return 0;
}

int main(int argc, char ** argv){
	FILE *f;
	int row,col;
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
	if((col != 2)||(row !=1 )){
		fprintf(stderr, "入力が違います\n");
		return 0;
	}

  Romberg(matrix[0][0],matrix[0][1]);
}
