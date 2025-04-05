#include <iostream>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        double* left_row = (double*)malloc(cols * sizeof(double));
        for (int j=0; j<cols; j++) {
            left_row[j] = matrix[i * cols + j];
        }
        result[i] = dot_product(left_row, vector, cols);
        free(left_row);
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

void print_vector(double* vector, int length) {
    for (int i=0; i<length; i++) {
        printf("%f ", vector[i]);
    }
    printf("\n \n");
}

int main() {
    return 0;
}
