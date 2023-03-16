/**
 * @file Triplet.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Triplet format of a sparse matrix
 * 
 * Includes a function to import from Matrix Market Format
 * Includes a function to import from the Kronecker graph generator (https://github.com/RapidsAtHKUST/Graph500KroneckerGraphGenerator)
 */

#ifndef PWM_TRIPLET_HPP
#define PWM_TRIPLET_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "../Util/VectorUtill.hpp"

#include <omp.h>

namespace pwm {
    template<typename T, typename int_type>
    class Triplet {
        public:
            // Row Coordinate array
            int_type* row_coord;

            // Column coordinate array
            int_type* col_coord;

            // Data array
            T* data;

            // x size
            int_type row_size;

            // y size
            int_type col_size;

            // Amount of nonzeros
            int_type nnz;

            // Random number generator for random vals of kronecker graph (set seed is 747846)
            boost::random::mt19937 gen;

            // Uniform real distribution
            boost::random::uniform_real_distribution<T> dist;

            // Base constructor
            Triplet(): gen(747846), dist(-100., 100.) {}

            // Deconstructor
            ~Triplet() {
                delete [] row_coord;
                delete [] col_coord;
                delete [] data;

                row_coord = NULL;
                col_coord = NULL;
                data = NULL;
            }

            /**
             * @brief Load from Matrix Market format
             * 
             * @param filename Filename of file to load
             * @param has_data Specifies if this is a weighted graph (x, y and z coordinates are present)
             * @param random_fill Specifies if the data should be randomly filled in. Only used if has_data is false.
             */
            void loadFromMM(std::string filename, bool has_data, bool symmetric, bool random_fill = false) {
                std::ifstream input_file(filename);

                if (input_file.is_open()) {
                    std::string temp_line;
                    std::string word;

                    // Get comment lines
                    while (input_file.good()) {
                        std::getline(input_file, temp_line);
                        
                        if (temp_line[0] != '%') {
                            std::stringstream line(temp_line);
                            line >> word;

                            // Get matrix size and amount of entries
                            row_size = boost::lexical_cast<int_type>(word);

                            line >> word;
                            col_size = boost::lexical_cast<int_type>(word);

                            line >> word; // Get amount of entries
                            if (!symmetric) {
                                nnz = boost::lexical_cast<int_type>(word);
                            } else {
                                nnz = 2*boost::lexical_cast<int_type>(word);
                            }
                            
                            row_coord = new int_type[nnz];
                            col_coord = new int_type[nnz];
                            data = new T[nnz];

                            break;
                        }
                    }

                    // Get data (Subtract 1 from coordinates to get index 0 for start)
                    int_type index = 0;
                    while (input_file.good()) {
                        std::getline(input_file, temp_line);
                        if (temp_line.size() == 0) break;

                        std::stringstream line(temp_line);

                        // x coord
                        line >> word;
                        row_coord[index] = boost::lexical_cast<int_type>(word) - 1;

                        // y coord
                        line >> word;
                        col_coord[index] = boost::lexical_cast<int_type>(word) - 1;

                        // Data
                        if (has_data) {
                            line >> word;
                            data[index] = boost::lexical_cast<T>(word);

                            if (data[index] == (T)0) { // Data can be zero thus then we don't store the value
                                continue;
                            }
                        } else if (random_fill) {
                            data[index] = dist(gen);
                        } else {
                            data[index] = 1.;
                        }
                        
                        index++;

                        if (symmetric && row_coord[index-1] != col_coord[index-1]) {
                            row_coord[index] = col_coord[index-1];
                            col_coord[index] = row_coord[index-1];
                            data[index] = data[index-1];
                            index++;
                        }
                    }

                    // Correction for diagonal entries for symmetric matrices and when there are explicit zero's
                    nnz = index;
                }
            }

            /**
             * @brief Loads Triplet matrix from Kronecker graph generator binary output.
             * 
             * @param filename Filename of input file
             * @param random_vals If this is true generate random matrix values. If this is false every value is 1.
             */
            void loadFromBin(std::string filename, int_type mat_size, bool symmetric, bool random_vals) {
                row_size = mat_size;
                col_size = mat_size;

                struct stat results;
                int_type binary_entries;
                if (stat(filename.c_str(), &results) == 0) {
                    binary_entries = results.st_size / (2*sizeof(uint32_t)); // Binary file is stored in unsigned long format
                    nnz = binary_entries;
                } else {
                    std::cout << "An error occurred while reading the Kronecker input file" << std::endl;
                }

                if (symmetric) {
                    nnz = nnz*2;
                }

                row_coord = new int_type[nnz];
                col_coord = new int_type[nnz];
                data = new T[nnz];

                int threads = omp_get_max_threads();
                int_type* nnz_end = new int_type[threads];

                #pragma omp parallel for schedule(static) num_threads(threads)
                for (int pid = 0; pid < threads; ++pid) {
                    uint32_t input_nb;
                    char input_buf[sizeof(uint32_t)];
                    std::ifstream input_file(filename, std::ios::in | std::ios::binary);

                    // Calculate starting position of stream and nnz
                    int_type stream_start = (binary_entries / threads)*pid;
                    int_type stream_end;
                    if (pid != threads-1) stream_end = (binary_entries / threads)*(pid+1);
                    else stream_end = binary_entries;

                    int_type nnz_start;
                    if (!symmetric) {
                        nnz_start = stream_start;
                    } else {
                        nnz_start = stream_start*2;
                    }

                    input_file.seekg(sizeof(uint32_t)*stream_start*2, std::ios::beg);
                    int_type i = nnz_start;
                    while (stream_start < stream_end) {
                        input_file.read(input_buf, sizeof(uint32_t));
                        std::memcpy(&input_nb, input_buf, sizeof(uint32_t));
                        row_coord[i] = input_nb;

                        input_file.read(input_buf, sizeof(uint32_t));
                        std::memcpy(&input_nb, input_buf, sizeof(uint32_t));
                        col_coord[i] = input_nb;

                        if (random_vals) {
                            data[i] = dist(gen);
                        } else {
                            data[i] = 1.;
                        }

                        i++;

                        if (symmetric && row_coord[i-1] != col_coord[i-1]) {
                            row_coord[i] = col_coord[i-1];
                            col_coord[i] = row_coord[i-1];
                            data[i] = data[i-1];
                            i++;
                        }

                        stream_start++;
                    }

                    nnz_end[pid] = i;
                }

                // Make sure that there are no empty spots in the array
                if (symmetric) {
                    for (int pid = 1; pid < threads; ++pid) {
                        int_type stream_start = (binary_entries / threads)*pid;
                        int_type nnz_start = stream_start*2;

                        if (nnz_end[pid-1] != nnz_start) {
                            // The array was not completely filled during reading
                            int_type pid_nnz = nnz_end[pid] - nnz_start;
                            int_type am_to_copy = std::min(nnz_start - nnz_end[pid-1], pid_nnz);

                            std::copy(row_coord+nnz_start+pid_nnz-am_to_copy, row_coord+nnz_start+pid_nnz, row_coord+nnz_end[pid-1]);
                            std::copy(col_coord+nnz_start+pid_nnz-am_to_copy, col_coord+nnz_start+pid_nnz, col_coord+nnz_end[pid-1]);
                            std::copy(data+nnz_start+pid_nnz-am_to_copy, data+nnz_start+pid_nnz, data+nnz_end[pid-1]);

                            // Update stream end
                            nnz_end[pid] -= am_to_copy;
                        }
                    }

                    nnz = nnz_end[threads-1];
                }
                
            }

            /**
             * @brief Fill this matrix as 2D discretized Poisson matrix.
             * 
             * https://en.wikipedia.org/wiki/Discrete_Poisson_equation
             * 
             * @param m The amount of discretization steps in the x direction
             * @param n The amount of discretization steps in the y direction
             */
            void generatePoisson(const int_type m, const int_type n) {
                row_size = m*n;
                col_size = m*n;
                nnz = n*(m+2*(m-1)) + 2*(n-1)*m;

                row_coord = new int_type[nnz];
                col_coord = new int_type[nnz];
                data = new T[nnz];

                int_type index = 0;

                // Add main diagonal
                for (int_type i = 0; i < row_size; ++i) {
                    row_coord[index] = i;
                    col_coord[index] = i;
                    data[index] = 4.;
                    index++;
                }

                // Add sub and super diagonal
                for (int_type i = 0; i < row_size - 1; ++i) {
                    // super diagonal
                    if (i % m != m-1) {
                        row_coord[index] = i;
                        col_coord[index] = i+1;
                        data[index] = -1.;
                        index++;
                    }

                    // sub diagonal
                    if ((i+1) % m != 0) {
                        row_coord[index] = i+1;
                        col_coord[index] = i;
                        data[index] = -1.;
                        index++;
                    }
                }

                // Add last two smaller diagonals
                for (int_type i = 0; i < row_size - m; ++i) {
                    row_coord[index] = i+m;
                    col_coord[index] = i;
                    data[index] = -1.;
                    index++;

                    row_coord[index] = i;
                    col_coord[index] = i+m;
                    data[index] = -1.;
                    index++;
                }

                assert(index == nnz);
            }
    };
} // namespace pwm


#endif // PWM_TRIPLET_HPP