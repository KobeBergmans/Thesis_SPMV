/**
 * @file DriverUtil.hpp
 * @author your name (you@domain.com)
 * @brief Helper functions to make drivers more streamlined and less error prone
 */

#ifndef PWM_DRIVERUTIL_HPP
#define PWM_DRIVERUTIL_HPP

#include <iostream>
#include <string>
#include <random>

#include "../Matrix/SparseMatrix.hpp"
#include "../Matrix/CRS.hpp"
#include "../Env_Implementations/CRSOMP.hpp"
#include "../Env_Implementations/CRSThreadPool.hpp"
#include "../Env_Implementations/CRSThreadPoolPinned.hpp"
#include "../SOA_Implementations/CRS_Merge.hpp"
#include "../SOA_Implementations/CSB.hpp"
#include "../SOA_Implementations/BlockCOH.hpp"

#ifndef NTBB
#include "../Env_Implementations/CRSTBB.hpp"
#include "../Env_Implementations/CRSTBBGraph.hpp"
#include "../Env_Implementations/CRSTBBGraphPinned.hpp"
#endif

#ifdef MKL
#include "../Env_Implementations/CRSMKL.hpp"
#endif

#include <boost/algorithm/string/predicate.hpp>

#include "omp.h"

namespace pwm {
    template<typename T, typename int_type>
    pwm::SparseMatrix<T, int_type>* selectType(int method, int threads) {
        if (threads == -1) {
            threads = omp_get_max_threads();
        }

        switch (method) {
            case 1:
                return new pwm::CRS<T, int_type>(threads);

            case 2:
                return new pwm::CRSOMP<T, int_type>(threads);

#ifndef NTBB
            case 3:
                return new pwm::CRSTBB<T, int_type>(threads);

            case 4:
                return new pwm::CRSTBBGraph<T, int_type>(threads);

            case 5:
                return new pwm::CRSTBBGraphPinned<T, int_type>(threads);
#endif
            case 6:
                return new pwm::CRSThreadPool<T, int_type>(threads);

            case 7:
                return new pwm::CRSThreadPoolPinned<T, int_type>(threads);
            
            case 8:
                return new pwm::CRS_Merge<T, int_type>(threads);

            case 9:
                return new pwm::CSB<T, int_type>(threads);

            case 10:
                return new pwm::BlockCOH<T, int_type>(threads);

#ifdef MKL
            case 11:
                return new pwm::CRSMKL<T, int_type>(threads);
#endif
            
            default:
                return NULL;
        }
    }

    void printAvailableMethods(int startNb) {
        std::cout << "  " << startNb << "° Method to use:" << std::endl;
        std::cout << "     1)  Standard CRS (sequential)" << std::endl;
        std::cout << "     2)  CRS parallelized using OpenMP" << std::endl;
#ifndef NTBB
        std::cout << "     3)  CRS parallelized using TBB" << std::endl;
        std::cout << "     4)  CRS parallelized using TBB graphs" << std::endl;
        std::cout << "     5)  CRS parallelized using TBB graphs with each node pinned to a CPU" << std::endl;
#endif
        std::cout << "     6)  CRS parallelized using Boost Thread Pool" << std::endl;
        std::cout << "     7)  CRS parallelized using Boost Thread Pool with functions pinned to a CPU" << std::endl;
        std::cout << "     8)  CRS parallelized using the merge-sort method" << std::endl;
        std::cout << "     9)  CSB parallelized using OpenMP tasks" << std::endl;
        std::cout << "     10) Row distributed block CO-H" << std::endl;
#ifdef MKL
        std::cout << "     11) SpMV using Intel MKL library parallelized with TBB" << std::endl;
#endif
        std::cout << "  " << startNb +1 << "° Amount of threads (only for a parallel method).";
        std::cout << " -1 lets the program choose the amount of threads arbitrarily" << std::endl;
        std::cout << "  " << startNb + 2 << "° Amount of partitions the matrix is split up into (only for method 4, 5, 6 and 7)" << std::endl;
    }

    template<typename T, typename int_type>
    void loadMatrixFromFile(pwm::Triplet<T, int_type>* input_mat, std::string input_file) {
        int file_start = input_file.find("/");
        if (boost::algorithm::ends_with(input_file, ".mtx")) {
            int indicator = std::stoi(input_file.substr(file_start+1, 1));
            if (indicator == 1) {
                input_mat->loadFromMM(input_file, false, false, false);
            } else if (indicator == 2) {
                input_mat->loadFromMM(input_file, false, false, true);
            } else if (indicator == 3) {
                input_mat->loadFromMM(input_file, true, true);
            } else if (indicator == 4) {
                input_mat->loadFromMM(input_file, false, true, false);
            } else if (indicator == 5) {
                input_mat->loadFromMM(input_file, false, true, true);
            } else {
                input_mat->loadFromMM(input_file, true, false);
            }
        } else if (boost::algorithm::ends_with(input_file, ".bin")) {
            int first_ = input_file.find("_");
            int mat_size = std::stoi(input_file.substr(file_start+1, first_-file_start-1));
            int indicator = std::stoi(input_file.substr(first_+1, 1));

            if (indicator == 1) {
                input_mat->loadFromBin(input_file, mat_size, false, false);
            } else if (indicator == 2) {
                input_mat->loadFromBin(input_file, mat_size, false, true);
            } else if (indicator == 3) {
                input_mat->loadFromBin(input_file, mat_size, true, false);
            } else {
                input_mat->loadFromBin(input_file, mat_size, true, true);
            }
        }
    }

    template<typename T>
    T randFloat() {
        return MIN_IN + (T)std::rand() / RAND_MAX * (MAX_IN - MIN_IN);    
    }
} // namespace pwm


#endif // PWM_DRIVERUTIL_HPP