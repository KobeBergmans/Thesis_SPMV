/**
 * @file CRSTBB.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using TBB
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSTBB_HPP
#define PWM_CRSTBB_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "../Matrix/SparseMatrix.hpp"
#include "../Util/VectorUtill.hpp"
#include "../Util/Poisson.hpp"

#include "oneapi/tbb.h"

namespace pwm {
    template<typename T, typename int_type>
    class CRSTBB: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Row start array for the CRS format
            int_type* row_start;
            
            // Column index array for the CRS format
            int_type* col_ind;

            // Data array which stores the actual nonzeros
            T* data_arr;

            // Global threads limit
            oneapi::tbb::global_control global_limit;

        public:
            // Base constructor
            CRSTBB() {}

            // Base constructor
            CRSTBB(int threads): global_limit(oneapi::tbb::global_control::max_allowed_parallelism, threads) {}

            // Deconstructor
            ~CRSTBB() {
                delete [] row_start;
                delete [] col_ind;
                delete [] data_arr;

                row_start = NULL;
                col_ind = NULL;
                data_arr = NULL;
            }

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             *
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions) {
                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];

                pwm::fillPoissonTBB(data_arr, row_start, col_ind, m, n);

                assert(row_start[0] == 0);
                assert(row_start[this->nor] == this->nnz);
            }

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partition_am) {
                this->noc = input->col_size;
                this->nor = input->row_size;
                this->nnz = input->nnz;

                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];

                pwm::TripletToCRSTBB(input->row_coord, input->col_coord, input->data, row_start, col_ind, data_arr, this->nnz, this->nor);
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * Loop is parallelized using parallel_for function from TBB
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {   
                oneapi::tbb::parallel_for((int_type)0, this->nor, [=](int_type i) {
                    T sum = 0.;
                    for (int_type k = row_start[i]; k < row_start[i+1]; ++k) {
                        sum += data_arr[k]*x[col_ind[k]];
                    }
                    
                    y[i] = sum;
                });
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * Loop is parallelized using parallel_for function of TBB
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm is it is uneven
             * @param y Vector to store calculations, contains the output at the end of the algorithm if it is even
             * @param it Amount of iterations for the algorithm
             */
            void powerIteration(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int it_nb = 0; it_nb < it; ++it_nb) {
                    if (it_nb % 2 == 0) {
                        this->mv(x, y);

                        T norm = pwm::norm2(y, this->nor);

                        oneapi::tbb::parallel_for((int_type)0, this->nor, [=](int_type i) {
                            y[i] /= norm;
                        });
                    } else {
                        this->mv(y, x);

                        T norm = pwm::norm2(x, this->nor);

                        oneapi::tbb::parallel_for((int_type)0, this->nor, [=](int_type i) {
                            x[i] /= norm;
                        });
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRSTBB_HPP