double **matrix_product(double **A, int Arow, int Acol,
                        double **B, int Brow, int Bcol) {

    double **result = allocMatrix(Arow, Bcol);
    int i, j, k;

    if (Acol != Brow){
        puts("演算ができません.");
			return result;
    }

    for (i = 0; i < Arow; i++) {
        for (j = 0; j < Bcol; j++) {
            for (k = 0; k < Acol; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}