/**
 * @file CRSMKL.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief CRS class which uses the Intel Math Kernel Library to perform SpMV
 */

#ifndef PWM_CRSMKL_HPP
#define PWM_CRSMKL_HPP

#include "../Matrix/CRS.hpp"

#include "oneapi/mkl.hpp"
#include "CL/sycl.hpp"

namespace pwm {
    template<typename T, typename int_type>
    class CRSMKL: public pwm::CRS<T, int_type> {
        protected:
            // MKL sparse matrix type
            oneapi::mkl::sparse::matrix_handle_t mkl_mat;

            // SYCL queue for SpMV execution
            cl::sycl::queue sycl_queue(cl::sycl::cpu_selector);

        public:
            // Base constructor
            CRSMKL() {}

            // Base constructor
            CRSMKL(int threads): pwm::CRS<T, int_type>(threads) {}

             /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partitions_am) {
                pwm::CRS<T, int_type>::loadFromTriplets(input, partitions_am);

                oneapi::mkl::sparse::init_matrix_handle(&mkl_mat);
                oneapi::mkl::sparse::set_csr_data(mkl_mat, this->nor, this->noc, oneapi::mkl::index_base::zero, this->row_start, this->col_ind, this->data_arr);
            }
    };

} // pwm

#endif // PWM_CRSMKL_HPP