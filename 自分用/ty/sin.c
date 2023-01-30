/* sin波のCSVデータ生成 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double amp, dif, pi2, rad;

  pi2 = 2 * M_PI;
  dif = M_PI / 500.0;
  for (rad = 0; rad <= pi2; rad += dif) {
    amp = sin(rad) + sin(rad * 100);
    printf("%6.3f, %6.3f\n", rad * 100, amp);
  }
  return EXIT_SUCCESS;
}