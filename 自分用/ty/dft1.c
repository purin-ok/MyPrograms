#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 80
#define DATANUM 20000
#define AMP 48000

int main(int argc, char **argv) {
  FILE *fp;
  double amp[DATANUM], tm[DATANUM];
  int i, j, n;
  double re, im, x, dt, df;
  char buf[BUF];
  // 入力信号
  double real[DATANUM], imag[DATANUM];  // 周波数成分の実数部と虚数部
  double amplitude[DATANUM];
  if (argc < 2) {
    fprintf(stderr, "File does not exist\n");
    return EXIT_FAILURE;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "File not open\n");
    return EXIT_FAILURE;
  }

  for (n = 0; n < DATANUM;) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
    if (buf[0] == '#') continue;
    // tm[n] = atof(strtok(buf, ","));
    amp[n] = atof(strtok(buf, "\r\n\0"));
    // printf("%f\f", amp[n]);
    n++;
  }
  fclose(fp);

  dt = 1 / AMP;  // 標本化間隔dt[s]

  // for (i = 0; i < n * 0.5; i++) {
  //   for (j = 0, re = 0, im = 0; j < n; j++) {
  //     re += amp[j] * cos(2 * M_PI * j * i / n) * dt;
  //     im += amp[j] * sin(2 * M_PI * j * i / n) * dt;
  //   }
  //   x = sqrt(re * re + im * im);
  //   printf("%f, %f\n", i / dt / n, x);
  // }

  // DFT の計算
  for (int k = 0; k < n; k++) {
    real[k] = 0;
    imag[k] = 0;
    for (int j = 0; j < n; j++) {
      real[k] += amp[j] * cos(2 * M_PI * k * j / n) / AMP;
      imag[k] += amp[j] * sin(2 * M_PI * k * j / n) / AMP;
    }
    // printf("a");
    amplitude[k] = sqrt(real[k] * real[k] + imag[k] * imag[k]);
  }
  // printf("\n");
  // 結果の表示
  for (int k = 0; k < n / 2; k++) {
    printf("%d, %f\n", k * AMP / n, amplitude[k]);
  }

  return 0;
}