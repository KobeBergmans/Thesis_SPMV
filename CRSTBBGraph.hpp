/**
 * @file CRSTBBGraph.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using TBB Graph 
 * @version 0.1
 * @date 2022-10-03
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSTBBGRAPH_HPP
#define PWM_CRSTBBGRAPH_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <tuple>

#include "SparseMatrix.hpp"
#include "VectorUtill.hpp"

#include "oneapi/tbb.h"

namespace tbb = oneapi::tbb;
namespace flow = oneapi::tbb::flow;

namespace pwm {
    template<typename T, typename int_type>
    class CRSTBBGraph: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Array of row start arrays for the CRS format. 1 for each thread.
            int_type** row_start;
            
            // Array of column index array for the CRS format. 1 for each thread
            int_type** col_ind;

            // Array of data array which stores the actual nonzeros. 1 for each thread.
            T** data_arr;

            // Amount of threads
            int threads;

            // TBB graph object
            flow::graph g;

            // TBB nodes list
            std::vector<flow::function_node<std::tuple<const T*, T*>, int>> n_list;

        public:
            // Base constructor
            CRSTBBGraph() {}

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * https://en.wikipedia.org/wiki/Discrete_Poisson_equation
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int threads_am) {
                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                threads = threads_am;

                row_start = new int_type*[threads];
                col_ind = new int_type*[threads];
                data_arr = new T*[threads];

                // Generate data for each thread
                int_type am_rows = std::round(m*n/threads);
                int_type first_row = 0;
                int_type last_row = 0;
                int_type thread_rows;
                for (int i = 0; i < threads; ++i) {
                    first_row = last_row;

                    if (i == threads - 1) last_row = m*n;
                    else last_row = first_row + am_rows;
                    thread_rows = last_row - first_row;

                    // Generate datastructures for this thread CRS
                    // TODO: The size of data_arr & col_ind is not exactly right
                    data_arr[i] = new T[5*thread_rows];
                    row_start[i] = new int_type[thread_rows+1];
                    col_ind[i] = new int_type[5*thread_rows];
                    
                    // Fill CRS matrix for given thread
                    pwm::fillPoisson(data_arr[i], row_start[i], col_ind [i], m, n, first_row, last_row);

                    // Create node for this thread
                    flow::function_node<std::tuple<const T*, T*>, int> n(g, 1, [=](std::tuple<const T*, T*> input) -> int {
                        const T* x = std::get<0>(input);
                        T* y = std::get<1>(input);

                        int_type j;
                        for (int_type l = 0; l < thread_rows; ++l) {
                            T sum = 0;
                            for (int_type k = row_start[i][l]; k < row_start[i][l+1]; ++k) {
                                j = col_ind[i][k];
                                sum += data_arr[i][k]*x[j];
                            }
                            y[l+first_row] = sum;
                        }

                        return 0;
                    });

                    n_list.push_back(n);
                }
                
            }

            void mv(const T* x, T* y) {   
                for (int i = 0; i < threads; ++i) {
                    n_list[i].try_put(std::make_tuple(x,y));
                }
                
                g.wait_for_all();
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

#endif // PWM_CRSTBBGRAPH_HPP