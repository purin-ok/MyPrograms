double 	vector_norm(double *vector, int len){
    int i;
    double s = 0.0;

    for (i = 0; i < len; i++) {
        s += vector[i] * vector[i];
    }
    return sqrt(s);
}

double formed_angle(double **A, int Arow, int Acol,
                    double **B, int Brow, int Bcol) {

    if (Arow != 1 || Bcol != 1 || Acol != Brow) {
    puts("演算ができません");
    return -1;
    }
    int len = Arow * Acol;
    double **in_pro = matrix_product(A, Arow, Acol, B, Brow, Bcol);

    return acos(in_pro[0][0] 
                / vector_norm(matrix2colVector(A, Arow, Acol), len)
                / vector_norm(matrix2colVector(B, Brow, Bcol), len));
}

