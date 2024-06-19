#include "NAbasic.h" 
 
int main(void) 
{ 
	FILE *fin; 
	double **matrix; 
	int row, col; 

	char c[sizeof(double)]; 
	int i, j, k; 

/* CSVから対象データを読み込む */ 

	if ((fin = fopen("1.csv", "r")) == NULL)
	{
		fprintf(stderr, "ファイルが存在しません.\n");
		return EXIT_FAILURE;
	}
	
	matrix = csvRead(&row,&col,fin);/*データをマトリックスに格納*/

	memcpy(c, &matrix[0][0], sizeof(double)); 

	printf("sEEEEEEE EEEEdddd dddddddd... \n"); 

	for (i = sizeof(double) - 1; i >= 0; i--) 
	{ 
		for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--) 
		{ 
			k = c[i] & (1 << j); 
			printf("%d", k ? 1 : 0); 
		} 
		printf(" "); 
	} 
	printf("\n"); 

	return 0; 
}