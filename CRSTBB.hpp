/**
 * @file CRSTBB.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using TBB
 * @version 0.1
 * @date 2022-10-03
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSTBB_HPP
#define PWM_CRSTBB_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "SparseMatrix.hpp"
#include "VectorUtill.hpp"

#include "oneapi/tbb.h"

namespace tbb = oneapi::tbb;

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

        public:
            // Base constructor
            CRSTBB() {}

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * https://en.wikipedia.org/wiki/Discrete_Poisson_equation
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

#ifndef NDEBUG
                assert(row_start[0] == 0);
                assert(row_start[this->nor] == this->nnz);

                std::cout << "Row start: " << std::endl;
                pwm::printVector(row_start, this->nor+1);

                std::cout << "Col ind: " << std::endl;
                pwm::printVector(col_ind, this->nnz);

                std::cout << "Data: " << std::endl;
                pwm::printVector(data_arr, this->nnz);
#endif
            }

            void mv(const T* x, T* y) {   
                tbb::parallel_for(0, this->nor, [=](int_type i) {
                    T sum = 0.;
                    int_type j;
                    for (int_type k = row_start[i]; k < row_start[i+1]; ++k) {
                        j = col_ind[k];
                        sum += data_arr[k]*x[j];
                    }
                    
                    y[i] = sum;
                });
            }

            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int i = 0; i < it; ++i) {
                    this->mv(x, y);

                    T norm = pwm::norm2(y, this->nor);
                    
                    tbb::parallel_for(0, this->nor, [=](int_type i) {
                        y[i] /= norm;
                        x[i] = y[i];
                    });
                }
            }
    };
} // namespace pwm

#endif // PWM_CRSTBB_HPP