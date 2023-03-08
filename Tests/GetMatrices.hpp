/**
 * @file GetMatrices.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Includes a function to return all possible matrices on this machine
 */

#ifndef PWM_GETMATRICES_HPP
#define PWM_GETMATRICES_HPP

#include <vector>

#include "../Matrix/CRS.hpp"
#include "../Env_Implementations/CRSOMP.hpp"
#include "../Env_Implementations/CRSTBB.hpp"
#include "../Env_Implementations/CRSTBBGraph.hpp"
#include "../Env_Implementations/CRSTBBGraphPinned.hpp"
#include "../Env_Implementations/CRSThreadPool.hpp"
#include "../Env_Implementations/CRSThreadPoolPinned.hpp"
#include "../SOA_Implementations/CRS_Merge.hpp"
#include "../SOA_Implementations/CSB.hpp"
#include "../SOA_Implementations/BlockCOH.hpp"
#include "../Matrix/SparseMatrix.hpp"

#include "omp.h"

namespace pwm {
    template<typename T, typename int_type>
    std::vector<pwm::SparseMatrix<T, int_type>*> get_all_matrices() {
        std::vector<pwm::SparseMatrix<T, int_type>*> matrices;
        matrices.push_back(new pwm::CRS<T, int_type>(1));
        for (int i = 1; i <= omp_get_max_threads(); ++i) {
            matrices.push_back(new pwm::CRSOMP<T, int_type>(i));
            matrices.push_back(new pwm::CRSTBB<T, int_type>(i));
            matrices.push_back(new pwm::CRSTBBGraph<T, int_type>(i));
            matrices.push_back(new pwm::CRSTBBGraphPinned<T, int_type>(i));
            matrices.push_back(new pwm::CRSThreadPool<T, int_type>(i));
            matrices.push_back(new pwm::CRSThreadPoolPinned<T, int_type>(i));
            matrices.push_back(new pwm::CRS_Merge<T, int_type>(i));
            matrices.push_back(new pwm::CSB<T, int_type>(i));
            matrices.push_back(new pwm::BlockCOH<T, int_type>(i));
        }
        return matrices;
    }

    int get_threads_for_matrix(int index) {
        if (index == 0) return 1;

        return std::floor((index - 1)/6.) + 1;
    }
} // namespace pwm

#endif