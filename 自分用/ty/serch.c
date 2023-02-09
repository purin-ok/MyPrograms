#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 80
#define DATANUM 20000

int main(int argc, char **argv) {
  FILE *fp;
  double amp[DATANUM], tm[DATANUM];
  int i, j, n;
  double re, im, x, dt, df;
  char buf[BUF];

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
    tm[n] = atof(strtok(buf, ","));
    amp[n] = atof(strtok(NULL, "\r\n\0"));
    n++;
  }

  for (i = 0, j = 0; i < n; i++) {
    if (amp[i] > amp[j]) j = i;
  }
  printf("%f, %f", tm[j], amp[j]);
}