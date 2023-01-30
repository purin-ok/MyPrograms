#include <math.h>

#include "NAbasic.h"
#define FNF(x) x *x
void daikei(const double **mat) {
  int i, n;
  double a, b, h, s, x;
  a = mat[0][1];
  b = mat[0][2];
  n = mat[0][0];
  h = (b - a) / n;
  s = FNF(a) * h / 2.0 + FNF(b) * h / 2.0;
  for (i = 1; i <= n - 1; i++) {
    x = a + h * i;
    s += FNF(x) * h;
  }
  printf("\nÏ•ª‚Ì‹ßŽ—’l = %10.6lf\n", s);
}
int main(int argc, char **argv) {
  double **matrix;
  int row, col;
  FILE *fp;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s amplitude frequency/n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "cannot open");
    return EXIT_FAILURE;
  }

  matrix = csvRead(&row, &col, fp);
  daikei((const double **)matrix);
  freeMatrix(matrix);
  fclose(fp);

  return EXIT_SUCCESS;
}
