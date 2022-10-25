/**
 * @file Triplet.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Triplet format of a sparse matrix
 * @version 0.1
 * @date 2022-10-18
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

#include "Utill/VectorUtill.hpp"

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
            void loadFromMM(std::string filename, bool has_data, bool random_fill = false) {
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
                            nnz = boost::lexical_cast<int_type>(word);
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
                    }
                }
            }

            /**
             * @brief Loads Triplet matrix from Kronecker graph generator binary output.
             * 
             * @param filename Filename of input file
             * @param random_vals If this is true generate random matrix values. If this is false every value is 1.
             */
            void loadFromKronecker(std::string filename, int_type mat_size, bool random_vals) {
                row_size = mat_size;
                col_size = mat_size;

                struct stat results;
                if (stat(filename.c_str(), &results) == 0) {
                    nnz = results.st_size / (2*sizeof(uint32_t)); // Binary file is stored in unsigned long format
                } else {
                    std::cout << "An error occurred while reading the Kronecker input file" << std::endl;
                }

                row_coord = new int_type[nnz];
                col_coord = new int_type[nnz];
                data = new T[nnz];

                uint32_t input_nb;
                char input_buf[sizeof(uint32_t)];
                std::ifstream input_file(filename, std::ios::in | std::ios::binary);
                for (int i = 0; i < nnz; ++i) {
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
                }
            }
    };
} // namespace pwm


#endif // PWM_TRIPLET_HPP