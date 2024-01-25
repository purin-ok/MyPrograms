#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR 10000
#define MOCOPI 27 * 6
int main() {
  int i = 0, j, k, frame;
  double time;
  double **data;
  // double data[410][MOCOPI];
  char tmp[STR], *tmp_tok;
  FILE *fp1, *fp2;
  char file_name[] = "Thand.BVH";
  char csv_name[] = "Thand1.csv";
  fp1 = fopen(file_name, "r");
  if (fp1 == NULL) {
    printf("%s file not open!\n", file_name);
    return -1;
  } else {
    printf("%s file opened!\n", file_name);
  }

  //	NULLポインタの終端までファイルから文字を1行ずつ読み込む
  while (fgets(tmp, STR, fp1) != NULL) {
    //	MOTIONという文字列が出るまでファイルポインタを進める．
    if (strcmp(tmp, "MOTION\n") == 0) break;
  }
  // 総フレーム数を読み込む
  if (fgets(tmp, STR, fp1) != NULL) {
    tmp_tok = strtok(tmp, ":");
    frame = atoi(strtok(NULL, "\n"));
    printf("%d\n", frame);  ///
  }

  // フレーム時間を読み込む
  if (fgets(tmp, STR, fp1) != NULL) {
    tmp_tok = strtok(tmp, ":");
    time = atof(strtok(NULL, "\n"));
    printf("%lf\n", time);  ///
  }

  // 動的に確保
  data = (double **)calloc(frame, sizeof(double *));
  for (i = 0; i < frame; i++) {
    data[i] = (double *)calloc(MOCOPI, sizeof(double));
  }
  i = 0;
  j = 1;
  //	NULLポインタの終端までファイルから文字を1行ずつ読み込む
  while (fgets(tmp, STR, fp1) != NULL) {
    tmp_tok = strtok(tmp, " ");
    data[i][0] = atof(tmp_tok);
    do {
      tmp_tok = strtok(NULL, " ");
      data[i][j] = atof(tmp_tok);
      j++;
    } while (j < MOCOPI);
    j = 1;
    i++;
  }

  fp2 = fopen(csv_name, "w");
  if (fp2 == NULL) {
    printf("%s file not open!\n", csv_name);
    return -1;
  } else {
    printf("%s file opened!\n", csv_name);
  }

  double lo = data[0][14] - data[0][18];
  printf("%f", lo);
  //////////////////////////////////////////////////////////////////
  // 出力
  for (i = 0; i < frame; i++) {
    for (j = 0; j < MOCOPI - 1; j++) {  // 関節数*チャンネル数
      fprintf(fp2, "%lf ,", data[i][j] / lo);
    }
    fprintf(fp2, "%lf\n", data[i][j] / lo);
  }

  fclose(fp1);
  fclose(fp2);
  return 0;
}