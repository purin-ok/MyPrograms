#include <math.h>
#include <stdio.h>
#define PI 3.14159265358979323846

void dft(double *x, double *y, int N) {
  for (int k = 0; k < N; k++) {
    y[k] = 0;
    for (int n = 0; n < N; n++) {
      y[k] += x[n] * cos(2 * PI * k * n / N) + x[k] * sin(2 * PI * k * n / N);
      printf("%d:amp%lf\n", n, y[k]);
    }
  }
}

int main() {
  int N = 256;
  double x[N], y[N];

  for (int n = 0; n < N; n++) {
    x[n] = sin(2 * PI * n / N);
  }

  dft(x, y, N);

  return 0;
}