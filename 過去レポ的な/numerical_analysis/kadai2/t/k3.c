#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NAbasic.h"

/* 関数f(x)の定義 */
double f(double x){
    return x*x*x*x - 3*x*x + 5*x -9;
}

/* 関数f(x)をxで微分した、関数f'(x)の定義 */
double df(double x){
    return 4*x*x*x - 6*x + 5;
}

int main(int argc, char **argv){
    int i = 0;
    int row, col;
    double ah, a, b, c, s;
    double **matrix;
    FILE *fin;

    /* 適切なコマンドライン引数が与えられていないときに警告する。 */
    if(argc != 2){
        fprintf(stderr, "Usage: %s difficult\n", argv[0]);
        return EXIT_FAILURE;
    }
    if((fin = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "File: %s cannot open\n", argv[1]);
        return EXIT_FAILURE;
    }

    matrix = csvRead(&row, &col, fin); /* データ読み込み */

    /* 範囲はaからbまで */
    a = matrix[0][0];  
    b = matrix[0][1];
    /* ニュートン法の初期値 */
    c = (a + b)/2.0;

    /* 2分法で解を求める。10回目まで繰り返しながら解を表示する。 */
    while(i<10){
        i++;
        s = (a+b)/2.0;
        if((f(s) * f(a))<0) b=s;
        else a = s;
        printf("2分法の解 : %f(繰り返し回数%d 回)\n", s, i);
    }

    i = 0;  /* iの値をリセット */
 
    /* ニュートン法で解を求める。10回目まで繰り返しながら解を表示する。 */
    while(i<10){
        i++;
        ah = c - f(c)/df(c);
        c = ah;
        printf("ニュートン法の解 : %f(繰り返し回数%d 回)\n", c, i);
    }

    freeMatrix(matrix); /* きちんと後処理をする。 */

    return EXIT_SUCCESS;
}