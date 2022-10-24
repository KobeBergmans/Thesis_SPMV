/**
 * @file poisson.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Test suite for poisson implementation
 * @version 0.1
 * @date 2022-10-24
 */

#define BOOST_TEST_MODULE test_poisson
#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <cmath>

#include "../SparseMatrix.hpp"
#include "GetMatrices.hpp"

#include "omp.h"

BOOST_AUTO_TEST_SUITE(poisson_mv)

BOOST_AUTO_TEST_CASE(mv_size_3_3, * boost::unit_test::tolerance(std::pow(10, -14))) {
    int mat_size = 3*3;

    // Precomputed solution using matlab
    double real_sol[] = {2., 1., 2., 1., 0., 1., 2., 1., 2.};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (pwm::SparseMatrix<double, int>* mat: matrices) {
        for (int partitions = 1; partitions <= std::max(omp_get_max_threads()*3, 3*3); ++partitions) {
            mat->generatePoissonMatrix(3, 3, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->mv(x,y);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(y[i] == real_sol[i]);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(mv_size_9_3, * boost::unit_test::tolerance(std::pow(10, -14))) {
    int mat_size = 9*3;

    // Precomputed solution using matlab
    double real_sol[] = {2., 1., 1., 1., 1., 1., 1., 1., 2., 1., 0., 0., 
                         0., 0., 0., 0., 0., 1., 2., 1., 1., 1., 1., 1., 1., 1., 2.};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (pwm::SparseMatrix<double, int>* mat: matrices) {
        for (int partitions = 1; partitions <= std::max(omp_get_max_threads()*3, 9*3); ++partitions) {
            mat->generatePoissonMatrix(9, 3, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->mv(x,y);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(y[i] == real_sol[i]);
            }
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(poisson_powermethod)

BOOST_AUTO_TEST_CASE(powermethod_size_5_5, * boost::unit_test::tolerance(std::pow(10, -14))) {
    int mat_size = 5*5;

    // Precomputed solution using matlab
    double real_sol[] = {-0.083333333333333, 0.144337567297407,-0.166666666666667, 0.144337567297406,-0.083333333333333, 
                         0.144337567297406, -0.250000000000000, 0.288675134594813, -0.250000000000000, 0.144337567297406, 
                         -0.166666666666667, 0.288675134594813, -0.333333333333333, 0.288675134594813, -0.166666666666667, 
                         0.144337567297406, -0.250000000000000, 0.288675134594813,-0.250000000000000, 0.144337567297406,
                         -0.083333333333333, 0.144337567297406,-0.166666666666667, 0.144337567297406,-0.083333333333333};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (pwm::SparseMatrix<double, int>* mat: matrices) {
        for (int partitions = 1; partitions <= std::max(omp_get_max_threads()*3, 5*5); ++partitions) {
            mat->generatePoissonMatrix(5, 5, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->powerMethod(x, y, 100);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(x[i] == real_sol[i]);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(powermethod_size_10_5, * boost::unit_test::tolerance(std::pow(10, -14))) {
    int mat_size = 10*5;

    // Precomputed solution using matlab
    double real_sol[] = {-0.034678880479031, 0.066548284304895,-0.093026341914262, 0.111967958550694,
                         -0.121838597084438, 0.121838597084437,-0.111967958550693, 0.093026341914261,
                         -0.066548284304894, 0.034678880479031, 0.060065582939291,-0.115265009572617, 
                         0.161126350637777,-0.193934193029568, 0.211030640473159,-0.211030640473159, 
                         0.193934193029566,-0.161126350637774, 0.115265009572615,-0.060065582939289,
                         -0.069357760958063, 0.133096568609790,-0.186052683828525, 0.223935917101388,
                         -0.243677194168875, 0.243677194168874,-0.223935917101386, 0.186052683828522,
                         -0.133096568609787, 0.069357760958061, 0.060065582939291,-0.115265009572617, 
                         0.161126350637776,-0.193934193029568, 0.211030640473159,-0.211030640473158, 
                         0.193934193029565,-0.161126350637773, 0.115265009572614,-0.060065582939289,
                         -0.034678880479032, 0.066548284304895,-0.093026341914262, 0.111967958550694,
                         -0.121838597084438, 0.121838597084437,-0.111967958550692, 0.093026341914261,
                         -0.066548284304893, 0.034678880479030};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (pwm::SparseMatrix<double, int>* mat: matrices) {
        for (int partitions = 1; partitions <= std::max(omp_get_max_threads()*3, 10*5); ++partitions) {
            mat->generatePoissonMatrix(10, 5, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->powerMethod(x, y, 100);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(x[i] == real_sol[i]);
            }
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()