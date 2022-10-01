/**
 * @file driver.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Main executable for power method comparison
 * @version 0.1
 * @date 2022-09-29
 */

#include <iostream>
#include <algorithm>

#include "CRS.hpp"
#include "VectorUtill.hpp"

int main(int argc, char** argv) {
    // TODO: Select parallelisation method
    std::cout << "For now the basic sequential algorithm is used..." << std::endl;

    // TODO: Initialize matrix and vectors
    pwm::CRS<double, int> test_mat;
    test_mat.generatePoissonMatrix(3,3);

    double* x = new double[9];
    double* y = new double[9];
    std::fill(x, x+9, 1.);

    // TODO: Solve power method
    test_mat.powerMethod(x, y, 100);

    std::cout << "Solution of power method: " << std::endl;
    pwm::printVector(x, 9);
    pwm::printVector(y, 9);

    return 0;
}