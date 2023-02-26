#include <stdio.h>
int main() {
  int i, j;
  for (j = 0; j < 100; j++) {
    for (i = 0; i < 100; i++) {
      if (i == 50) {
        printf("1 ");
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
  return 0;
}