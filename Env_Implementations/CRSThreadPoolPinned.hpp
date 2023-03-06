/**
 * @file CRSThreadPoolPinned.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Compressed Row Storage matrix class using Boost thread pool with threads pinned to a CPU
 * 
 * Includes method to generate CRS matrix obtained from discrete 2D poisson equation
 */

#ifndef PWM_CRSTHREADPOOLPINNED_HPP
#define PWM_CRSTHREADPOOLPINNED_HPP

#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>

#include "../Matrix/SparseMatrix.hpp"
#include "../Util/VectorUtill.hpp"
#include "../Util/Poisson.hpp"

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

namespace pwm {
    template<typename T, typename int_type>
    class CRSThreadPoolPinned: public pwm::SparseMatrix<T, int_type> {
        protected:
            // Array of row start arrays for the CRS format. 1 for each thread.
            int_type** row_start;
            
            // Array of column index array for the CRS format. 1 for each thread
            int_type** col_ind;

            // Array of data array which stores the actual nonzeros. 1 for each thread.
            T** data_arr;

            // Amount of threads
            int threads;

            // Amount of partitions
            int partitions;

            // Amount of rows per partition
            int_type* partition_rows;

            // First row of each partition
            int_type* first_rows;

            // Thread pool
            boost::asio::thread_pool pool;

            // mv Function list
            std::vector<std::function<void(const T*, T*)>> mv_function_list;

            // Normalize Function list
            std::vector<std::function<void(T*, T)>> norm_function_list;

        private:
            void generateFunctions() {
                mv_function_list = std::vector<std::function<void(const T*, T*)>>();
                norm_function_list = std::vector<std::function<void(T*, T)>>();

                int cpu_count = std::thread::hardware_concurrency();
                int max_threads = std::min(threads, cpu_count);
                for (int i = 0; i < partitions; ++i) {
                    // Create mv lambda function for this thread
                    std::function<void(const T*, T*)> mv_func = [=](const T* x, T* y) -> void {
                        // Put the current thread on the right cpu
                        cpu_set_t *mask;
                        mask = CPU_ALLOC(1);
                        auto mask_size = CPU_ALLOC_SIZE(1);
                        CPU_ZERO_S(mask_size, mask);
                        CPU_SET_S(i % max_threads, mask_size, mask);
                        if (sched_setaffinity(0, mask_size, mask)) {
                            std::cout << "Error in setAffinity" << std::endl;
                        }

                        int_type j;
                        for (int_type l = 0; l < partition_rows[i]; ++l) {
                            T sum = 0;
                            for (int_type k = row_start[i][l]; k < row_start[i][l+1]; ++k) {
                                j = col_ind[i][k];
                                sum += data_arr[i][k]*x[j];
                            }
                            y[l+first_rows[i]] = sum;
                        }
                    };

                    mv_function_list.push_back(mv_func);


                    // Create normalize function for this thread
                    std::function<void(T*, T)> norm_func = [=](T* x, T norm) -> void {
                        // Put the current thread on the right cpu
                        cpu_set_t *mask;
                        mask = CPU_ALLOC(1);
                        auto mask_size = CPU_ALLOC_SIZE(1);
                        CPU_ZERO_S(mask_size, mask);
                        CPU_SET_S(i % max_threads, mask_size, mask);
                        if (sched_setaffinity(0, mask_size, mask)) {
                            std::cout << "Error in setAffinity" << std::endl;
                        }

                        for (int_type l = 0; l < partition_rows[i]; ++l) {
                            x[l+first_rows[i]] /= norm;
                        }
                    };

                    norm_function_list.push_back(norm_func);
                }
            }

        public:
            // Base constructor
            CRSThreadPoolPinned() {}

            // Base constructor
            CRSThreadPoolPinned(int threads): threads(threads), pool(threads) {}

            // Deconstructor
            ~CRSThreadPoolPinned() {
                for (int i = 0; i < partitions; ++i) {
                    delete [] row_start[i];
                    delete [] col_ind[i];
                    delete [] data_arr[i];

                    row_start[i] = NULL;
                    col_ind[i] = NULL;
                    data_arr[i] = NULL;
                }

                delete [] row_start;
                delete [] col_ind;
                delete [] data_arr;
                delete [] partition_rows;
                delete [] first_rows;

                row_start = NULL;
                col_ind = NULL;
                data_arr = NULL;
                partition_rows = NULL;
                first_rows = NULL;
            }

            /**
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * The matrix is partitioned for each thread 
             * This is done by splitting the rows equally, this is only optimal because every row has approximately the same elements.
             * 
             * Then each Matrix part gets its own mv_function and norm_function 
             * This is used to calculate the matrix vector product & normalization of the given partition.
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoissonMatrix(const int_type m, const int_type n, const int partitions_am) {
                this->noc = m*n;
                this->nor = m*n;

                this->nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                partitions = partitions_am;

                row_start = new int_type*[partitions];
                col_ind = new int_type*[partitions];
                data_arr = new T*[partitions];

                partition_rows = new int_type[partitions];
                first_rows = new int_type[partitions];

                // Generate data for each thread
                int_type am_rows = std::round(m*n/partitions);
                int_type last_row = 0;
                for (int i = 0; i < partitions_am; ++i) {
                    first_rows[i] = last_row;

                    if (i == partitions - 1) last_row = m*n;
                    else last_row = first_rows[i] + am_rows;
                    partition_rows[i] = last_row - first_rows[i];

                    // Generate datastructures for this thread CRS (data_arr & col_ind are sometimes too large...)
                    data_arr[i] = new T[5*partition_rows[i]];
                    row_start[i] = new int_type[partition_rows[i]+1];
                    col_ind[i] = new int_type[5*partition_rows[i]];
                    
                    // Fill CRS matrix for given thread
                    pwm::fillPoisson(data_arr[i], row_start[i], col_ind [i], m, n, first_rows[i], last_row);
                }
                
                // Generate functions for each partition
                generateFunctions();
            }

            /**
             * @brief Input the CRS matrix from a Triplet format
             * 
             * @param input Triplet format matrix used to convert to CRS
             */
            void loadFromTriplets(pwm::Triplet<T, int_type>* input, const int partitions_am) {
                this->noc = input->col_size;
                this->nor = input->row_size;
                this->nnz = input->nnz;

                partitions = partitions_am;

                row_start = new int_type*[partitions];
                col_ind = new int_type*[partitions];
                data_arr = new T*[partitions];
                
                partition_rows = new int_type[partitions];
                first_rows = new int_type[partitions];

                // Generate data for each thread
                pwm::TripletToMultipleCRS(input->row_coord, input->col_coord, input->data, row_start, col_ind, data_arr, 
                                          partitions, partition_rows, first_rows, this->nnz, this->nor);

                // Generate function nodes per thread
                generateFunctions();
            }

            /**
             * @brief Matrix vector product Ax = y
             * 
             * The loop is parallelized using functions posted to the threadpool
             * 
             * @param x Input vector
             * @param y Output vector
             */
            void mv(const T* x, T* y) {
                std::vector<boost::packaged_task<void>> tasks;
                tasks.reserve(partitions);

                for (int i = 0; i < partitions; ++i) {
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
             * Loop is parallelized using functions posted to the threadpool
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
                        
                        std::vector<boost::packaged_task<void>> tasks;
                        tasks.reserve(partitions);

                        for (int i = 0; i < partitions; ++i) {
                            tasks.emplace_back(boost::bind(norm_function_list[i], y, norm));
                        }

                        std::vector<boost::unique_future<boost::packaged_task<void>::result_type>> futures;
                        for (auto& t : tasks) {
                            futures.push_back(t.get_future());
                            boost::asio::post(pool, std::move(t));
                        }

                        for (auto& fut : boost::when_all(futures.begin(), futures.end()).get()) {
                            fut.get();
                        }
                    } else {
                        this->mv(y, x);
                        T norm = pwm::norm2(x, this->nor);
                        
                        std::vector<boost::packaged_task<void>> tasks;
                        tasks.reserve(partitions);

                        for (int i = 0; i < partitions; ++i) {
                            tasks.emplace_back(boost::bind(norm_function_list[i], x, norm));
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
            }
    };
} // namespace pwm

#endif // PWM_CRSTHREADPOOLPINNED_HPP