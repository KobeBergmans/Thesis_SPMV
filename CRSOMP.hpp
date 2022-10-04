/**
 * @file CRSOMP.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using OpenMP
 * @version 0.1
 * @date 2022-10-01
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSOMP_HPP
#define PWM_CRSOMP_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "SparseMatrix.hpp"
#include "VectorUtill.hpp"

#include <omp.h>

namespace pwm {
    template<typename T, typename int_type>
    class CRSOMP: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Row start array for the CRS format
            int_type* row_start;
            
            // Column index array for the CRS format
            int_type* col_ind;

            // Data array which stores the actual nonzeros
            T* data_arr;

        public:
            // Base constructor
            CRSOMP() {}

            // Base constructor
            CRSOMP(int threads) {
                omp_set_num_threads(threads);
            }

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             *
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int threads) {
                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];

                pwm::fillPoisson(data_arr, row_start, col_ind, m, n);

                assert(row_start[0] == 0);
                assert(row_start[this->nor] == this->nnz);
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * Loop is parallelized using OpenMP
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {             
                #pragma omp parallel for shared(x, y) schedule(dynamic, 8) // We use dynamic scheduler because of the varying workload per row
                for (int_type i = 0; i < this->nor; ++i) {
                    T sum = 0.;
                    int_type j;
                    for (int_type k = row_start[i]; k < row_start[i+1]; ++k) {
                        j = col_ind[k];
                        sum += data_arr[k]*x[j];
                    }
                    
                    y[i] = sum;
                }
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * Loop is parallelized using OpenMP
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm
             * @param y Temporary vector to store calculations
             * @param it Amount of iterations for the algorithm
             */
            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int i = 0; i < it; ++i) {
                    this->mv(x, y);

                    T norm = pwm::norm2(y, this->nor);
                    
                    #pragma omp parallel for shared(x, y) schedule(static) // Static scheduler because workload is the same for each row
                    for (int i = 0; i < this->nor; ++i) {
                        y[i] /= norm;
                        x[i] = y[i];
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRSOMP_HPP