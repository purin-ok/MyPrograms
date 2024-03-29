/*
???l???p??{????Q?????t?@?C??
  Sept. 30, 2021	ver 1.2
?@Jan. 11, 2019		ver 1.1
 */

#include "NAbasic.h"

 /*
  csvRead(int *row, int *col, FILE *fin)
   csv?t?@?C?????????????z???i?[????B
	 ???l: 2?????z????v?f???|?C???^?i?????s??j

	 ?p?????[?^
	 ?@?o??
		 row: ????????s??
		 col: ????????? (csv??????f?[?^?s??m??)

	 ?@????
		 fin: ??????t?@?C????t?@?C???|?C???^
 */
double** csvRead(int *row, int *col, FILE *fin)
{
	char buf[MAX_STR_LENGTH], buf2[MAX_STR_LENGTH];
	double *mat[MAX_ROW_NUM];
	double **result;

	char *nbuf;
	int i = 0, j;
	*row = *col = 0;
	
	while (fgets(buf, sizeof(buf), fin) != NULL)
	{
		// #??R?????g?s
		if (buf[0] == '#')	continue;

		if (i == 0)
		{
			strcpy(buf2, buf);
			if (strtok(buf2, ",") != NULL)	(*col)++;
			while (strtok(NULL, ",\r\n\0") != NULL)	(*col)++;
		}

		mat[i] = allocVector(*col);

		mat[i][0] = atof(strtok(buf, ","));
		//printf("%f", mat[i][0]);
		for (j = 1; j < *col; j++)
		{
			nbuf = strtok(NULL, ",\r\n\0");
			if (nbuf == NULL)
				mat[i][j] = 0;
			else
				mat[i][j] = atof(nbuf);
		}
		i++;
	}

	// ?s???????????????C?????????m????C???z????R?s?[????
	*row = i;
	if ((result = (double **)malloc(((*row) + 1) * sizeof(double *))) == NULL)
	{
		fprintf(stderr, "?????????m????????? (from csvRead) \n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < *row; i++)
	{
		result[i] = mat[i];
	}
	result[*row] = NULL; // ?I?[??NULL????????

	// ??????????z???|?C???^????
	return result;
}

/*
 allocVector(int length)
  vector???m?????
	???l: 1?????z????v?f???|?C???^?i?????s??j

	?p?????[?^
	  ????
		length: ?x?N?g???????
*/
double* allocVector(int length)
{
	double *vec;

	if ((vec = (double*)malloc(length * sizeof(double))) == NULL)
	{
		fprintf(stderr, "?????????m????????? (from allocVector) \n");
		exit(EXIT_FAILURE);
	}

	return vec;
}

/*
 allocMatrix(int row, int col)
  matrix???m?????
	???l: 2?????z????v?f???|?C???^?i?????s??j

	?p?????[?^
	  ????
		row: ?s??
		col: ??
*/
double** allocMatrix(int row, int col)
{
	double **matrix;
	int i;
	if ((matrix = (double **)malloc((row + 1) * sizeof(double *))) == NULL)
	{
		fprintf(stderr, "?????????m????????? (from allocMatrix) \n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < row; i++)
	{
		if ((matrix[i] = (double *)malloc(col * sizeof(double))) == NULL)
		{
			fprintf(stderr, "?????????m????????? (from allocMatrix) \n");
			exit(EXIT_FAILURE);
		}
	}
	matrix[row] = NULL;

	return matrix;
}

/*
  freeMatrix(double **matrix)
	matrix???m?????
	  ???l: ?J??????or???s

	  ?p?????[?^
		????
		  matrix: ?J?????????s??i??I?s?v?f??NULL?j
*/
int freeMatrix(double **matrix)
{
	int i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);

	return EXIT_SUCCESS;
}

/*
freeVector(double *vector)
  vector???m?????
	  ???l: ?J??????or???s

	  ?p?????[?^
		????
		  vector: ?J?????????x?N?g??
*/
int freeVector(double *vector)
{
	free(vector);
	return EXIT_SUCCESS;
}

/*
matrix2colVector(const double **matrix, int row, int col)
  matrix???x?N?g??????????
	  ???l: 1?????z??i?x?N?g???j???v?f???|?C???^?i?????z??j

	  ?p?????[?^
		????
		  matrix: ??????s??
		?@row: ????O??z???s??
		?@col: ????O??z???s??
*/
double* matrix2colVector(const double **matrix, int row, int col)
{
	double *vector;
	int i, j, k;

	k = 0;
	vector = allocVector(row * col);
	for (j = 0; j < col; j++)
	{
		for (i = 0; i < row; i++)
		{
			vector[k] = matrix[i][j];
			k++;
		}
	}

	return vector;
}

/*
matrix2colVector(const double **matrix, int row, int col)
  matrix???x?N?g??????????
	  ???l: ?\??????

	  ?p?????[?^
		????
		  matrix: ?o????s??i?s?��j
		?@row: ????O??z???s??
		?@col: ????O??z???s??
*/
int showMatrix(const double **matrix, int row, int col)
{
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%.4f \t", matrix[i][j]);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}

/*
tpMatrix(const double **matrix)
  matrix??]?u????
	  ???l: ?]?u?s??

	  ?p?????[?^
		????
		  matrix: ?]?u???s??i?s?��j
		  row: ?]?u?O??z???s??
		?@col: ?]?u?O??z???s??
*/
double** tpMatrix(const double ** matrix, int row, int col)
{
	double **transM = allocMatrix(col, row);
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			transM[j][i] = matrix[i][j];
		}
	}

	return transM;
}