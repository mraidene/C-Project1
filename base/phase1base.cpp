#include <iostream>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

int affine(int x, int y, int z)
{
    return x * y + z;
}

// Part 1 Function 1
void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        double* left_row = (double*)malloc(cols * sizeof(double));
        for (int j=0; j<cols; j++) {
            left_row[j] = matrix[affine(i, cols, j)];
        }
        result[i] = dot_product(left_row, vector, cols);
        free(left_row);
    }
}
// Part 1 Function 2
void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        double* left_row = (double*)malloc(cols * sizeof(double));
        for (int j=0; j<cols; j++) {
            left_row[j] = matrix[affine(j, rows, i)];
        }
        result[i] = dot_product(left_row, vector, cols);
        free(left_row);
    }
}
// Part 1 Function 3
void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result){
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int j=0; j<colsB; j++) {
        double* col_right = (double*)malloc(rowsB * sizeof(double));
        for (int i=0; i<colsB; i++) {
            col_right[i] = matrixB[affine(i, colsB, j)];
        }
        for (int i=0; i<rowsA; i++) {
            double* row_left = (double*)malloc(colsA * sizeof(double));
            for (int k=0; k<colsA; k++) {
                row_left[k] = matrixA[affine(i, colsA, k)];
            }
            result[affine(i, colsB, j)] = dot_product(row_left, col_right, rowsB);
            free(row_left);
        }
        free(col_right);
    }
}
// Part 1 Function 4
void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int i=0; i<rowsA; i++) {
        double* row_left = (double*)malloc(colsA * sizeof(double));
        for (int j=0; j<colsA; j++) {
            row_left[j] = matrixA[affine(i, colsA, j)];
        }
        for (int j=0; j<colsB; j++) {
            double* col_right = (double*)malloc(rowsB * sizeof(double));
            for (int k=0; k<rowsB; k++) {
                col_right[k] = matrixB_transposed[affine(j, rowsB, k)];
            }
            result[i * colsB + j] = dot_product(row_left, col_right, rowsB);
            free(col_right);
        }
        free(row_left);
    }
}

int main() {
    return 0;
}