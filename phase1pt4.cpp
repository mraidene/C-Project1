#include "phase1header.h"
#include <iostream>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int i=0; i<rowsA; i++) {
        double* row_left = (double*)malloc(colsA * sizeof(double));
        for (int j=0; j<colsA; j++) {
            row_left[j] = matrixA[i * colsA + j];
        }
        for (int j=0; j<colsB; j++) {
            double* col_right = (double*)malloc(rowsB * sizeof(double));
            for (int k=0; k<rowsB; k++) {
                col_right[k] = matrixB_transposed[j * rowsB + k];
            }
            result[i * colsB + j] = dot_product(row_left, col_right, rowsB);
            free(col_right);
        }
        free(row_left);
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
    int rowsA = 4;
    int colsA = 3;
    int rowsB = 3;
    int colsB = 2;
    double* matrixA = (double*)malloc(colsA * rowsA * sizeof(double));
    double* matrixB = (double*)malloc(colsB * rowsB * sizeof(double));
    double* result = (double*)malloc(colsB * rowsA * sizeof(double));
    for (int i=0; i<rowsA * colsA; i++) {
        matrixA[i] = i;
    }
    for (int i=0; i<rowsB * colsB; i++) {
        matrixB[i] = i;
    }
    print_matrix_row_major(matrixA, rowsA, colsA);
    print_matrix_col_major(matrixB, rowsB, colsB);
    multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);
    print_matrix_row_major(result, rowsA, colsB);
    return 0;
}