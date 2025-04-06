#include <iostream>
#include <cassert>

double dot_product(const double* A, const double* B, const int length) {
    double value = 0;
    for (int i=0; i<length; i++){
        value += A[i] * B[i];
    }
    return value;
}

// 1
void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        result[i] = 0;
        for (int j=0; j<cols; j++) {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

// 2
void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    for (int i=0; i<rows; i++) {
        result[i] = 0;
        for (int j=0; j<cols; j++) {
            result[i] += matrix[j * rows + i] * vector[j];
        }
    }
}

// 3
void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result){
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int j=0; j<colsB; j++) {
        for (int i=0; i<rowsA; i++) {
            result[i * colsB + j] = 0;
            for (int k=0; k<colsA; k++) {
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
}

// 4
void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {
    if (colsA != rowsB) {
        printf("Incompatible Matrix Dimensions");
        return;
    }
    for (int i=0; i<rowsA; i++) {
        for (int j=0; j<colsB; j++) {
            result[i * colsB + j] = 0;
            for (int k=0; k<rowsB; k++) {
                result[i * colsB + j] += matrixA[i * colsA + k] * matrixB_transposed[j * rowsB + k];
            }
        }
    }
}

int test1() {
    int rowsB = 2;
    int colsB = 2;

    double* vector = new double[colsB * sizeof(double)];
    double* matrixBRowMajor = new double[colsB * rowsB * sizeof(double)];

    for (int i=0; i<colsB; i++) {
        vector[i] = i+1;
    }

    for (int i=0; i<rowsB * colsB; i++) {
        matrixBRowMajor[i] = i+1;
    }

    double* result1 = new double[rowsB * sizeof(double)];

    multiply_mv_row_major(matrixBRowMajor, rowsB, colsB, vector, result1);

    assert(result1[0] == 5);
    assert(result1[1] == 11);
    return 0;
}

int test2() {
    int rowsB = 2;
    int colsB = 2;

    double* vector = new double[colsB * sizeof(double)];
    double* matrixBColMajor = new double[colsB * rowsB * sizeof(double)];

    for (int i=0; i<colsB; i++) {
        vector[i] = i+1;
    }

    for (int i=0; i<rowsB * colsB; i++) {
        matrixBColMajor[i] = i+1;
    }

    double* result1 = new double[rowsB * sizeof(double)];

    multiply_mv_col_major(matrixBColMajor, rowsB, colsB, vector, result1);

    assert(result1[0] == 7);
    assert(result1[1] == 10);
    return 0;
}

int test3() {
    int rowsA = 2;
    int colsA = 2;
    int rowsB = 2;
    int colsB = 2;

    double* matrixA = new double[colsA * rowsA * sizeof(double)];
    double* matrixBRowMajor = new double[colsB * rowsB * sizeof(double)];

    for (int i=0; i<rowsA * colsA; i++) {
        matrixA[i] = i+1;
    }

    for (int i=0; i<rowsB * colsB; i++) {
        matrixBRowMajor[i] = i+7;
    }

    double* result1 = new double[rowsA * colsB * sizeof(double)];

    multiply_mm_naive(matrixA, rowsA, colsA, matrixBRowMajor, rowsB, colsB, result1);

    assert(result1[0] == 25);
    assert(result1[1] == 28);
    assert(result1[2] == 57);
    assert(result1[3] == 64);
    return 0;
}

int test4() {
    int rowsA = 2;
    int colsA = 2;
    int rowsB = 2;
    int colsB = 2;

    double* matrixA = new double[colsA * rowsA * sizeof(double)];
    double* matrixBColMajor = new double[colsB * rowsB * sizeof(double)];

    for (int i=0; i<rowsA * colsA; i++) {
        matrixA[i] = i+1;
    }

    for (int i=0; i<rowsB * colsB; i++) {
        matrixBColMajor[i] = i+7;
    }

    double* result1 = new double[rowsA * colsB * sizeof(double)];

    multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixBColMajor, rowsB, colsB, result1);

    assert(result1[0] == 23);
    assert(result1[1] == 29);
    assert(result1[2] == 53);
    assert(result1[3] == 67);
    return 0;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
