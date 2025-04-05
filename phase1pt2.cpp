#include "phase1header.h"
#include <iostream>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        double* left_row = (double*)malloc(cols * sizeof(double));
        for (int j=0; j<cols; j++) {
            left_row[j] = matrix[j * rows + i];
        }
        result[i] = dot_product(left_row, vector, cols);
        free(left_row);
    }
}

void print_matrix_col_major(double* matrix, int rows, int cols) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            printf("%f ", matrix[rows * j + i]);
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
    int rows = 4;
    int cols = 3;
    double* vector = (double*)malloc(cols * sizeof(double));
    double* matrix = (double*)malloc(cols * rows * sizeof(double));
    double* result = (double*)malloc(rows * sizeof(double));
    for (int i=0; i<rows * cols; i++) {
        matrix[i] = i;
    }
    for (int i=0; i<cols; i++) {
        vector[i] = i;
    }
    print_matrix_col_major(matrix, rows, cols);
    print_vector(vector, cols);
    multiply_mv_col_major(matrix, rows, cols, vector, result);
    print_vector(result, rows);
    return 0;
}