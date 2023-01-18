/*連立一次方程式の反復解法*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*絶対値関数*/
#define N1 80 /*Jacobi法の繰り返し回数*/
#define N 10 /*Gauss-Seidel法の繰り返し回数*/

/*ベクトルの要素を表示する関数*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%.6f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

/*Jacobi法*/
double* J_method(double **A,double *b,int size){
  int i,j,k;
  double L,R;
  double **x;
  x = allocMatrix(2,size);
  /*要素を0で初期化*/
  for(i=0;i<size;i++) x[0][i] = x[1][i] = 0;

  /*反復*/
  for(i=0;i<N1;i++){
    for(j=0;j<size;j++){
      L = R = 0;

      /*対角成分の左側*/
      for(k=0;k<j;k++){
        L += A[j][k]*x[i%2][k];
      }

      /*対角成分の右側*/
      for(k=j+1;k<size;k++){
        R += A[j][k]*x[i%2][k];
      }

      x[(i+1)%2][j] = (b[j] - L - R)/A[j][j];
    }
  }

  return x[i%2];
}

/*Gauss-Seidel法*/
double* GS_method(double **A,double *b,int size){
  int i,j,k;
  double L,R;
  double *x, *xn;
  x = allocVector(size);
  xn = allocVector(size);
  /*要素を0で初期化*/
  
  for(i = 0; i < N; i++)
  {
    xn[i] = b[i];
    for(j = 0; j < i-1; j++)
    {
	xn[i] -= A[i][j]*xn[j];
    }
    for(j = i+1; j < N; j++)
    {
        xn[i] -= A[i][j]*x[j];
    }
    xn[i] /= A[i][i];
	x[i] = xn[i];
	printf("%f", x[i]);
  }
  return x;
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int Arow,Acol,brow,bcol;
	double **A,**matrix;
	double *x,*b;

	/*コマンドライン引数の確認*/
	if(argc != 3){
		fprintf(stderr,"Usage: %s matrix_CSV vector_CSV \n", argv[0]);
		return EXIT_FAILURE;
	}

	/*行列のCSVファイルの読み込み*/
	if((f1  = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	A = csvRead(&Arow,&Acol,f1);

	/*ベクトルのCSVファイルの読み込み*/
	if((f2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	matrix = csvRead(&brow,&bcol,f2);

	/*ベクトルに直す*/
	if(bcol != 1){
		fprintf(stderr, "ベクトルが入力されていません.\n");
		return EXIT_FAILURE;
	}else{
		b = matrix2colVector((const double **)matrix,brow,bcol);
	}

	/*連立一次方程式となるか確認*/
	if((Acol != brow) && (Acol != Arow)){
		fprintf(stderr, "連立一次方程式となりません.\n");
		return EXIT_FAILURE;
	}

  /*Jacobi法で解を求める*/
  x = J_method(A,b,Arow);

  /*結果を表示*/
//  printf("Jacobi法(反復%d回)\n",N1);
//  showVector((const double *) x,Arow);

  /*Gauss-Seidel法で解を求める*/
  x = GS_method(A,b,Arow);

  /*解を表示*/
  printf("Gauss-Seidel法(反復%d回)\n",N);
  showVector((const double *) x,Arow);

	/*メモリの解放*/
  freeMatrix(A);
  freeMatrix(matrix);
  freeVector(b);
  freeVector(x);

	/*ファイルを閉じる*/
	fclose(f1);
	fclose(f2);
}
