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
            cl::sycl::queue sycl_queue;

            // Global threads limit
            oneapi::tbb::global_control global_limit;

        private:
            /**
             * @brief Invokes the MKL matrix and sets the CRS data
             */
            void generateMKLMat() {
                oneapi::mkl::sparse::init_matrix_handle(&mkl_mat);
                oneapi::mkl::sparse::set_csr_data(mkl_mat, this->nor, this->noc, oneapi::mkl::index_base::zero, this->row_start, this->col_ind, this->data_arr);
            }

        public:
            // Base constructor
            CRSMKL(): sycl_queue(cl::sycl::cpu_selector{}) {}

            // Base constructor
            CRSMKL(int threads): pwm::CRS<T, int_type>(threads), sycl_queue(cl::sycl::cpu_selector{}),
                                 global_limit(oneapi::tbb::global_control::max_allowed_parallelism, threads) {}

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                pwm::CRS<T, int_type>::generatePoissonMatrix(m, n, partitions);

                generateMKLMat();
            }

             /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partitions_am) {
                pwm::CRS<T, int_type>::loadFromTriplets(input, partitions_am);

                generateMKLMat();
            }

            /**
             * @brief Matrix vector product Ax = y by calling the MKL library
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {
                oneapi::mkl::sparse::gemv(sycl_queue, oneapi::mkl::transpose::nontrans, 1., mkl_mat, x, 0., y);
            }
    };

} // pwm

#endif // PWM_CRSMKL_HPP