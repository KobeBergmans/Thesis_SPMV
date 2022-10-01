/**
 * @file driver.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison
 * @version 0.1
 * @date 2022-09-29
 */

#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>

#include "CRS.hpp"
#include "VectorUtill.hpp"

int main(int argc, char** argv) {
    struct timespec start, stop; 
	double time;

    if (argc < 4) {
        std::cout << "You need to provide 3 command line arguments:" << std::endl;
        std::cout << "  1° Amount of times the power algorithm is executed" << std::endl;
        std::cout << "  2° Amount of iterations in the power method algorithm" << std::endl;
        std::cout << "  3° Poisson equation discretization steps" << std::endl;
        return -1;
    }

    int iter = std::stoi(argv[1]);
    int pwm_iter = std::stoi(argv[2]);
    int m = std::stoi(argv[3]);
    int mat_size = m*m;
    
    //Select method
    std::cout << "For now the basic sequential algorithm is used..." << std::endl;

    //Initialize matrix and vectors
    clock_gettime(CLOCK_MONOTONIC, &start);
    pwm::CRS<double, int> test_mat;
    test_mat.generatePoissonMatrix(m,m);

    double* x = new double[mat_size];
    double* y = new double[mat_size];
    std::fill(x, x+mat_size, 1.);

    clock_gettime(CLOCK_MONOTONIC, &stop);
    time  = (stop.tv_sec-start.tv_sec)*1000;
	time += (stop.tv_nsec-start.tv_nsec)/1000000.0;
    std::cout << "Time to set up datastructures: " << time << "ms" << std::endl;

    // Solve power method an amount of time
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < iter; ++i) {
        test_mat.powerMethod(x, y, pwm_iter);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    time  = (stop.tv_sec-start.tv_sec)*1000;
	time += (stop.tv_nsec-start.tv_nsec)/1000000.0;
    std::cout << "Time (ms) to get 1000 executions: " << time << "ms" << std::endl;
    
    
    return 0;
}