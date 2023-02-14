/*最大固有値と最小固有値を計算*/
#include <math.h>
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*絶対値関数*/
#define EPS 10e-9

/*行列の要素が同じ新たな行列を返す関数*/
double** copyMatrix(double **matrix,int row,int col){
  int i,j;
  double **newMatrix;
  newMatrix = allocMatrix(row,col);

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      newMatrix[i][j] = matrix[i][j];
    }
  }

  return newMatrix;
}

/*行の入れ替えを行う関数*/
void swap(double **matrix,int row,int i,int pivot){
  double *tmp_vec = matrix[pivot];

  if(!(((0<=i)&&(i<row))&&((0<=pivot)&&(pivot<row)))){
    fprintf(stderr, "行の交換に失敗しました\n");
    exit(EXIT_FAILURE);
  }

  matrix[pivot] = matrix[i];
  matrix[i] = tmp_vec;
}

/*行列積を計算する関数*/
double** dot(double **A,int Arow,int Acol, double **B, int Brow, int Bcol){
	int i,j,k;
	double **result;

	/*計算可能かを判定*/
	if(Acol != Brow){
		printf("計算できません");
		exit(EXIT_FAILURE);
	}

	/*2次元配列を用意*/
	result = allocMatrix(Arow,Bcol);

	/*行列を計算*/
	for(i=0;i<Arow;i++){
		for(j=0;j<Bcol;j++){
			result[i][j]=0;
			for(k=0;k<Acol;k++){
				result[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	return result;
}

/*前進代入*/
double** foward(double **L, double **Pb,int size){
  int i,j;
  double **y;
  y = allocMatrix(size,1);

  for(i=0;i<size;i++){
    y[i][0] = Pb[i][0]/L[i][i];
    for(j=0;j<i;j++){
      y[i][0] -= y[j][0]*L[i][j]/L[i][i];
    }
  }

  return y;
}

/*後退代入*/
double** backward(double **U,double **y,int size){
  int i,j;
  double **x;
  x = allocMatrix(size,1);

  for(i=size-1;i>=0;i--){
    x[i][0] = y[i][0]/U[i][i];
    for(j=i+1;j<size;j++){
      x[i][0] -= x[j][0]*U[i][j]/U[i][i];
    }
  }
  return x;
}

/*LU分解*/
void LU_decomposition(
  double **A,
  double **L,
  double **U,
  double **P,
  int size
){
  int i,j,k,pivot;
  double tmp,a;

  for(i=0;i<size;i++){
    /*ピポットを選択*/
		pivot = i;
    for(j=i;j<size;j++){
			if(ABS(A[j][i]) > ABS(A[pivot][i])){
				pivot = j;
			}
		}
    /*A,Pの行の入れ替え*/
    swap(A,size,i,pivot);
    swap(P,size,i,pivot);

    /*Lの計算した部分を入れ替える*/
    for(j=0;j<i;j++){
      tmp = L[pivot][j];
      L[pivot][j] = L[i][j];
      L[i][j] = tmp;
    }

    for(j = i + 1;j<size;j++){
      if(ABS(A[i][i]) < 1.0e-6){
        fprintf(stderr, "LU分解に失敗\n");
        exit(EXIT_FAILURE);
      }

      L[j][i] = A[j][i]/A[i][i];
      /*前進消去*/
      a = A[j][i]/A[i][i];
  		for(k=i;k<size;k++){
        A[j][k] -= a*A[i][k];
  		}
    }

    /*Uを更新*/
    for(j=i;j<size;j++){
      U[i][j] = A[i][j];
    }
  }
}

/*matrixの逆行列とベクトルbの積を計算する*/
double** dotInverseMatrix(double **matrix,int Arow,int Acol,double **b, int brow, int bcol){
  int i,j;
  double **A,**L,**U,**P,**z,**Pb,**result;

  if((Acol!=Arow)||(Acol!=brow)||(bcol!=1)){
    fprintf(stderr, "逆行列とベクトルの積の計算に失敗\n");
		exit(EXIT_FAILURE);
  }

  /*行列をコピー*/
  A = copyMatrix(matrix,Arow,Acol);

  /*L,U,Pの行列と結果格納用の配列を用意*/
  L = allocMatrix(Arow,Acol);
  U = allocMatrix(Arow,Acol);
  P = allocMatrix(Arow,Acol);
  result = allocMatrix(bcol,1);

  /*L,U,Pを単位行列で初期化*/
  for(i=0;i<Arow;i++){
    for(j=0;j<Acol;j++){
      U[i][j] = L[i][j] = P[i][j] = (i==j) ? 1 : 0;
    }
  }

  /*LU分解*/
  LU_decomposition(A,L,U,P,Acol);

  /*解を計算*/
  Pb  = dot(P,Arow,Acol,b,brow,bcol);
  z = foward(L,Pb,Arow);
  result = backward(U,z,Arow);

  /*メモリを格納*/
  freeMatrix(A);
  freeMatrix(L);
  freeMatrix(U);
  freeMatrix(P);
  freeMatrix(z);
  freeMatrix(Pb);

  return result;
}

/*L2ノルムを計算する関数*/
double L2_norm(double **vec,int row,int col){
	int i;
	double norm = 0;

	/*列ベクトルか確認*/
	if(col!=1){
		fprintf(stderr, "L2ノルムの計算に失敗\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<row;i++)	norm += vec[i][0]*vec[i][0];
	return sqrt(norm);
}

/*ベクトルの大きさを1に正規化する関数*/
void normalizeVector(double **vector,int row,int col){
  int i;
  double norm;
  if(col!=1){
    fprintf(stderr,"ベクトルのノルム計算に失敗\n");
    exit(EXIT_FAILURE);
  }

  norm = L2_norm(vector,row,col);
  for(i=0;i<row;i++) vector[i][0] /= norm;
}

/*内積を計算する関数*/
double inner_product(double **a,int arow,int acol,double **b,int brow,int bcol){
  double result;
  double **matrix,**aT;
  /*内積が計算可能か調べる*/
  if((acol!=1)||(bcol!=1)||(arow!=brow)){
    fprintf(stderr, "内積を計算できません\n");
    //exit(EXIT_FAILURE);
  }

  /*行列aを転置*/
  aT = tpMatrix((const double**)a,arow,acol);

  /*行列の積を計算*/
  matrix = dot(aT,acol,arow,b,brow,bcol);

  result = matrix[0][0];
  freeMatrix(aT);
  freeMatrix(matrix);

  return result;
}

/*最大固有値を計算する関数*/
double calcMaxEigen(double **matrix,int row,int col){
  int i;
  double lambda1=0,lambda2=0;
  double **y[2];
  /*列ベクトルを2つ用意する*/
  y[0] = allocMatrix(row,1);
  y[1] = allocMatrix(row,1);
  /*列ベクトルの初期化*/
  for(i=0;i<row;i++) y[0][i][0] = 1.0;

  i = 0;
  while((i<2)||(ABS((lambda2 - lambda1)/lambda1) > EPS)){
    lambda1 = lambda2;
    normalizeVector(y[i%2],row,1);  /*ベクトルの正規化*/
    y[(i+1)%2] = dot(matrix,row,col,y[i%2],row,1);  /*行列を一度掛ける*/

    /*ラムダを計算*/
    lambda2 = inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1)
      /inner_product(y[(i+1)%2],row,1,y[i%2],row,1);

    i++;
  }

  /*メモリの開放*/
  freeMatrix(y[0]);
  freeMatrix(y[1]);

  return lambda2;
}

/*最小固有値を計算*/
double calcMinEigen(double **matrix,int row,int col){
  int i;
  double lambda1=0,lambda2=0;
  double **y[2];
  /*列ベクトルを2つ用意する*/
  y[0] = allocMatrix(row,1);
  y[1] = allocMatrix(row,1);

  /*列ベクトルの初期化*/
  for(i=0;i<row;i++) y[0][i][0] = 1.0;

  i = 0;
  while((i<2)||(ABS((lambda2 - lambda1)/lambda1) > EPS)){
    lambda1 = lambda2;
    normalizeVector(y[i%2],row,1);  /*ベクトルの正規化*/
    y[(i+1)%2] = dotInverseMatrix(matrix,row,col,y[i%2],row,1); /*逆行列を一度掛ける*/

    /*ラムダを計算*/
    double a,b;
    a = inner_product(y[(i+1)%2],row,1,y[i%2],row,1);
    b = inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1);
    printf("%f/%f\n",a,b);
    lambda2 = a/b;
    /*
    lambda2 = inner_product(y[(i+1)%2],row,1,y[i%2],row,1)
      /inner_product(y[(i+1)%2],row,1,y[(i+1)%2],row,1);
    */
    i++;
  }
  /*メモリの開放*/
  freeMatrix(y[0]);
  freeMatrix(y[1]);

  return lambda2;
}


int main(int argc, char ** argv){
	FILE *f;
	int row,col;
  double max_lambda,min_lambda;
	double **matrix;

	/*コマンドライン引数の確認*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s matrix_CSV \n", argv[0]);
		return EXIT_FAILURE;
	}

	/*行列のCSVファイルの読み込み*/
	if((f  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}

  /*入力を格納*/
	matrix = csvRead(&row,&col,f);

  /*正方行列かどうか確認*/
  if(col != row){
    fprintf(stderr, "入力が正方行列ではありません.\n");
		return EXIT_FAILURE;
  }

  /*最大&最小固有値を計算*/
  max_lambda = calcMaxEigen(matrix,row,col);
  min_lambda = calcMinEigen(matrix,row,col);

  /*出力*/
  printf("最大固有値:%f\n",max_lambda);
  printf("最小固有値:%f\n",min_lambda);

  /*メモリの開放*/
  freeMatrix(matrix);
  free(f);

  return 0;
}
