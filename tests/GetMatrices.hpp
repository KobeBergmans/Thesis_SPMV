/**
 * @file GetMatrices.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Includes a function to return all possible matrices on this machine
 * @version 0.1
 * @date 2022-10-24
 */

#ifndef PWM_GETMATRICES_HPP
#define PWM_GETMATRICES_HPP

#include <vector>

#include "../CRS.hpp"
#include "../CRSOMP.hpp"
#include "../CRSTBB.hpp"
#include "../CRSTBBGraph.hpp"
#include "../CRSTBBGraphPinned.hpp"
#include "../CRSThreadPool.hpp"
#include "../CRSThreadPoolPinned.hpp"
#include "../SparseMatrix.hpp"

#include "omp.h"

namespace pwm {
    template<typename T, typename int_type>
    std::vector<pwm::SparseMatrix<T, int_type>*> get_all_matrices() {
        std::vector<pwm::SparseMatrix<double, int>*> matrices;
        matrices.push_back(new pwm::CRS<double, int>(1));
        for (int i = 1; i <= omp_get_max_threads(); ++i) {
            matrices.push_back(new pwm::CRSOMP<double, int>(i));
            matrices.push_back(new pwm::CRSTBB<double, int>(i));
            matrices.push_back(new pwm::CRSTBBGraph<double, int>(i));
            matrices.push_back(new pwm::CRSTBBGraphPinned<double, int>(i));
            matrices.push_back(new pwm::CRSThreadPool<double, int>(i));
            matrices.push_back(new pwm::CRSThreadPoolPinned<double, int>(i));
        }
        return matrices;
    }

    int get_threads_for_matrix(int index) {
        if (index == 0) return 1;

        return std::floor((index - 1)/6.) + 1;
    }
} // namespace pwm

#endif