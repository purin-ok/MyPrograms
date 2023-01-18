/*関数の最小二乗近似*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*絶対値関数*/

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

double** calcLeft(double **matrix,int row,int col,int n){
	int i,j;
  double sum;
	double *x;
	double **L;
	x = allocVector(row);
	L = allocMatrix(n,1);

	/*xとLの要素を初期化する*/
	for(i=0;i<row;i++)  x[i] = 1.0;

	for(i=0;i<n;i++){
    sum = 0;
		for(j=0;j<row;j++){
			sum += matrix[j][1]*x[j];
			x[j]*=matrix[j][0];
		}
    L[i][0] = sum;
	}

	free(x);

	return L;
}

double** calcRight(double **matrix,int row,int col,int n){
	int i,j,k;
  double sum;
  double *x,*xn;
	double **R;
  x = allocVector(row);
  xn = allocVector(row);
	R = allocMatrix(n,n);

  /*xの要素をすべて1にする*/
	for(i=0;i<row;i++) x[i] = xn[i] = 1.0;


	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
      sum = 0;
			for(k=0;k<row;k++){
				sum += x[k]*xn[k];
        xn[k]*=matrix[k][0];
			}
      R[i][j] = R[j][i] = sum;
		}

    for(k=0;k<row;k++){
      x[k]*=matrix[k][0];
      xn[k] = x[k];
    }
	}

	free(x);
  free(xn);

	return R;
}

double** calcParams(double **matrix,int row, int col,int n){
	double **L,**R,**a;
  L = calcLeft(matrix,row,col,n);/*線形近似の式の左辺を計算*/
  R = calcRight(matrix,row,col,n);/*線形近似の式の右辺を計算*/

  a = dotInverseMatrix(R,n,n,L,n,1);

  freeMatrix(L);
  freeMatrix(R);
  return a;
}

void plot_graph(double **A,int row,int col,double **a,int n){
    int i;
    double min=10e10,max=-10e10;

    /*xの最大値と最小値を求める*/
    for(i=0;i<row;i++){
      if(A[i][1] > max) max =  A[i][1];
      if(A[i][1] < min) min =  A[i][1];
    }

    /*係数の小数点以下第3位を四捨五入*/
    for(i=0;i<n;i++){
      a[i][0] = (double)((int)(a[i][0]*100+0.5)*0.01);
    }

    FILE *pOut = popen("gnuplot","w");
    fprintf(pOut, "set zeroaxis\n");
    fprintf(pOut, "set xrange [%f:%f]\n",min-0.5,max+0.5);
    fprintf(pOut, "plot");
    for(i=n;i>0;i--)
      fprintf(pOut, "%2.2f*x**%d +",a[i][0],i);
    fprintf(pOut, "%2.2f*x**%d\n",a[i][0],i);

    fprintf(pOut, "replot'-'title'data'\n");
    for(i=0;i<=row;i++){
      fprintf(pOut, "%f\t%f\n",A[i][0],A[i][1]);
    }
    fprintf(pOut, "e\n");
    fflush(pOut);

    printf("please enter key to terminate program\n");
    getchar();
    pclose(pOut);
}

int main(int argc, char ** argv){
  int degree;
	FILE *f;
	int row,col;
	double **matrix,**a;

	/*コマンドライン引数の確認*/
	if(argc != 2){
		fprintf(stderr,"Usage: %s matrix_CSV\n", argv[0]);
		return EXIT_FAILURE;
	}

	/*行列のCSVファイルの読み込み*/
	if((f  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	matrix = csvRead(&row,&col,f);

	/*入力をチェック*/
	if(col != 2){
		fprintf(stderr, "入力が違います\n");
		return 0;
	}

  /*入力を要求*/
  printf("次数を入力:");
  scanf("%d",&degree);

	/*線形近似のための行列を求める*/
  a = calcParams(matrix,row,col,degree+1);

  showMatrix((const double**)a,3,1);

  plot_graph(matrix,row,col,a,degree);

}
