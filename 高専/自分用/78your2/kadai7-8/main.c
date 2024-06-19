//反復法によって最大固有値と最小固有値を求めるプログラム

#include<math.h>
#include "NAbasic.h"

#define EPSILON 1.0e-8          //打ち止め誤差
#define ROW 10
#define LOOPLIMIT 150           //反復上限

//プロトタイプ宣言
int findPivot(double **matrix, int top, int row);                                                               //ピボットを見つける
void swapLine(double **matrix1, int pivot, int top, int row, int col);                                          //入れ替える
void erase(double **matrix, int pivot, int row, int col);                                                       //前進消去
double *calcProduct(double **matrix, double *vector, int row, int col);                                         //行列×ベクトル
void setDiagonalMatrix(double **matrix, int row, int col);                                                      //対角成分を1にする
double calcInnerProduct(double *vector1, double *vector2, int row);                                             //内積求める
void forwardSubstitution(double **matrixL, double *y, double *Pb, int row);                                     //前進代入
void backSubstitution(double **matrixU, double *x, double *y, int row);                                         //後退代入
int normalize(double *vector, int row);                                                                         //正規化

void generateLU(double **matrixL, double **matrixU, double **matrixA, double **matrixP, int row, int col);      //LU分解
double calcMaxEigenvalue(double **matrixA, int row);                                                            //最大固有値
double calcMinEigenvalue(double **matrixInverseA, double **matrixL, double **matrixU, int row);                 //最小固有値

int main(int argc, char **argv) {
    FILE *fp;          
    double **a, **l, **u, **p;  //行列       
    double maxLambda, minLambda;          
    int row, col;               //行、列

    //ファイルオープン、csvファイル読込
    if (argc != 2) {
        fprintf(stderr, "コマンドライン引数が不足しています\n");
        return EXIT_FAILURE;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
       	fprintf(stderr, "ファイル名: %s が開けませんでした\n", argv[1]);
        return EXIT_FAILURE;
    }
    //行列、ベクトル分のメモリ確保、表示
    a = csvRead(&row, &col, fp);
    l = allocMatrix(row, col);
    u = allocMatrix(row, col);
    p = allocMatrix(row, col);
    printf("A行列:\n");
    showMatrix((const double**)a, row, col);

    //L行列、U行列を生成する
    generateLU(l, u, a, p, row, col);
    printf("L行列:\n");
    showMatrix((const double**)l, row, col);
    printf("U行列:\n");
    showMatrix((const double **)u, row, col);

    //最大固有値、最小固有値を求める
    maxLambda = calcMaxEigenvalue(a, row);
    minLambda = calcMinEigenvalue(a, l, u, row);
    printf("最大固有値:%lf\n最小固有値:%lf\n", maxLambda, minLambda);

    //メモリ開放・ファイルクローズ
    freeMatrix(a);
    freeMatrix(l);
    freeMatrix(u);
    freeMatrix(p);
    fclose(fp);
    return EXIT_SUCCESS;
}

/*---------------------------------------------------
ピボットの行を見つける関数
引数:行列、始点の行、行数
戻り値:ピボットが存在する行
---------------------------------------------------*/
int findPivot(double **matrix, int top, int row) {
    int max = top;

    for (int i = top; i < row; i++) {     //始点から終点まで絶対値を比較
        if(fabs(matrix[max][top]) < fabs(matrix[i][top])) {
            max = i;
        }
    }
    return max;
}
/*---------------------------------------------------
行を入れ替える関数
引数:行列、ピボット、先頭の行、行数、列数
戻り値:なし
---------------------------------------------------*/
void swapLine(double **matrix1, int pivot, int top, int row, int col) {  
    double **temp = allocMatrix(row, col);
   
    for (int i = 0; i < col; i++) { //ピボットの行を先頭と入れ替える
        temp[0][i] = matrix1[top][i];
        matrix1[top][i] = matrix1[pivot][i];
        matrix1[pivot][i] = temp[0][i];
    }
    freeMatrix(temp);
}
/*---------------------------------------------------
前進消去をする関数
引数:係数行列、ピボット、行数、列数
戻り値:なし
---------------------------------------------------*/
void erase(double **matrix, int pivot, int row, int col) {
    double element;  //消去する要素を入れておく変数

    for (int i = pivot + 1; i < row; i++) { //ピボットの行より後ろの行について処理を行う
        element = matrix[i][pivot];     //要素を保存  
        for(int j = pivot; j < col; j++) {  //左辺の各成分について計算
            matrix[i][j] = matrix[i][j] - ((element * matrix[pivot][j]) / matrix[pivot][pivot]);
        }
    }
}
/*---------------------------------------------------
行列とベクトルの積を求める
引数:行列、ベクトル、行数、列数
戻り値:計算結果(行列)
---------------------------------------------------*/
double *calcProduct(double **matrix, double *vector, int row, int col) {
    double *answer = allocVector(row);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            answer[i] += matrix[i][j] * vector[j];
        }
    }
    return answer;
}
/*---------------------------------------------------
n行n列の対角成分が1の対角行列を生成する関数
引数:行列、行数、列数
戻り値:なし
---------------------------------------------------*/
void setDiagonalMatrix(double **matrix, int row, int col) {
    int i;
        for(i = 0; i < row; i++) {
            matrix[i][i] = 1;           //対角成分に1を代入   
        }
}
/*---------------------------------------------------
内積を求める関数
引数:ベクトル2つ、行数
戻り値:内積の値
---------------------------------------------------*/
double calcInnerProduct(double *vector1, double *vector2, int row) {
    double innerProduct = 0;

    for (int i = 0; i < row; i++) {
        innerProduct +=  vector1[i] * vector2[i];
    }
    return innerProduct;
}
/*---------------------------------------------------
LU行列を求める関数
引数:L行列、U行列、A行列、P行列、行数、列数
戻り値:なし
---------------------------------------------------*/
void generateLU(double **matrixL, double **matrixU, double **matrixA, double **matrixP, int row, int col) {
    int pivot;
    int i, j;
    double temp; 

    //P行列
    setDiagonalMatrix(matrixP, row, col);

    //U行列
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixU[i][j] = matrixA[i][j];
        }
    }
    for(int k = 0; k < row -1; k++){
        pivot = findPivot(matrixU, k, row);            
        swapLine(matrixU, pivot, k, row, col);              
        swapLine(matrixA, pivot, k, row, col);
        swapLine(matrixP, pivot, k, row, col);  
                      
        erase(matrixU, k, row, col);                        
    }

    //L行列
    setDiagonalMatrix(matrixL, row, col);       //対角成分を1にする
    for (i = 0; i < row; i++) {           
        temp = 0;
        for (j = 0; j < i; j++) {        
                matrixL[i][j] = (matrixA[i][j] - temp) / matrixU[j][j];     //左辺の結果(temp)を右辺に移項して係数Uで割る
                temp += matrixL[i][j] * matrixU[j][j + 1];
        }
    }
}
/*---------------------------------------------------
前進代入をする Lz=y
引数:L行列、zベクトル、yベクトル、行数
戻り値:なし
---------------------------------------------------*/
void forwardSubstitution(double **matrixL, double *z, double *y, int row) {
	for (int i = 0; i < row; i++) {
        z[i] = y[i] / matrixL[i][i];
		for (int j = 0; j < i; j++) {
			z[i] -= z[j] * matrixL[i][j] / matrixL[i][i];
		}
        
	}
}
/*---------------------------------------------------
後退代入をする
引数:U行列、xベクトル、yベクトル、行数
戻り値:なし
---------------------------------------------------*/
void backSubstitution(double **matrixU, double *x, double *y, int row) {
	for (int i = (row - 1); i >= 0; i--) {
        x[i] = y[i] / matrixU[i][i];
		for (int j = (row - 1); j > i; j--) {
			x[i] -= x[j] * matrixU[i][j] / matrixU[i][i];
		}
	}
}
/*---------------------------------------------------
ベクトルを単位ベクトルに正規化する
引数: ベクトル、次数
戻り値: 成功したら0, 失敗したら1
---------------------------------------------------*/
int normalize(double *vector, int row) {
	double norm = 0; // ベクトルのノルム
	int i;

	// ベクトルのノルム計算
	for (i = 0; i < row; i++) {
		norm += vector[i] * vector[i];
	}

	norm = sqrtf(norm);

	if (norm == 0) {        //0ベクトル判定
		puts("正規化できませんでした\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i < row; i++) {
		vector[i] /= norm;           // 各要素をノルムで割る
	}

	return EXIT_SUCCESS;
}
/*---------------------------------------------------
最大固有値を求める関数
引数:A行列、行数
戻り値:最大固有値
---------------------------------------------------*/
double calcMaxEigenvalue(double **matrixA, int row) {
    double lambdaPrev, lambda = 0;
    double yPrev[ROW];
    double *y = allocVector(row);
    int count = 0;

    printf("最大固有値:");
    for (int i = 0; i < row; i++) {
        y[i] = 100.0;       //適当な値を代入
    }

    do {
        memcpy(yPrev, y, sizeof(double) * row);     //1つ前のyにコピー
        y = calcProduct(matrixA, y, row, row);      
        lambdaPrev = lambda;
        lambda = calcInnerProduct(y, y, row) / calcInnerProduct(y, yPrev, row); //内積による固有値計算
        normalize(y, row);
        count++;
    }while((fabs(lambda - lambdaPrev) / fabs(lambda) > EPSILON) && (count < LOOPLIMIT));       //いずれかを満たさなければ抜ける
    
    printf("反復回数は%d回\n", count);
    freeVector(y);
    return lambda;
}
/*---------------------------------------------------
最小固有値を求める関数
引数:A行列、L行列、U行列、行数
戻り値:最小固有値
---------------------------------------------------*/
double calcMinEigenvalue(double **matrixA, double **matrixL, double **matrixU, int row) {
    double lambdaPrev, lambda = 0;
    double yPrev[ROW];
    double *y = allocVector(row);
    double *z = allocVector(row);
    int count = 0;

    printf("最小固有値:");
    for (int i = 0; i < row; i++) {
        y[i] = 100.0;           //適当な値を代入
    }

    do{
        memcpy(yPrev, y, sizeof(double) * row);
        forwardSubstitution(matrixL, z, yPrev, row);
        backSubstitution(matrixU, y, z, row);
        lambdaPrev = lambda;
        lambda = calcInnerProduct(y, yPrev, row) / calcInnerProduct(y, y, row);
        normalize(y, row);
        count++;
    }while((fabs(lambda - lambdaPrev) / fabs(lambda) > EPSILON) && (count < LOOPLIMIT));

    printf("反復回数は%d回\n", count);
    freeVector(y);
    return lambda;
}



