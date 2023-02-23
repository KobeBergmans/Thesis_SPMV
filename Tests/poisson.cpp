/**
 * @file poisson.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Test suite for poisson implementation
 */

#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <cmath>

#include "../Matrix/SparseMatrix.hpp"
#include "GetMatrices.hpp"

#include "omp.h"
#include "oneapi/tbb.h"

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
    for (size_t mat_index = 0; mat_index < matrices.size(); ++mat_index) {
        pwm::SparseMatrix<double, int>* mat = matrices[mat_index];

        // Get omp max threads
        int max_threads = omp_get_max_threads();

        // If we have a TBB implementation set a global limiter to overwrite other limits
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, pwm::get_threads_for_matrix(mat_index));
        
        for (int partitions = 1; partitions <= std::min(max_threads*3, 3*3); ++partitions) {
            mat->generatePoissonMatrix(3, 3, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->mv(x,y);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(y[i] == real_sol[i]);
            }

            // If matrix is an omp or TBB matrix break because all executions are the same
            if ((mat_index-1) % 6 == 0 || (mat_index-2) % 6 == 0) {
                break;
            }
        }

        // Reset omp threads
        omp_set_num_threads(max_threads);
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
    for (size_t mat_index = 0; mat_index < matrices.size(); ++mat_index) {
        pwm::SparseMatrix<double, int>* mat = matrices[mat_index];
            
        // Get omp max threads
        int max_threads = omp_get_max_threads();

        // If we have a TBB implementation set a global limiter to overwrite other limits
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, pwm::get_threads_for_matrix(mat_index));

        for (int partitions = 1; partitions <= std::min(max_threads*3, 9*3); ++partitions) {
            mat->generatePoissonMatrix(9, 3, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->mv(x,y);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(y[i] == real_sol[i]);
            }

            // If matrix is an omp or TBB matrix break because all executions are the same
            if ((mat_index-1) % 6 == 0 || (mat_index-2) % 6 == 0) {
                break;
            }
        }


        // Reset omp threads
        omp_set_num_threads(max_threads);
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(poisson_powermethod)

BOOST_AUTO_TEST_CASE(powermethod_size_5_5, * boost::unit_test::tolerance(std::pow(10, -12))) {
    int mat_size = 5*5;

    // Precomputed solution using matlab
    double real_sol[] = {0.083333333337580, -0.144337567301084,  0.166666666668790, -0.144337567301084,  0.083333333337580, -0.144337567301084,  0.250000000000000, -0.288675134591135,  0.250000000000000, -0.144337567301084,  0.166666666668790, -0.288675134591135,  0.333333333324839, -0.288675134591135,  0.166666666668790, -0.144337567301084,  0.250000000000000, -0.288675134591135,  0.250000000000000, -0.144337567301084,  0.083333333337580, -0.144337567301084,  0.166666666668790, -0.144337567301084,
   0.083333333337580};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (size_t mat_index = 0; mat_index < matrices.size(); ++mat_index) {
        pwm::SparseMatrix<double, int>* mat = matrices[mat_index];

        // Get omp max threads
        int max_threads = omp_get_max_threads();

        // If we have a TBB implementation set a global limiter to overwrite other limits
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, pwm::get_threads_for_matrix(mat_index));
        
        for (int partitions = 1; partitions <= std::min(max_threads*3, 5*5); ++partitions) {
            mat->generatePoissonMatrix(5, 5, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->powerMethod(x, y, 100);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(x[i] == real_sol[i]);
            }

            // If matrix is an omp or TBB matrix break because all executions are the same
            if ((mat_index-1) % 6 == 0 || (mat_index-2) % 6 == 0) {
                break;
            }
        }

        // Reset omp threads
        omp_set_num_threads(max_threads);
    }
}

BOOST_AUTO_TEST_CASE(powermethod_size_10_5, * boost::unit_test::tolerance(std::pow(10, -12))) {
    int mat_size = 10*5;

    // Precomputed solution using matlab
    double real_sol[] = {0.066549515155803, -0.111968981176319,  0.121838215857833, -0.093025002550037,  0.034678148918472,  0.034678148918472, -0.093025002550038,  0.121838215857834, -0.111968981176319,  0.066549515155803, -0.115267141466527,  0.193935964265070, -0.211029980164918,  0.161124030787534, -0.060064315837982, -0.060064315837983,  0.161124030787535, -0.211029980164918,  0.193935964265070, -0.115267141466527,  0.133099030307450, -0.223937962345645,  0.243676431708057, -0.186050005094264,  0.069356297834777,  0.069356297834778, -0.186050005094265,  0.243676431708058, -0.223937962345645,  0.133099030307450, -0.115267141466527,  0.193935964265070, -0.211029980164918,  0.161124030787534, -0.060064315837982, -0.060064315837983,  0.161124030787535, -0.211029980164918,  0.193935964265071, -0.115267141466527,  0.066549515155803, -0.111968981176319,  0.121838215857833, -0.093025002550037,  0.034678148918472,  0.034678148918472, -0.093025002550038,  0.121838215857834, -0.111968981176319, 
   0.066549515155803};


    // Get datastructures
    std::vector<pwm::SparseMatrix<double, int>*> matrices = pwm::get_all_matrices<double, int>();
    double* x = new double[mat_size];
    double* y = new double[mat_size];

    // Run test on all the matrices
    for (size_t mat_index = 0; mat_index < matrices.size(); ++mat_index) {
        pwm::SparseMatrix<double, int>* mat = matrices[mat_index];

        // Get omp max threads
        int max_threads = omp_get_max_threads();

        // If we have a TBB implementation set a global limiter to overwrite other limits
        tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, pwm::get_threads_for_matrix(mat_index));

        for (int partitions = 1; partitions <= std::min(max_threads*3, 10*5); ++partitions) {
            mat->generatePoissonMatrix(10, 5, partitions);
            std::fill(x, x+mat_size, 1.);
            mat->powerMethod(x, y, 100);

            // Check solution
            for (int i = 0; i < mat_size; ++i) {
                BOOST_TEST(x[i] == real_sol[i]);
            }

            // If matrix is an omp or TBB matrix break because all executions are the same
            if ((mat_index-1) % 6 == 0 || (mat_index-2) % 6 == 0) {
                break;
            }
        }

        // Reset omp threads
        omp_set_num_threads(max_threads);
    }
}

BOOST_AUTO_TEST_SUITE_END()