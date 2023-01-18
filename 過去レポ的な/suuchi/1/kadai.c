#include <stdio.h>

#include "NAbasic.h"

// IEEE754形式に変換して出力
// sample.cを参考に作成
void output(char* c) {
  int i, j, k;

  printf("sEEEEEEE EEEEdddd dddddddd...\n");

  for (i = sizeof(double) - 1; i >= 0; --i) {
    for (j = sizeof(c[i]) * 8 - 1; j >= 0; --j) {
      k = c[i] & (1 << j);
      printf("%d", k ? 1 : 0);
    }
    printf(" ");
  }
}

int main(int argc, char* argv[]) {
  FILE* fin;
  double** matrix;
  int row, col;
  char c[sizeof(double)], file_name[256];

  // csvファイルの入力
  printf("ファイル名を入力してください：");
  scanf("%s", file_name);
  putchar('\n');

  // csvファイル読み込み
  if ((fin = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "ファイルが存在しません.\n");
    return EXIT_FAILURE;
  }

  // csvからデータを読み込み
  matrix = csvRead(&row, &col, fin);

  // 一つ目の数値を文字列にコピー
  memcpy(c, &matrix[0][0], sizeof(double));

  // 出力
  output(c);

  return EXIT_SUCCESS;
}