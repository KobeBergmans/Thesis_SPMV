/**
 * @file Triplet.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Triplet format of a sparse matrix
 * 
 * Includes a function to import from Matrix Market Format
 * TODO: Includes a function to import from the Kronecker graph generator (https://github.com/RapidsAtHKUST/Graph500KroneckerGraphGenerator)
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

                    // Correction for diagonal entries for symmetric matrices
                    if (symmetric) {
                        nnz = index;
                    }
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
                if (stat(filename.c_str(), &results) == 0) {
                    nnz = results.st_size / (2*sizeof(uint32_t)); // Binary file is stored in unsigned long format
                } else {
                    std::cout << "An error occurred while reading the Kronecker input file" << std::endl;
                }

                if (symmetric) {
                    nnz = nnz*2;
                }

                row_coord = new int_type[nnz];
                col_coord = new int_type[nnz];
                data = new T[nnz];

                uint32_t input_nb;
                char input_buf[sizeof(uint32_t)];
                std::ifstream input_file(filename, std::ios::in | std::ios::binary);
                int_type i = 0;
                while (i < nnz) {
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
                }

                // Correction for diagonal entries for symmetric matrices
                if (symmetric) {
                    nnz = i;
                }
            }

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
                for (int_type i = 0; i < row_size; ++i) {
                    // sub diagonal
                    if (i % m != 0) {
                        row_coord[index] = i;
                        col_coord[index] = i+1;
                        data[index] = -1.;
                        index++;
                    }

                    // super diagonal
                    if (i % m != m-1) {
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