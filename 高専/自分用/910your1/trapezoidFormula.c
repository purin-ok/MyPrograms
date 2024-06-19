//trapezoidFormula.c
#include <stdio.h>

double func(double x);

int main(){

double a0;//分割数
double a1,a2;//積分範囲
float fa0,fa1,fa2;
double s,sum = 0.0;
FILE *fp;

  //csvファイルからx,yの値を読み込む
  if ((fp = fopen("k10-input.csv", "r")) == NULL) return 0;
      while(fscanf(fp, "%f, %f, %f ", &fa0, &fa1, &fa2) != EOF) {
          a0 = (double)fa0;
          a1 = (double)fa1;
          a2 = (double)fa2;
      }
  fclose(fp);

double split = (a2 - a1) / a0;//刻み幅

for(int i = 0; i < a0; i++){
  //台形の面積を求める
  s = ((func(a1 + split*i) + func(a1 + split*(i+1))) / 2.0) * split;
  sum += s;
}

printf("計算結果 = %lf\n",sum);
return 0;
}

double func(double x){
  return x*x;
}
