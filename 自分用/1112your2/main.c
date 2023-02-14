// 12週目課題
// オイラー法による微分方程式の解の導出

#include <stdio.h>

// オイラー法で数値解を求める
int Euler(double x0, double h, double xm, double *y) {
  int a;
  double x;

  for (a = 1, x = 0; x < xm; a++) {
    x = x + h;
    y[a] = y[a - 1] + ((-(x - h) * y[a - 1] + (x - h)) * h);
    printf("x=%f,  ", x);
    printf("y=%lf\n", y[a]);
  }

  return 0;
}

int main(void) {
  FILE *fin;
  double y[1], h;
  double x0, xm, y0;
  /*
  x0 : xの初期値
  h : ステップ幅
  xm : xの最大値
  y0 : yの初期値
  */

  // csvファイルからデータを読み込む
  fin = fopen("k12-input.csv", "r");
  if (!fin) {
    perror("fopen");
    return 1;
  }

  fscanf(fin, "%lf, %lf, %lf, %lf\n", &x0, &h, &xm, &y0);
  fclose(fin);

  printf("STEP : %lf\n", h);
  y[0] = y0;

  printf("Answer\n");
  printf("x=%lf,  y=%lf\n", x0, y[0]);
  Euler(x0, h, xm, y);  // オイラー法で数値解を求める

  return 0;
}