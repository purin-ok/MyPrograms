#include "NAbasic.h"
#include <math.h>
#include <stdio.h>


double f(double x, double y) {//傾きの計算
	return -x * y + x;
}

void Runge(double x, double h, double e, double y0) {//ルンゲクッタ法
	double k[10] = { 0 }, y[100];
	int i = 0, j;

	y[0] = y0;

	printf("STEP:%f\nAnswer\n", h);

	for (; x <= e; x += h) {
		printf("x=%f,y=%f\n", x, y[i]);//解の表示
		k[0] = h * f(x, y[i]);
		for (j = 0; j < 2; j++) k[j + 1] = h * f(x + h / 2, y[i] + k[j] / 2);
		k[3] = h * f(x + h, y[i] + k[2]);

		y[i + 1] = y[i] + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;

		i++;
	}
}


int main()
{
	FILE* fin = fopen("b.csv", "r");
	double** A, x0, h, e, y0;
	int row1, col1;

	A = csvRead(&row1, &col1, fin);//ファイルから入力を読みこむ
	x0 = A[0][0];
	h = A[0][1];
	e = A[0][2];
	y0 = A[0][3];

	Runge(x0, h, e, y0);//ルンゲクッタ法

	//メモリの開放
	freeMatrix(A);
	return 0;
}
