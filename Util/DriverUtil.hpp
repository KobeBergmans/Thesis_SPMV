/**
 * @file DriverUtil.hpp
 * @author your name (you@domain.com)
 * @brief Helper functions to make drivers more streamlined and less error prone
 */

#ifndef PWM_DRIVERUTIL_HPP
#define PWM_DRIVERUTIL_HPP

#include "../Matrix/SparseMatrix.hpp"
#include "../Matrix/CRS.hpp"
#include "../Env_Implementations/CRSOMP.hpp"
#include "../Env_Implementations/CRSTBB.hpp"
#include "../Env_Implementations/CRSTBBGraph.hpp"
#include "../Env_Implementations/CRSTBBGraphPinned.hpp"
#include "../Env_Implementations/CRSThreadPool.hpp"
#include "../Env_Implementations/CRSThreadPoolPinned.hpp"
#include "../SOA_Implementations/CRS_Merge.hpp"
#include "../SOA_Implementations/CSB.hpp"

namespace pwm {
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
            
            case 8:
                return new pwm::CRS_Merge<T, int_type>(threads);

            case 9:
                return new pwm::CSB<T, int_type>(threads);
            
            default:
                return NULL;
        }
    }
} // namespace pwm


#endif // PWM_DRIVERUTIL_HPP