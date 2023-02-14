#include "NAbasic.h"

//IEEE754形式に変換して出力
void IEEE754_conversion(char *c)
{
	int i, j, k;

	printf("sEEEEEEE EEEEdddd dddddddd... \n");

	for (i = sizeof(double) - 1; i >= 0; i--)
	{
		for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--)
		{
			k = c[i] & (1 << j);
			printf("%d", k ? 1 : 0);
		}
		printf(" ");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	FILE *fin;
	double **matrix;
	int row, col;

	char c[sizeof(double)];

	//コマンドラインの処理
	if (argc != 2) {
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	//csvファイルからデータを読み込む
	matrix = csvRead(&row, &col, fin);

	//1つ目の数値をコピー
	memcpy(c, &matrix[0][0], sizeof(double));

	IEEE754_conversion(c);

	return 0;
}