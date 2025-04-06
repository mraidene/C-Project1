// #include "phase1header.h"
// I can't get the functions to import properly so I am copy pasting them
#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <numeric>

double mean (const int* vec, const int length) {
    double sum = 0.0;
    for (int i=0; i<length; i++) {
        sum += vec[i];
    }
    return sum/length;
}

double stdev (const int* vec, const int length) {
    double mu = mean(vec, length);
    double var = 0;
    for (int i=0; i<length; i++) {
        var += std::pow(vec[i] - mu, 2);
    }
    return std::sqrt(var / (length-1));
}

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
        double* left_row = (double*)malloc(cols * sizeof(double));
        for (int j=0; j<cols; j++) {
            left_row[j] = matrix[i * cols + j];
        }
        result[i] = dot_product(left_row, vector, cols);
        free(left_row);
    }
}

// 2
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

// 3
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

// 4
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

int main() {

    int trials = 100;

    int dim = 100;

    int rowsA = dim;
    int colsA = dim;
    int rowsB = dim;
    int colsB = dim;

    std::random_device rd;
    std::uniform_int_distribution<> distrib(-10, 10);
    std::mt19937 gen(rd());

    double* vector = (double*)malloc(colsB * sizeof(double));
    double* matrixA = (double*)malloc(colsA * rowsA * sizeof(double));
    double* matrixBRowMajor = (double*)malloc(colsB * rowsB * sizeof(double));
    double* matrixBColMajor = (double*)malloc(colsB * rowsB * sizeof(double));

    int* times1 = (int*)malloc(trials * sizeof(int));
    int* times2 = (int*)malloc(trials * sizeof(int));
    int* times3 = (int*)malloc(trials * sizeof(int));
    int* times4 = (int*)malloc(trials * sizeof(int));

    for (int t=0; t<trials; t++){
        // Filling The Vector
        for (int i=0; i<colsB; i++) {
            vector[i] = distrib(gen);
        }

        // Filling Matrix A
        for (int i=0; i<rowsA * colsA; i++) {
            matrixA[i] = distrib(gen);
        }

        // Filling Matrix B in row and col major
        for (int i=0; i<rowsB; i++) {
            for (int j=0; j<colsB; j++) {
                int temp = distrib(gen);
                matrixBRowMajor[i * colsB + j] = temp;
                matrixBColMajor[j*rowsB + i] = temp;
            }
        }

        double* result1 = (double*)malloc(rowsB * sizeof(double));
        double* result2 = (double*)malloc(rowsB * sizeof(double));
        double* result3 = (double*)malloc(colsB * rowsA * sizeof(double));
        double* result4 = (double*)malloc(colsB * rowsA * sizeof(double));

        auto start1 = std::chrono::high_resolution_clock::now();
        multiply_mv_row_major(matrixBRowMajor, rowsB, colsB, vector, result1);
        auto end1 = std::chrono::high_resolution_clock::now();
        times1[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();

        auto start2 = std::chrono::high_resolution_clock::now();
        multiply_mv_col_major(matrixBColMajor, rowsB, colsB, vector, result2);
        auto end2 = std::chrono::high_resolution_clock::now();
        times2[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();

        auto start3 = std::chrono::high_resolution_clock::now();
        multiply_mm_naive(matrixA, rowsA, colsA, matrixBRowMajor, rowsB, colsB, result3);
        auto end3 = std::chrono::high_resolution_clock::now();
        times3[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count();

        auto start4 = std::chrono::high_resolution_clock::now();
        multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixBColMajor, rowsB, colsB, result4);
        auto end4 = std::chrono::high_resolution_clock::now();
        times4[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count();
    }



    std::cout << "Average Time1: " << mean(times1, trials) << " nanoseconds   ";
    std::cout << "Std: " << stdev(times1, trials) << " nanoseconds" << std::endl;
    std::cout << "Average Time2: " << mean(times2, trials) << " nanoseconds   ";
    std::cout << "Std: " << stdev(times2, trials) << " nanoseconds" << std::endl;
    std::cout << "Average Time3: " << mean(times3, trials) << " nanoseconds   ";
    std::cout << "Std: " << stdev(times3, trials) << " nanoseconds" << std::endl;
    std::cout << "Average Time4: " << mean(times4, trials) << " nanoseconds   ";
    std::cout << "Std: " << stdev(times4, trials) << " nanoseconds" << std::endl;

    return 0;
}
