#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define f(x) (x)*(x)


int main(int argc, char* argv[]) {

	FILE *fin;
	char file_name[256];

	double **a;
	int row, col, a_0, i;
	double a_1, a_2, Area = 0, h;
	
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
	a = csvRead(&row, &col, fin);
	a_0 = a[0][0];
	a_1 = a[0][1];
	a_2 = a[0][2];
	
	Area = f(a_1) + f(a_2);

	h = (a_2 - a_1) / a_0;
	
	for (i = 1; i <= a_0 - 1; i++) {
		Area += 2 * f(h * i + a_1);
	}

	Area = Area * h / 2.0;

	printf("Result : %.10f\n", Area);

	return EXIT_SUCCESS;
}