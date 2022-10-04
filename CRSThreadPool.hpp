/**
 * @file CRSThreadPool.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using Boost thread pool
 * @version 0.1
 * @date 2022-10-03
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSTHREADPOOL_HPP
#define PWM_CRSTHREADPOOL_HPP

#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>

#include "SparseMatrix.hpp"
#include "VectorUtill.hpp"

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

namespace pwm {
    template<typename T, typename int_type>
    class CRSThreadPool: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Array of row start arrays for the CRS format. 1 for each thread.
            int_type** row_start;
            
            // Array of column index array for the CRS format. 1 for each thread
            int_type** col_ind;

            // Array of data array which stores the actual nonzeros. 1 for each thread.
            T** data_arr;

            // Amount of threads
            int threads;

            // Thread pool
            boost::asio::thread_pool pool;

            // mv Function list
            std::vector<std::function<void(const T*, T*)>> mv_function_list;

            // Normalize Function list
            std::vector<std::function<void(T*, T*, T)>> norm_function_list;

        public:
            // Base constructor
            CRSThreadPool() {}

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

                    // Create mv lambda function for this thread
                    std::function<void(const T*, T*)> mv_func = [=](const T* x, T* y) -> void {
                        int_type j;
                        for (int_type l = 0; l < thread_rows; ++l) {
                            T sum = 0;
                            for (int_type k = row_start[i][l]; k < row_start[i][l+1]; ++k) {
                                j = col_ind[i][k];
                                sum += data_arr[i][k]*x[j];
                            }
                            y[l+first_row] = sum;
                        }
                    };

                    mv_function_list.push_back(mv_func);

                    // Create normalize function for this thread
                    std::function<void(T*, T*, T)> norm_func = [=](T* x, T* y, T norm) -> void {
                        for (int_type l = 0; l < thread_rows; ++l) {
                            y[l+first_row] /= norm;
                            x[l+first_row] = y[l+first_row];
                        }
                    };

                    norm_function_list.push_back(norm_func);
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
                std::vector<boost::packaged_task<void>> tasks;
                tasks.reserve(threads);

                for (int i = 0; i < threads; ++i) {
                    tasks.emplace_back(boost::bind(mv_function_list[i], x, y));
                }

                std::vector<boost::unique_future<boost::packaged_task<void>::result_type>> futures;
                for (auto& t : tasks) {
                    futures.push_back(t.get_future());
                    boost::asio::post(pool, std::move(t));
                }

                for (auto& fut : boost::when_all(futures.begin(), futures.end()).get()) {
                    fut.get();
                }
            }

            /**
             * @brief Power method: Executes matrix vector product repeatedly to get the dominant eigenvector.
             * 
             * Loop is parallelized using parallel_for from TBB
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
                    
                    std::vector<boost::packaged_task<void>> tasks;
                    tasks.reserve(threads);

                    for (int i = 0; i < threads; ++i) {
                        tasks.emplace_back(boost::bind(norm_function_list[i], x, y, norm));
                    }

                    std::vector<boost::unique_future<boost::packaged_task<void>::result_type>> futures;
                    for (auto& t : tasks) {
                        futures.push_back(t.get_future());
                        boost::asio::post(pool, std::move(t));
                    }

                    for (auto& fut : boost::when_all(futures.begin(), futures.end()).get()) {
                        fut.get();
                    }
                }
            }
    };
} // namespace pwm

#endif // PWM_CRSTHREADPOOL_HPP