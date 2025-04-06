#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <numeric>
#include "phase1pt1.h"
#include "phase1pt2.h"
#include "phase1pt3.h"
#include "phase1pt4.h"


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

int main() {

    int trials = 500;

    int dim = 4;

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
        free(result1);

        auto start2 = std::chrono::high_resolution_clock::now();
        multiply_mv_col_major(matrixBColMajor, rowsB, colsB, vector, result2);
        auto end2 = std::chrono::high_resolution_clock::now();
        times2[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
        free(result2);

        auto start3 = std::chrono::high_resolution_clock::now();
        multiply_mm_naive(matrixA, rowsA, colsA, matrixBRowMajor, rowsB, colsB, result3);
        auto end3 = std::chrono::high_resolution_clock::now();
        times3[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count();
        free(result3);

        auto start4 = std::chrono::high_resolution_clock::now();
        multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixBColMajor, rowsB, colsB, result4);
        auto end4 = std::chrono::high_resolution_clock::now();
        times4[t] = std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count();
        free(result4);
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
