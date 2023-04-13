/**
 * @file MPI_driver.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison using MPI
 */

#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>

#include "Util/VectorUtill.hpp"
#include "Util/Poisson.hpp"

#include <mpi.h>
#include "omp.h"

void printErrorMsg() {
    std::cout << "You need to provide the correct command line arguments:" << std::endl;
    std::cout << "  1° Amount of times the power algorithm is executed" << std::endl;
    std::cout << "  2° Amount of warm up runs for the power algorithm (not timed)" << std::endl;
    std::cout << "  3° Amount of iterations in the power method algorithm" << std::endl;
    std::cout << "  4° Poisson equation discretization steps";
}

void mv(const double* x, double* y, const double* data_arr, const int* col_ind, const int* row_start, const int thread_rows, const int first_row) {
    int j;
    for (int l = 0; l < thread_rows; ++l) {
        double sum = 0;
        for (int k = row_start[l]; k < row_start[l+1]; ++k) {
            j = col_ind[k];
            sum += data_arr[k]*x[j];
        }
        y[l] = sum;
    }
}

void powerIteration(double* x, double* y, const double* data_arr, const int* col_ind, const int* row_start, const int thread_rows, const int first_row, 
                 const int iterations, const int* recvcount, const int* displs) {
    for (int i = 0; i < iterations; ++i) {
        mv(x, y, data_arr, col_ind, row_start, thread_rows, first_row);

        // Calculate norm on own part
        double norm_part = 0;
        for (int i = 0; i < thread_rows; ++i) {
            norm_part += y[i]*y[i];
        }

        // All reduce the norm and square root
        double norm;
        MPI_Allreduce(&norm_part, &norm, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        norm = std::sqrt(norm);

        // Normalize y and copy to x
        for (int i = 0; i < thread_rows; ++i) {
            y[i] /= norm;
            x[i+first_row] = y[i];
        }

        // Allgather x
        MPI_Allgatherv(x+first_row, thread_rows, MPI_DOUBLE, x, recvcount, displs, MPI_DOUBLE, MPI_COMM_WORLD);
    }
}

int main(int argc, char **argv) {
    double start = 0;
    double stop; 
    double time;

    // Setup MPI
    int processes, processID;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &processID);

    if (argc < 5) {
        if (processID == 0) printErrorMsg();
        return -1;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (processID == 0) start = omp_get_wtime();

    // Get command line arguments and properties of matrix
    int iter = std::stoi(argv[1]);
    int warm_up = std::stoi(argv[2]);
    int pwm_iter = std::stoi(argv[3]);
    int m = std::stoi(argv[4]);

    // Fill the Matrix datastructures for each matrix
    int am_rows = std::round(m * m / processes);
    int first_row = am_rows*processID;
    int last_row;
    if (processID == processes - 1) last_row = m*m;
    else last_row = first_row + am_rows;
    int thread_rows = last_row - first_row;

    int* row_start = new int[thread_rows + 1];
    int* col_ind = new int[5 * thread_rows];
    double* data_arr = new double[5 * thread_rows];
    pwm::fillPoisson(data_arr, row_start, col_ind, m, m, first_row, last_row);

    // Create y and x on each processor
    double* x = new double[m*m];
    double* y = new double[thread_rows];
    std::fill(x, x+m*m, 1.);

    // Create recvcount & displs
    int* recvcount = new int[processes];
    int* displs = new int[processes];
    displs[0] = 0;
    for (int i = 0; i < processes; ++i) {
        if (i != processes - 1) recvcount[i] = am_rows;
        else recvcount[i] = m*m-am_rows*(processes-1);

        if (i != 0) displs[i] = displs[i-1] + am_rows;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (processID == 0) {
        stop = omp_get_wtime();
        time = (stop - start) * 1000;
        std::cout << "Time to set up datastructures: " << time << "ms" << std::endl;
    }

    // Do warm up iterations
    for (int i = 0; i < warm_up; ++i) {
        std::fill(x, x+m*m, 1.);
        powerIteration(x, y, data_arr, col_ind, row_start, thread_rows, first_row, pwm_iter, recvcount, displs);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (processID == 0)     start = omp_get_wtime();

    // Do power iterations
    for (int i = 0; i < iter; ++i) {
        std::fill(x, x+m*m, 1.);
        powerIteration(x, y, data_arr, col_ind, row_start, thread_rows, first_row, pwm_iter, recvcount, displs);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (processID == 0) {
        stop = omp_get_wtime();
        time = (stop - start) * 1000;
        std::cout << "Time (ms) to get " << iter << " executions: " << time << "ms" << std::endl;
    }

#ifndef NDEBUG
    // Print each proc contents
    for (int i = 0; i < processes; ++i) {
        if (i != processID) {
            MPI_Barrier(MPI_COMM_WORLD);
        } else {
            std::cout << "Proc " << processID << " has following result: " << std::endl;
            pwm::printVector(x, m*m);
            MPI_Barrier(MPI_COMM_WORLD);
        }
    }
#endif

    MPI_Finalize();
}