/**
 * @file driver.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison
 */

#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>

#include "Matrix/CRS.hpp"
#include "Util/VectorUtill.hpp"
#include "Util/DriverUtil.hpp"

#include "omp.h"

void printErrorMsg() {
    std::cout << "You need to provide the correct command line arguments:" << std::endl;
    std::cout << "  1° Amount of times the power algorithm is executed" << std::endl;
    std::cout << "  2° Amount of warm up runs for the power algorithm (not timed)" << std::endl;
    std::cout << "  3° Amount of iterations in the power method algorithm" << std::endl;
    std::cout << "  4° Poisson equation discretization steps" << std::endl;

    pwm::printAvailableMethods(5);
}

int main(int argc, char** argv) {
    double start, stop, time; 

    if (argc < 6) {
        printErrorMsg();
        return -1;
    }

    int iter = std::stoi(argv[1]);
    int warm_up = std::stoi(argv[2]);
    int pwm_iter = std::stoi(argv[3]);
    int m = std::stoi(argv[4]);
    int mat_size = m*m;

    int method = std::stoi(argv[5]);
    int threads = 0;
    int partitions = 0;
    if (method > 1 && argc < 6) {
        // No amount of threads specified
        printErrorMsg();
        return -1;
    } else if (method > 1) {
        threads = std::stoi(argv[6]);
    }

    if ((method == 4 || method == 5 || method == 6 || method == 7) && argc < 7) {
        printErrorMsg();
        return -1;
    } else if (method == 4 || method == 5 || method == 6 || method == 7) {
        partitions = std::stoi(argv[7]);
    }
    
    //Select method
    pwm::SparseMatrix<double, int>* test_mat = pwm::selectType<double, int>(method, threads);

    if (test_mat == NULL) {
        printErrorMsg();
        return -1;
    }
    
    //Initialize matrix and vectors
    start = omp_get_wtime();
    test_mat->generatePoissonMatrix(m, m, partitions);

    double* x = new double[mat_size];
    double* y = new double[mat_size];
    std::fill(x, x+mat_size, 1.);

    stop = omp_get_wtime();
    time = (stop - start) * 1000;
    std::cout << "Time to set up datastructures: " << time << "ms" << std::endl;

    // Do warm up iterations
    for (int i = 0; i < warm_up; ++i) {
        std::fill(x, x+mat_size, 1.);
        test_mat->powerMethod(x, y, pwm_iter);
    }

    // Solve power method an amount of time
    double timings[iter];
    for (int i = 0; i < iter; ++i) {
        start = omp_get_wtime();
        std::fill(x, x+mat_size, 1.);
        test_mat->powerMethod(x, y, pwm_iter);
        stop = omp_get_wtime();
        timings[i] = (stop - start) * 1000;
    }

    pwm::printVector(timings, iter);

#ifndef NDEBUG
    std::cout << "Result for checking measures: " << std::endl;
    if (pwm_iter % 2 == 0) {
        pwm::printVector(x, mat_size);
    } else {
        pwm::printVector(y, mat_size);
    }
    
#endif

    delete [] x;
    delete [] y;
    delete test_mat;
    
    return 0;
}