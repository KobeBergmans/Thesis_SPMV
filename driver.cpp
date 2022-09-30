/**
 * @file driver.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison
 * @version 0.1
 * @date 2022-09-29
 */

#include <iostream>

#include "CRS.hpp"

int main(int argc, char** argv) {
    // TODO: Select parallelisation method
    std::cout << "For now the basic sequential algorithm is used..." << std::endl;

    // TODO: Initialize matrix
    pwm::CRS<double, int> test_mat;
    test_mat.generatePoissonMatrix(3,3);

    std::vector<double> x(9,1.);
    std::vector<double> test = test_mat.mv(x);

    std::cout << "Test: " << std::endl;
    for (int i = 0; i < 9; ++i) {
        std::cout << test[i] << ", ";
    }
    std::cout << std::endl;

    // TODO: Solve power method

    return 0;
}