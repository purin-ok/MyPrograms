#include "NAbasic.h"

// 関数
double fxy(double x, double y) {
	return (-x * y + x);
}

// ホイン法
void heun_mh(double x0, double st, double xe, double y0) {
	double x, y;

	printf("STEP:%lf\nAnswer\n", st);
	printf("x=%lf, y=%lf\n", x0, y0);

	while (x < xe) {
		x += st;
		y = y0 + st / 2.0 * (fxy(x0, y0) + (-x * (y0 + st * fxy(x0, y0)) + x));
		printf("x=%lf, y=%lf\n", x, y);
		x0 += st;
		y0 = y;
	}
}

int main(void) {
	FILE *fp;
	double **data;
	double x0, st, xe, y0;
	int row, col;
	char file_name[256];

	// CSVから対象データを読み込む
	printf("csvファイルを入力してください:");
	scanf("%s", file_name);
	putchar('\n');
	if((fp = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

	data = csvRead(&row, &col, fp);

	// 各値代入
	x0 = data[0][0];	// xの初期値
	st = data[0][1];	// ステップ幅
	xe = data[0][2];	// xの最終値
	y0 = data[0][3];	// yの初期値

	// ホイン法
	heun_mh(x0, st, xe, y0);
	
	// ファイル, メモリ開放
	fclose(fp);
	freeMatrix(data);

	return 0;
}