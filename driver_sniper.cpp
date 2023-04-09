/**
 * @file driver_sniper.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Driver for simulation using snipersim
 */

#include <iostream>
#include <algorithm>
#include <time.h>
#include <string>
#include <cmath>

#include "Matrix/CRS.hpp"
#include "Matrix/Triplet.hpp"
#include "Util/VectorUtill.hpp"
#include "Util/DriverUtil.hpp"

#include "omp.h"

#include <sim_api.h>

void printErrorMsg() {
    std::cout << "You need to provide the correct command line arguments:" << std::endl;
    std::cout << "  1° Filename of Matrix market (.mtx extension). Filename starts with: " << std::endl;
    std::cout << "     1) Arbitrary matrix with no data present and filled in with ones" << std::endl;
    std::cout << "     2) Arbitrary matrix with no data present and random fill in" << std::endl;
    std::cout << "     3) Symmetric matrix with only lower half entries with data present" << std::endl;
    std::cout << "     4) Symmetric matrix with only lower half entries without data and filled in with ones" << std::endl;
    std::cout << "     5) Symmetric matrix with only lower half entries without data and filled in randomly" << std::endl;
    std::cout << "     Other) Arbitrary matrix with data present" << std::endl;
    std::cout << "  1° Kronecker graph input file (.bin extension). Filename starts with size and then an indicator: " << std::endl;
    std::cout << "     1) Arbitrary matrix with no data present and filled in with ones" << std::endl;
    std::cout << "     2) Arbitrary matrix with no data present and random fill in" << std::endl;
    std::cout << "     3) Symmetric matrix with only lower half entries without data and filled in with ones" << std::endl;
    std::cout << "     Other) Symmetric matrix with only lower half entries without data and filled in randomly" << std::endl;

    pwm::printAvailableMethods(2);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printErrorMsg();
        return -1;
    }

    std::string input_file = argv[1];
    int method = std::stoi(argv[2]);
    int threads = 0;
    int partitions = 0;
    if (method > 1 && argc < 4) {
        // No amount of threads specified
        printErrorMsg();
        return -1;
    } else if (method > 1) {
        threads = std::stoi(argv[3]);
    }

    if ((method == 4 || method == 5 || method == 6 || method == 7) && argc < 5) {
        printErrorMsg();
        return -1;
    } else if (method == 4 || method == 5 || method == 6 || method == 7) {
        partitions = std::stoi(argv[4]);
    }
    
    // Select method
    pwm::SparseMatrix<data_t, index_t>* test_mat = pwm::selectType<data_t, index_t>(method, threads);

    if (test_mat == NULL) {
        printErrorMsg();
        return -1;
    }

    // Input matrix & initialize vectors
    pwm::Triplet<data_t, index_t> input_mat;
    pwm::loadMatrixFromFile(&input_mat, input_file);
    int mat_size = input_mat.row_size;

    test_mat->loadFromTriplets(&input_mat, partitions);
    
    data_t* x = new data_t[mat_size];
    data_t* y = new data_t[mat_size];
    std::generate(x, x+mat_size, pwm::randFloat<data_t>);

    SimMarker(1, 1);
    test_mat->mv(x,y);

    #pragma omp parallel for schedule(static) num_threads(threads)
    for (int pid = 0; pid < threads; ++pid) {
        std::generate(x+pid*pwm::integerCeil(mat_size, threads), 
                      x+std::min(mat_size, pwm::integerCeil(mat_size, threads)*(pid+1)), 
                      pwm::randFloat<data_t>);
    }
    SimMarker(2, 1);

    // Do simulation
    SimMarker(1, 2);
    test_mat->mv(x, y);
    SimMarker(2, 2);

#ifndef NDEBUG
    std::cout << "Result for checking measures: " << std::endl;
    pwm::printVector(y, mat_size);
#endif

    delete [] y;
    delete [] x;

    delete test_mat;
    
    return 0;
}
