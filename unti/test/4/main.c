/*部分ピポット選択付ガウスの消去法*/
#include "NAbasic.h"
#define ABS(x) ((x) < 0 ? -(x) : (x)) /*絶対値関数*/

/*ベクトルの要素を表示する関数*/
int showVector(const double *vector,int length){
    int i;
    for(i=0;i<length;i++){
        printf("%.4f\n",vector[i]);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv){

	FILE *f1,*f2;
	int row1,col1,row2,col2,i,j,k,pipot,pipot_val;
	double **matrix1,**matrix2;
	double *ans,*tmp_vec,*vector;
  double a,tmp;

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
	matrix1 = csvRead(&row1,&col1,f1);

	/*ベクトルのCSVファイルの読み込み*/
	if((f2  = fopen(argv[2],"r")) == NULL){
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	matrix2 = csvRead(&row2,&col2,f2);

	/*二次元配列に直す*/
	if(col2 != 1){
		fprintf(stderr, "ベクトルが入力されていません.\n");
		return EXIT_FAILURE;
	}else{
		vector = matrix2colVector((const double **)matrix2,row2,col2);
	}

	/*連立一次方程式となるか確認*/
	if((col1 != row2) && (col1 != row1)){
		fprintf(stderr, "連立一次方程式となりません.\n");
		return EXIT_FAILURE;
	}

	/*ガウスの消去法*/
	for(i=0;i + 1 < row1;i++){
		/*ピポットを選択*/
		pipot_val = -1;
		pipot = 0;

		for(j=i;j<row1;j++){
			if(ABS(matrix1[j][i]) > pipot_val){
				pipot_val = ABS(matrix1[j][i]);
				pipot = j;
			}
		}

		/*行の入れ替え*/
		if(pipot != 0){
			tmp_vec = matrix1[pipot];
			matrix1[pipot] = matrix1[i];
			matrix1[i] = tmp_vec;

			tmp = vector[pipot];
			vector[pipot] = vector[i];
			vector[i] = tmp;
		}

		/*前進消去*/
		for(j=i+1;j<row1;j++){/*行*/
      a = matrix1[j][i]/matrix1[i][i];
			for(k=i;k<col1;k++){/*列*/
        matrix1[j][k] -= a*matrix1[i][k];
			}
			vector[j] -= a*vector[i];
		}
	}

  /*答え格納用配列を用意*/
  ans = allocVector(row1);

  /*交代代入*/
  for(i=row1-1;i>=0;i--){
      for(j=row1-1;j>i;j--){
          vector[i] -= matrix1[i][j]*ans[j];
      }
      ans[i] = vector[i]/matrix1[i][i];
  }

  /*結果を表示*/
  showVector((const double *) ans,row1);

	/*メモリの解放*/
  freeMatrix(matrix1);
  freeMatrix(matrix1);
	freeVector(vector);
  freeVector(tmp_vec);
  freeVector(ans);

	/*ファイルを閉じる*/
	fclose(f1);
	fclose(f2);
}
