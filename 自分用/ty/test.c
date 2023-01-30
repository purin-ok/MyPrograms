#include <math.h>
#include <stdio.h>

#define N 1000

int main(void) {
  double x[N];  // 入力信号
  double real[N], imag[N];  // 周波数成分の実数部と虚数部
  double amplitude[N];      // 周波数成分の振幅




  // DFT の計算
  for (int k = 0; k < N; k++) {
    real[k] = 0;
    imag[k] = 0;
    for (int n = 0; n < N; n++) {
      real[k] += x[n] * cos(2 * M_PI * k * n / N);
      imag[k] -= x[n] * sin(2 * M_PI * k * n / N);
    }
    amplitude[k] = sqrt(real[k] * real[k] + imag[k] * imag[k]);
  }

  // 結果の表示
  for (int k = 0; k < N; k++) {
    printf("%d: amplitude = %f\n", k, amplitude[k]);
  }

  return 0;
}