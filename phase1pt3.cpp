#include <iostream>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result){
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int j=0; j<colsB; j++) {
        double* col_right = (double*)malloc(rowsB * sizeof(double));
        for (int i=0; i<colsB; i++) {
            col_right[i] = matrixB[i * colsB + j];
        }
        for (int i=0; i<rowsA; i++) {
            double* row_left = (double*)malloc(colsA * sizeof(double));
            for (int k=0; k<colsA; k++) {
                row_left[k] = matrixA[i * colsA + k];
            }
            result[i * colsB + j] = dot_product(row_left, col_right, rowsB);
            free(row_left);
        }
        free(col_right);
    }
}

void print_matrix_row_major(double* matrix, int rows, int cols) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            printf("%f ", matrix[cols * i + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    return 0;
}
