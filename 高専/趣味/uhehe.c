#include <stdio.h>
int aa(int a) {
  int r = 0, u;
  r = a;
  r++;
  printf("%d,%d\n", a, &a);
  if (a > 4) return 0;
  u = aa(r);
  printf("%d,%d\n", a, &a);
  return a;
}

int main() {
  int a;
  a = aa(1);
  printf("%d", a);
  return 0;
}