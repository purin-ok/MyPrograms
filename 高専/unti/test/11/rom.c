//rombergIntegral.c
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double f(double x);//関数f(x)
double h(double a, double b, int k);//高さ
void readCSV(FILE *file, double *a0, double *a1);//csvファイルから積分範囲を読み込む





int main(){
        char range[20];
        double a;//積分範囲の下端
        double b;//積分範囲の上端
        int n = 4;//分割数

        double tmp;
        double r[n+2][n+2];
        int i,j,k;
        FILE *fp;

        readCSV(fp, &a, &b);
        printf("a = %lf, b = %lf\n",a,b);

        r[1][1] = h(a,b,1)/2*(f(a)+f(b));

        for(k = 2; k <= n+1; k++){
                tmp = 0;
                for(i = 1;i <= pow(2,k-2);i++){
                        tmp = tmp+f(a+(2*i-1)*h(a,b,k));
                }
                r[k][1] = (r[k-1][1]+h(a,b,k-1)*tmp)/2;
        }


        for(k = 2; k <= n+1; k++){
                for(j = 2;j <= k;j++){
                        r[k][j] = r[k][j-1]+(r[k][j-1]-r[k-1][j-1])/(pow(4,j-1)-1);
                }
        }


        for(k = 1; k <= n+1; k++){
                for(j = 1;j <= k;j++){
                        printf("%.8f ",r[k][j]);
                }
                printf("\n");
        }
        printf("積分値: %f",r[n+1][n+1] );

return 0;
}



//関数f(x)
double f(double x){
  return exp(x);
}


//高さを求める
double h(double a, double b, int k){
        return (b-a)/pow(2,k-1);
}


//csvファイルから行列を読み込む
void readCSV(FILE *file, double *a0, double *a1) {

  float f1,f2;
  int i  =  0;

  if ((file  =  fopen("k11-input.csv", "r"))  ==  NULL) {
    printf("ファイルが読み込めません \n");
  }

  while (fscanf(file, "%f, %f ", &f1, &f2) !=  EOF) {
    *a0  =  (double)f1;
    *a1  =  (double)f2;
  }

  fclose(file);
}
