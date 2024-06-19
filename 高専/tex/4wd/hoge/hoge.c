#include <stdio.h>
int main() {
  int i;
  for (i = 0; i < 33; i++) {
    printf("    %d_x,", i);
    printf("    %d_y,", i);
    printf("    %d_z,", i);
  }
  return 0;
}