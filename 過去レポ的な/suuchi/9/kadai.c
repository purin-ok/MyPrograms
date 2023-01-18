#include "NAbasic.h"
#include <math.h>

int main(int argc,char **argv){
	FILE *fp;
	int row,col;
	int i,j;
	double **temp, **xy;
	double P,input,seki=1;

	if((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr,"File: %s cannot open\n",argv[1]);
	}

	puts("xの値を入力\n");
	scanf("%lf",&input);

	xy = csvRead(&row, &col, fp);//計測データを読み込んでおく行列
	temp = allocMatrix(row,row);
//3点を利用した補間によるyの値
	for(i = 0; i < row-1; i++){//差分商を計算し行列tempに代入
		for(j = 0; j < (row-i-1); j++){
			if(i == 0) temp[j][i] = xy[j][1];//1列目には対応するyの値がそのまま入る
			else temp[j][i] = (temp[j+1][i-1] - temp[j][i-1]) / (xy[j+i][0] - xy[j][0]);//2列目以降は差分商を計算
		}
	}

	P = temp[0][0];

	for(i = 1; i < (row - 1); i++){//式に基づき入力されたxの値に対応するyの値を計算
		for(j = 0; j < i; j++){
			seki = seki * (input - xy[j][0]);
		}
		P += seki * temp[0][i];
		seki = 1;
	}
	puts("3点を利用した補間によるyの値は\n");
	printf("%f\n",P);
//4点を利用した補間によるyの値
	for(i = 0; i < row; i++){
		for(j = 0; j < (row - i); j++){//増えたところだけ計算
			if(i == 0){
				if(j == (row - 1))temp[j][i] = xy[j][1];
			}else{
				if(j == (row - i - 1))temp[j][i] = (temp[j+1][i-1] - temp[j][i-1]) / (xy[j+i][0] - xy[j][0]);
			}
		}
	}

	for(j = 0; j < (row - 1); j++){
		seki = seki * (input - xy[j][0]);
	}
	P += seki * (temp[0][row-1]);//3点による補間のyの値に増えた分を加算

	puts("4点を利用した補間によるyの値は\n");
	printf("%f\n",P);

	freeMatrix(temp);
	freeMatrix(xy);
	fclose(fp);
	return EXIT_SUCCESS;
}