// matrix_multiplication_openmp.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define BLOCK_SIZE 16

void initialize_matrix(int *array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i * cols + j] = rand() % 10;
        }
    }
}

void print_matrix(int *array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << array[i * cols + j] << " ";
        }
        cout << endl;
    }
}

void matrix_multiplication_serial(int *a, int *b, int *c, int common, int c_rows, int c_cols) {
    for (int i = 0; i < c_rows; i++) {
        for (int j = 0; j < c_cols; j++) {
            int sum = 0;
            for (int k = 0; k < common; k++) {
                sum += a[i * common + k] * b[k * c_cols + j];
            }
            c[i * c_cols + j] = sum;
        }
    }
}

void matrix_multiplication_parallel(int *a, int *b, int *c, int common, int c_rows, int c_cols) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < c_rows; i++) {
        for (int j = 0; j < c_cols; j++) {
            int sum = 0;
            for (int k = 0; k < common; k++) {
                sum += a[i * common + k] * b[k * c_cols + j];
            }
            c[i * c_cols + j] = sum;
        }
    }
}

int main() {
    int a_rows, a_cols, b_rows, b_cols, c_rows, c_cols;

    cout << "Dimensions of matrix 1:\n";
    cout << "Rows: ";
    cin >> a_rows;

    cout << "Columns: ";
    cin >> a_cols;

    cout << "Dimensions of matrix 2:\n";
    cout << "Rows: " << a_cols << endl << "Columns: ";
    cin >> b_cols;

    b_rows = a_cols;
    c_rows = a_rows;
    c_cols = b_cols;

    int a_size = a_rows * a_cols;
    int b_size = b_rows * b_cols;
    int c_size = c_rows * c_cols;

    int *A = new int[a_size];
    int *B = new int[b_size];
    int *C_serial = new int[c_size];
    int *C_parallel = new int[c_size];

    srand(time(0)); // random seed

    initialize_matrix(A, a_rows, a_cols);
    //cout << "Matrix 1:\n";
    //print_matrix(A, a_rows, a_cols);

    initialize_matrix(B, b_rows, b_cols);
    //cout << "Matrix 2:\n";
    //print_matrix(B, b_rows, b_cols);

    // Serial multiplication
    double start_time = omp_get_wtime();
    matrix_multiplication_serial(A, B, C_serial, a_cols, c_rows, c_cols);
    double end_time = omp_get_wtime();
    double serial_time = (end_time - start_time) * 1000; // ms

    cout << "\nResult (Serial CPU):\n";
   // print_matrix(C_serial, c_rows, c_cols);
    cout << "Elapsed Time (Serial CPU) = " << serial_time << " milliseconds\n";

    // Parallel multiplication
    start_time = omp_get_wtime();
    matrix_multiplication_parallel(A, B, C_parallel, a_cols, c_rows, c_cols);
    end_time = omp_get_wtime();
    double parallel_time = (end_time - start_time) * 1000; // ms

    cout << "\nResult (Parallel CPU using OpenMP):\n";
    //print_matrix(C_parallel, c_rows, c_cols);
    cout << "Elapsed Time (Parallel CPU) = " << parallel_time << " milliseconds\n";

    delete[] A;
    delete[] B;
    delete[] C_serial;
    delete[] C_parallel;

    return 0;
}
