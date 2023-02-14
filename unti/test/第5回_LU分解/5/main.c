/*LU分解を用いた連立一次方程式の直接解法*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*絶対値関数*/

/*ベクトルの要素を表示する関数*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

/*行の入れ替え*/
void swap(double **matrix,int row,int i,int pivot){
  double *tmp_vec = matrix[pivot];

  if(!(((0<=i)&&(i<row))&&((0<=pivot)&&(pivot<row)))){
    fprintf(stderr, "行の交換に失敗しました\n");
    exit(EXIT_FAILURE);
  }

  matrix[pivot] = matrix[i];
  matrix[i] = tmp_vec;
}

/*行列とベクトルの積を計算*/
double *matrix_times_vector(double **A,double *b,int row,int col,int len){
  int i,j;
  double *Ab = allocVector(len);

  if(col != len){
    fprintf(stderr, "行列とベクトルの積の計算に失敗しました\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < row; i++) {
      for (j = 0; j < col; j++) {
          Ab[i] += A[i][j] * b[j];
      }
  }

  return Ab;
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

/*前進代入*/
void foward(double **L,double *y,double *Pb,int size){
  int i,j;

  for(i=0;i<size;i++){
    y[i] = Pb[i]/L[i][i];
    for(j=0;j<i;j++){
      y[i] -= y[j]*L[i][j]/L[i][i];
    }
  }
}

/*後退代入*/
void backward(double **U,double *x,double *y,int size){
  int i,j;

  for(i=size-1;i>=0;i--){
    x[i] = y[i]/U[i][i];
    for(j=i+1;j<size;j++){
      x[i] -= x[j]*U[i][j]/U[i][i];
    }
  }
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int Arow,Acol,brow,bcol,i;
	double **A,**matrix,**L,**U,**P;
	double *b,*Pb,*y,*x;

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
		b = matrix2colVector(matrix,brow,bcol);
	}

	/*連立一次方程式となるか確認*/
	if((Acol != brow) && (Acol != Arow)){
		fprintf(stderr, "連立一次方程式となりません.\n");
		return EXIT_FAILURE;
	}

  /*L,U,Pの行列を用意*/
  L = allocMatrix(Arow,Acol);
  U = allocMatrix(Arow,Acol);
  P = allocMatrix(Arow,Acol);

  /*L,Pを単位行列にする*/
  for(i=0;i<Acol;i++){
    P[i][i] = 1;
    L[i][i] = 1;
  }

  /*LU分解*/
  LU_decomposition(A,L,U,P,Acol);

  /*各行列の表示*/
  puts("行列L");
  showMatrix((const double **)L,Arow,Acol);
  puts("行列U");
  showMatrix((const double **)U,Arow,Acol);
  puts("行列P");
  showMatrix((const double **)P,Arow,Acol);

  /*交換行列Pとベクトルbの積を計算*/
  Pb = matrix_times_vector(P,b,Arow,Acol,brow);

  /*x,yのベクトルを用意*/
  y = allocVector(bcol);
  x = allocVector(bcol);

  /*前進代入*/
  foward(L,y,Pb,Arow);
  /*後退代入*/
  backward(U,x,y,Arow);

  /*解を表示*/
  puts("ベクトルx");
  showVector((const double *) x,Arow);

	/*メモリの解放*/
  freeMatrix(A);
  freeMatrix(L);
  freeMatrix(U);
  freeMatrix(P);
  freeMatrix(matrix);
  freeVector(b);
  freeVector(Pb);
  freeVector(x);
  freeVector(y);

	/*ファイルを閉じる*/
	fclose(f1);
	fclose(f2);
}
