/**
 * @file CRS.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class
 * @version 0.2
 * @date 2022-09-29
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRS_HPP
#define PWM_CRS_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "../Matrix/SparseMatrix.hpp"
#include "../Matrix/Triplet.hpp"
#include "../Util/VectorUtill.hpp"
#include "../Util/Poisson.hpp"
#include "../Util/TripletToCRS.hpp"

namespace pwm {
    template<typename T, typename int_type>
    class CRS: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Row start array for the CRS format
            int_type* row_start;
            
            // Column index array for the CRS format
            int_type* col_ind;

            // Data array which stores the actual nonzeros
            T* data_arr;

        public:
            // Base constructor
            CRS() {}

            // Base constructor
            CRS(int threads) {}

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

                pwm::fillPoisson(data_arr, row_start, col_ind, m, n);

                assert(row_start[0] == 0);
                assert(row_start[this->nor] == this->nnz);
            }

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partitions_am) {
                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;
                
                row_start = new int_type[this->nor+1];
                col_ind = new int_type[this->nnz];
                data_arr = new T[this->nnz];
 
                pwm::TripletToCRS(input.row_coord, input.col_coord, input.data, row_start, col_ind, data_arr, this->nnz, this->nor);
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {
                std::fill(y, y+this->nor, 0.);

                int_type j;
                for (int_type i = 0; i < this->nor; ++i) {
                    for (int_type k = row_start[i]; k < row_start[i+1]; ++k) {
                        j = col_ind[k];
                        y[i] = y[i] + data_arr[k]*x[j];
                    }
                }
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm is it is uneven
             * @param y Vector to store calculations, contains the output at the end of the algorithm if it is even
             * @param it Amount of iterations for the algorithm
             */
            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int i = 0; i < it; ++i) {
                    if (i % 2 == 0) {
                        this->mv(x,y);
                        pwm::normalize(y, this->nor);
                    } else {
                        this->mv(y,x);
                        pwm::normalize(x, this->nor);
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRS_HPP