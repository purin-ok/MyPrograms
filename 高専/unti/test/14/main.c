#include "NAbasic.h"
#define df(x, y) (-1 * x * y + x)

// Runge_Kutta
void Runge_Kutta(double x, double h, double xn, double y) {
  double k0, k1, k2, k3;

  for (; x <= xn; x += h) {
    printf("x = %f, y = %f\n", x, y);

    k0 = h * df(x, y);
    k1 = h * df((x + (h / 2)), (y + (k0 / 2)));
    k2 = h * df((x + (h / 2)), (y + (k1 / 2)));
    k3 = h * df((x + h), (y + k2));

    y += (k0 + (2 * k1) + (2 * k2) + k3) / 6;
  }
}

int main(int argc, char **argv) {
  FILE *fin;
  double **a;
  int arow, acol;

  // Checking the command line
  if (argc != 2) {
    fprintf(stderr, "ERROR: invalid command line usage\n");
    return EXIT_FAILURE;
  }

  // Open the csv file
  if ((fin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERROR: the file does not exist\n");
    return EXIT_FAILURE;
  }

  // Read data from csv
  a = csvRead(&arow, &acol, fin);
  if (1 != arow) {
    puts("ERROR: there is an error in your input\n");
    return EXIT_FAILURE;
  }

  printf("STEP : %f\n", a[0][1]);
  puts("Answer");
  Runge_Kutta(a[0][0], a[0][1], a[0][2], a[0][3]);

  return EXIT_SUCCESS;
}