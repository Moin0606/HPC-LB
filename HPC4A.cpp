#include<iostream>
#include<omp.h>     // OpenMP header
#include<cstdlib>   // For rand()
using namespace std;

void fill_array(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void add_cpu_parallel(int *arr1, int *arr2, int *result, int size) {
    #pragma omp parallel for
    for(int i = 0; i < size; i++) {
        result[i] = arr1[i] + arr2[i];
    }
}

void print_matrix(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int *arr1_cpu, *arr2_cpu, *result_cpu;
    int size;

    cout << "Enter size of vector: ";
    cin >> size;

    arr1_cpu = new int[size];
    arr2_cpu = new int[size];
    result_cpu = new int[size];

    fill_array(arr1_cpu, size);
    cout << "Array 1: ";
   // print_matrix(arr1_cpu, size);

    fill_array(arr2_cpu, size);
    cout << "Array 2: ";
   // print_matrix(arr2_cpu, size);

    double start_time, end_time;

    // Parallel addition using OpenMP
    start_time = omp_get_wtime();
    add_cpu_parallel(arr1_cpu, arr2_cpu, result_cpu, size);
    end_time = omp_get_wtime();

    cout << "Result (Parallel CPU using OpenMP):\n";
    //print_matrix(result_cpu, size);
    cout << "Elapsed Time = " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    // Optional: Serial addition for comparison
    start_time = omp_get_wtime();
    for(int i = 0; i < size; i++) {
        result_cpu[i] = arr1_cpu[i] + arr2_cpu[i];
    }
    end_time = omp_get_wtime();

    cout << "Result (Serial CPU):\n";
    //print_matrix(result_cpu, size);
    cout << "Elapsed Time = " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    delete[] arr1_cpu;
    delete[] arr2_cpu;
    delete[] result_cpu;

    return 0;
}
