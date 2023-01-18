#include <stdio.h>
#include <math.h>
#include "NAbasic.h"

#define fmax 100                 //繰り返し最大回数
#define eps 1.0e-5              //最小誤差許容範囲

int main(int argc, char **argv)
{ 
 FILE *fin; 
 double **matrix1, **matrix2;	/*配列matrix1,matrix2には係数の値等を。*/
 int row, col; 
 
 char c[sizeof(double)]; 
 int i, j, k, n;
 double err;
 
 /* CSVから対象データを読み込む */ 
if (argc != 3) {
	fprintf(stderr, "Usage: %s decimal data \n", argv[0]); /* 不適切な入力がされたときに警告する */
	return EXIT_FAILURE;
}
if ((fin = fopen(argv[1], "r")) == NULL) { /* readモードでテキストファイルを開く */
	fprintf(stderr, "File: %s cannot open\n", argv[1]);
	return EXIT_FAILURE;
}
matrix1 = csvRead(&row, &col, fin); /* csvファイル1を読み込みmatrix2に格納する。 NAbasicで関数定義 */

if ((fin = fopen(argv[2], "r")) == NULL) { /* readモードでテキストファイルを開く */
	fprintf(stderr, "File: %s cannot open\n", argv[2]);
	return EXIT_FAILURE;
}
matrix2 = csvRead(&row, &col, fin); /* csvファイル2を読み込みmatrix2に格納する。 NAbasicで関数定義 */

/*ヤコビ法*/

/*配列xoldには適当に決めた解の値を入れておく*/
double xold[row],xnew[row];

for(n =0; n<row; n++){
	xold[n] = 1.0;
}

for(k=0;k<fmax;k++) {
	err=0.0;	//誤差のリセット
	for(i=0;i<row;i++) {
		xnew[i]=matrix2[i][0];
		for(j=0;j<n;j++) {
			if(j!=i) {
				xnew[i]-=matrix1[i][j]*xold[j];
			}
		}
		xnew[i]=xnew[i]/matrix1[i][i];
	}
/*各解の誤差を足し、古い解は捨て配列xoldに新しい解を入れる*/
	for(i=0;i<n;i++) {
		err+=fabs(xold[i]-xnew[i]);
		xold[i]=xnew[i];
	}
/*足しあわされた誤差が許容範囲内だったら
計算終了とし解が求まったとする*/
	if(err<eps) break;
}

/*求まった解を出力する*/
printf("ヤコビ法による解は\n");
for(i=0;i<n;i++) {
	printf("%8.4f\n",xnew[i]);
}

/*繰り返し回数が最大回数の値だったら
正確な解が求まっていない可能性大なので注意*/
printf("繰り返し回数は %d\n",k+1);

/*ガウスザイデル法*/

double xn = 0.0, dx, absx, sum;

k = 1;
for(n =0; n<row; n++){
	xnew[n] = 1.0;
}

do{	// 反復計算のループ
	dx = 0.0;
	absx = 0.0;
	k++;
	for(i=0; i<row; i++){
		sum = 0;
		for(j=0; j<row; j++){
			if(i != j){
				sum+=matrix1[i][j]*xnew[j];
			}
		}
		xn = 1.0/matrix1[i][i]*(*matrix2[i] - sum);	// 反復計算後の近似解
		dx += fabs(xn-xnew[i]);	// 近似解の変化量を加算
		absx += fabs(xn);	// 近似解の総和計算
		xnew[i] = xn;	// 新しい近似解を代入
	}
}while(dx/absx > eps);	// 計算終了条件

/*求まった解を出力する*/
printf("ガウス・ザイデル法による解は\n");
for(i=0; i<row; i++){
	printf("%8.4f\n",xnew[i]);
}
printf("繰り返し回数は %d\n",k);

	return 0;
}
