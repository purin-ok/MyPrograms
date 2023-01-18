void swap_row(double **matrix, int row, int col, int row1, int row2){
    row1--;
    row2--;

    if(row1 < 1 || row1 > row || row2 < 1 || row2 > row){
        return;
    }
    double *temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}