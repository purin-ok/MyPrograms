#include <math.h>
#include "NAbasic.h"

//関数
#define f(x) (x * x)

//分割数K，規定値
#define N 5
#define EPS (exp(x) - x*x*x + 5*sin(x))

//台形公式  ( 分割数a0, 積分範囲[a1, a2] )
void trapezoid(double a0, double a1, double a2){
	double k, h, sum = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += h){
		sum += f(k);
	}

	printf("%f\n", (h / 2.0) * (f(a1) + f(a2) + (2.0 * sum)));
}

//シンプソン公式
void simpson(double a0, double a1, double a2){
	double k, h, sum1 = 0, sum2 = 0;

	h = (a2 - a1) / a0;

	for(k = a1 + h; k < a2; k += h){
		sum1 += f(k);
		k += h;
		if(k < a2) sum2 += f(k);
	}

	printf("%f\n", (h / 3.0) * (f(a1) + f(a2) + (4.0 * sum1) + (2.0 * sum2)));
}

//ロンバーグ法
void romberg(double a1, double a2){
	int i, k, m;
	double h, sum, T[N + 1][N + 1];

	//2^0 = 1分割の台形公式
	h = a2 - a1;
	T[0][0] = h * (f(a1) + f(a2)) / 2;
	
	for(k = 1; k <= N; k++) {
		h /= 2;

		for(i = 1, sum = 0; i <= pow(2, (k - 1)); i++){
			sum += f(a1 + (2 * i - 1) * h);
		}
		T[k][0] = T[k - 1][0] / 2.0 + h * sum;

		for(m = 1; m <= k; m++){
			T[k][m] = T[k][m - 1] + (T[k][m - 1] - T[k - 1][m - 1]) / (pow(4, m) - 1);
			//収束判定
			//if(fabs(T[k][m] - T[k][m - 1]) < EPS) break;
		}

		//収束判定
		//if(fabs(T[k][0] - T[k - 1][0]) < EPS) break;
	}

	//printf("分割数：%d, 次数：%d\n", (int)pow(2, k), (int)pow(2, m));
	printf("%f\n", T[k - 1][m - 1]);	
}

int main(int argc, char **argv){
	FILE *fin;
	double a0, a1, a2;
	double **a;
	int arow, acol, i;

	//コマンドラインの処理
	if(argc != 2){
		fprintf(stderr, "コマンドラインが不正です．\n");
		return EXIT_FAILURE;
	}

	//aのcsvファイル読み込み
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "ファイルが存在しません．\n");
		return EXIT_FAILURE;
	}

	//csvからデータを読み込み
	a = csvRead(&arow, &acol, fin);

	if (1 != arow) {
		puts("入力が不適です．\n");
		return EXIT_FAILURE;
	}

//	a0 = a[0][0];
//	a1 = a[0][1];
//	a2 = a[0][2];

	a1 = a[0][0];
	a2 = a[0][1];

//	for(i = 1; i < 101; i++){
//		trapezoid(i, a1, a2);
//	}

//	for(i = 2; i < 101; i+=2){
//		simpson(i, a1, a2);
//	}

//	for(i = 1; i < 11; i++){
//		romberg(i, a1, a2);
//	}

	romberg(a1, a2);

	return EXIT_SUCCESS;
}