/**
 * @file CRSTBBGraph.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using TBB Graph 
 * @version 0.2
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
#include <thread>

#include "SparseMatrix.hpp"
#include "Utill/VectorUtill.hpp"
#include "Utill/Poisson.hpp"
#include "Utill/TripletToCRS.hpp"

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

            // Amount of partitions
            int partitions;

            // Graph for TBB nodes
            flow::graph g;

            // TBB nodes list
            std::vector<flow::function_node<std::tuple<const T*, T*>, int>> n_list;

            // Global threads limit
            tbb::global_control global_limit;

        public:
            // Base constructor
            CRSTBBGraph() {}

            // Base constructor
            CRSTBBGraph(int threads):
            global_limit(tbb::global_control::max_allowed_parallelism, threads) {}

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * The matrix is partitioned for each thread 
             * This is done by splitting the rows equally, this is only optimal because every row has approximately the same elements.
             * 
             * Then each Matrix part gets its own TBB function_node which is used to calculate the matrix vector product of the given partition.
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             * @param partitions_am The amount of partitions the matrix is partitioned in
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions_am) {
                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                partitions = partitions_am;

                row_start = new int_type*[partitions];
                col_ind = new int_type*[partitions];
                data_arr = new T*[partitions];

                // Generate data for each thread
                int_type am_rows = std::round(m*n/partitions);
                int_type first_row = 0;
                int_type last_row = 0;
                int_type thread_rows;
                for (int i = 0; i < partitions; ++i) {
                    first_row = last_row;

                    if (i == partitions - 1) last_row = m*n;
                    else last_row = first_row + am_rows;
                    thread_rows = last_row - first_row;

                    // Generate datastructures for this thread CRS (data_arr & col_ind are sometimes too large...)
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

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type> input, const int partitions_am) {
                this->noc = input.col_size;
                this->nor = input.row_size;
                this->nnz = input.nnz;

                partitions = partitions_am;

                row_start = new int_type*[partitions];
                col_ind = new int_type*[partitions];
                data_arr = new T*[partitions];
                int_type* thread_rows = new int_type[partitions];
                int_type* first_rows = new int_type[partitions];

                // Generate data for each thread
                pwm::TripletToMultipleCRS(input.row_coord, input.col_coord, input.data, row_start, col_ind, data_arr, 
                                          partitions, thread_rows, first_rows, this->nnz, this->nor);

                // Generate function nodes per thread
                for (int i = 0; i < partitions; ++i) {
                    // Create node for this thread
                    flow::function_node<std::tuple<const T*, T*>, int> n(g, 1, [=](std::tuple<const T*, T*> input) -> int {
                        const T* x = std::get<0>(input);
                        T* y = std::get<1>(input);

                        int_type j;
                        for (int_type l = 0; l < thread_rows[i]; ++l) {
                            T sum = 0;
                            for (int_type k = row_start[i][l]; k < row_start[i][l+1]; ++k) {
                                j = col_ind[i][k];
                                sum += data_arr[i][k]*x[j];
                            }
                            y[l+first_rows[i]] = sum;
                        }

                        return 0;
                    });

                    n_list.push_back(n);
                }
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * The loop is parallelized using different graph nodes from TBB for each thread.
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {   
                for (int i = 0; i < partitions; ++i) {
                    n_list[i].try_put(std::make_tuple(x,y));
                }
                
                g.wait_for_all();
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * Loop is parallelized using parallel_for from TBB
             * 
             * @param x Input vector to start calculation, contains the output at the end of the algorithm is it is uneven
             * @param y Vector to store calculations, contains the output at the end of the algorithm if it is even
             * @param it Amount of iterations for the algorithm
             */
            void powerMethod(T* x, T* y, const int_type it) {
                assert(this->nor == this->noc); //Power method only works on square matrices
                
                for (int it_nb = 0; it_nb < it; ++it_nb) {
                    if (it_nb % 2 == 0) {
                        this->mv(x, y);

                        T norm = pwm::norm2(y, this->nor);

                        tbb::parallel_for(0, this->nor, [=](int_type i) {
                            y[i] /= norm;
                        });
                    } else {
                        this->mv(y, x);

                        T norm = pwm::norm2(x, this->nor);

                        tbb::parallel_for(0, this->nor, [=](int_type i) {
                            x[i] /= norm;
                        });
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRSTBBGRAPH_HPP