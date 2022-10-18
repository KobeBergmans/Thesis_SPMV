/**
 * @file driver_input.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison with MM input files
 * @version 0.1
 * @date 2022-10-18
 */

#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>

#include "CRS.hpp"
#include "CRSOMP.hpp"
#include "CRSTBB.hpp"
#include "CRSTBBGraph.hpp"
#include "CRSTBBGraphPinned.hpp"
#include "CRSThreadPool.hpp"
#include "CRSThreadPoolPinned.hpp"
#include "VectorUtill.hpp"
#include "Triplet.hpp"

#include "omp.h"
#include "oneapi/tbb.h"

void printErrorMsg() {
    std::cout << "You need to provide the correct command line arguments:" << std::endl;
    std::cout << "  1° Filename of Matrix market input file" << std::endl;
    std::cout << "  2° Amount of times the power algorithm is executed" << std::endl;
    std::cout << "  3° Amount of warm up runs for the power algorithm (not timed)" << std::endl;
    std::cout << "  4° Amount of iterations in the power method algorithm" << std::endl;
    std::cout << "  5° Method to use:" << std::endl;
    std::cout << "     1) Standard CRS (sequential)" << std::endl;
    std::cout << "     2) CRS parallelized using OpenMP" << std::endl;
    std::cout << "     3) CRS parallelized using TBB" << std::endl;
    std::cout << "     4) CRS parallelized using TBB graphs" << std::endl;
    std::cout << "     5) CRS parallelized using TBB graphs with each node pinned to a CPU" << std::endl;
    std::cout << "     6) CRS parallelized using Boost Thread Pool" << std::endl;
    std::cout << "     7) CRS parallelized using Boost Thread Pool with functions pinned to a CPU" << std::endl;
    std::cout << "  6° Amount of threads (only for a parallel method).";
    std::cout << " -1 lets the program choose the amount of threads arbitrarily" << std::endl;
    std::cout << "  7° Amount of partitions the matrix is split up into (only for method 4, 5, 6 and 7)" << std::endl;
}

template<typename T, typename int_type>
pwm::SparseMatrix<T, int_type>* selectType(int method, int threads) {
    switch (method) {
        case 1:
            return new pwm::CRS<T, int_type>(threads);

        case 2:
            return new pwm::CRSOMP<T, int_type>(threads);

        case 3:
            return new pwm::CRSTBB<T, int_type>(threads);

        case 4:
            return new pwm::CRSTBBGraph<T, int_type>(threads);

        case 5:
            return new pwm::CRSTBBGraphPinned<T, int_type>(threads);

        case 6:
            return new pwm::CRSThreadPool<T, int_type>(threads);

        case 7:
            return new pwm::CRSThreadPoolPinned<T, int_type>(threads);
        
        default:
            return NULL;
    }
}

int main(int argc, char** argv) {
    double start, stop, time; 

    if (argc < 6) {
        printErrorMsg();
        return -1;
    }

    std::string input_file = argv[1];
    int iter = std::stoi(argv[2]);
    int warm_up = std::stoi(argv[3]);
    int pwm_iter = std::stoi(argv[4]);

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
    pwm::SparseMatrix<double, int>* test_mat = selectType<double, int>(method, threads);

    // Input matrix
    pwm::Triplet<double, int> input_mat;
    input_mat.loadFromMM(input_file);
    
    return 0;
}