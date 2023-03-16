/**
 * @file TripletToCRS.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility file to transform Triplet format into CRS format
 */

#ifndef PWM_TRIPLETTOCRS_HPP
#define PWM_TRIPLETTOCRS_HPP

#include <stdlib.h>

#include "VectorUtill.hpp"
#include "Constants.hpp"

#include <omp.h>

#ifndef NTBB
#include "oneapi/tbb.h"
#endif

namespace pwm {
    template<typename T, typename index_type, typename int_type>
    void swapArrayElems(index_type** coords, T* data, int am_coords, int_type index_1, int_type index_2) {
        for (int i = 0; i < am_coords; ++i) {
            index_type temp = coords[i][index_1];
            coords[i][index_1] = coords[i][index_2];
            coords[i][index_2] = temp;
        }

        T data_temp = data[index_1];
        data[index_1] = data[index_2];
        data[index_2] = data_temp;
    }

    template<typename T, typename index_type, typename int_type>
    void swapArrayElems(index_type** coords, std::vector<T>& data, int am_coords, int_type index_1, int_type index_2) {
        for (int i = 0; i < am_coords; ++i) {
            index_type temp = coords[i][index_1];
            coords[i][index_1] = coords[i][index_2];
            coords[i][index_2] = temp;
        }

        T data_temp = data[index_1];
        data[index_1] = data[index_2];
        data[index_2] = data_temp;
    }

    template<typename T, typename index_type, typename int_type>
    void swapArrayElems(index_type* coords, T* data, int_type index_1, int_type index_2) {
        index_type temp = coords[index_1];
        coords[index_1] = coords[index_2];
        coords[index_2] = temp;

        T data_temp = data[index_1];
        data[index_1] = data[index_2];
        data[index_2] = data_temp;
    }

    template<typename T, typename index_type, typename int_type>
    void swapArrayElems(index_type* coords, std::vector<T>& data, int_type index_1, int_type index_2) {
        index_type temp = coords[index_1];
        coords[index_1] = coords[index_2];
        coords[index_2] = temp;

        T data_temp = data[index_1];
        data[index_1] = data[index_2];
        data[index_2] = data_temp;
    }

    template<typename T, typename index_type, typename int_type>
    int_type partitionArrays(index_type** coords, T* data, int am_coords, int_type low, int_type high) {
        // Select pivot (rightmost element)
        int_type pivot = coords[0][high];

        // Points to biggest element
        int_type i = low;
        for (int j = low; j < high; ++j) {
            if (coords[0][j] <= pivot) {
                // If element is smaller than pivot swap it with i+1
                swapArrayElems<T, index_type, int_type>(coords, data, am_coords, i, j);
                i++;
            }
        }

        // Swap pivot with the greatest element at i+1
        swapArrayElems<T, index_type, int_type>(coords, data, am_coords, i, high);

        // return the partitioning point
        return i;
    }

    /**
     * @brief Quicksort implementation to sort the triplets by coordinates
     * 
     * Sorts all the elements using quicksort by the first array present in coords
     * 
     * https://www.programiz.com/dsa/quick-sort
     * 
     * @param coords Coordinate array of arrays where the first array represents the coordinate to sort on 
     * @param data Data array for Triplet format
     * @param am_coords Amount of arrays in coords
     * @param low Start index of quicksort
     * @param high End index of quicksort
     */
    template<typename T, typename index_type, typename int_type>
    void sortOnCoord(index_type** coords, T* data, int am_coords, int_type low, int_type high) {
        if (low < high) {
            swapArrayElems(coords, data, am_coords, (((int_type)rand()) % (high-low)) + low, high); // Random permutation of rightmost element
            int_type middle = partitionArrays(coords, data, am_coords, low, high);

            if (middle > 0) {
                sortOnCoord(coords, data, am_coords, low, middle - 1);
            }
            sortOnCoord(coords, data, am_coords, middle + 1, high);
        }
    }

    /**
     * @brief Transforms Triplet format to CRS format
     * 
     * The output arrays are assumed to have the right size.
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param row_start Output row_start array of CRS format
     * @param col_ind Output col_ind array of CRS format
     * @param CRS_data Output data array of CRS format
     * @param nnz Number of nonzeros in matrix
     */
    template<typename T, typename index_type, typename int_type>
    void TripletToCRS(index_type* row_coord, index_type* col_coord, T* data, index_type* row_start, index_type* col_ind, T* CRS_data, int_type nnz, int_type nor) {
        // Sort triplets on row value
        index_type** coords = new index_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortOnCoord<T, index_type, int_type>(coords, data, 2, 0, nnz-1);

        // Fill CRS datastructures
        row_start[0] = 0;
        int_type row_index = 0;
        for (int_type i = 0; i < nnz; ++i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];

            while (row_coord[i] != row_index) {
                row_index++;
                row_start[row_index] = i;
            }
        }

        // Fill last elements of row_start with nnz
        while (row_index < nor) {
            row_index++;
            row_start[row_index] = nnz;
        }

        // Sort columns of CRS data
        coords[0] = col_ind;
        for (int row = 0; row <= row_coord[nnz-1]; ++row) {
            if (row_start[row+1] != 0) { // Needed for when the first row is empty and unsigned integers are used
                sortOnCoord<T, index_type, int_type>(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
            }
        }

        delete [] coords;
    }

    /**
     * @brief Transforms Triplet format to CRS format
     * 
     * The output arrays are assumed to have the right size.
     * 
     * Implementation with OMP to avoid first touch problem
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param row_start Output row_start array of CRS format
     * @param col_ind Output col_ind array of CRS format
     * @param CRS_data Output data array of CRS format
     * @param nnz Number of nonzeros in matrix
     */
    template<typename T, typename int_type>
    void TripletToCRSOMP(int_type* row_coord, int_type* col_coord, T* data, int_type* row_start, int_type* col_ind, T* CRS_data, int_type nnz, int_type nor) {
        // Sort triplets on row value
        int_type** coords = new int_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortOnCoord<T, int_type, int_type>(coords, data, 2, 0, nnz-1);

        // Fill CRS data with omp to avoid first touch
        #pragma omp parallel for shared(col_ind, col_coord, CRS_data, data, row_coord, row_start) schedule(dynamic, OMP_DYNAMIC_CHUNK_SIZE)
        for (int i = 0; i < nnz; ++i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];
        }

        // Fill CRS row_start
        row_start[0] = 0;
        int_type row_index = 0;
        for (int_type i = 0; i < nnz; ++i) {
            while (row_coord[i] != row_index) {
                row_index++;
                row_start[row_index] = i;
            }
        }
        
        // Fill last elements of row_start with nnz
        while (row_index < nor) {
            row_index++;
            row_start[row_index] = nnz;
        }

        // Sort columns of CRS data
        coords[0] = col_ind;
        #pragma omp parallel for shared(col_ind, CRS_data, row_start) schedule(dynamic, OMP_DYNAMIC_CHUNK_SIZE)
        for (int_type row = 0; row <= row_coord[nnz-1]; ++row) {
            if (row_start[row+1] != 0) { // Needed for when the first row is empty and unsigned integers are used
                sortOnCoord<T, int_type, int_type>(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
            }
        }

        delete [] coords;
    }

#ifndef NTBB
    /**
     * @brief Transforms Triplet format to CRS format
     * 
     * The output arrays are assumed to have the right size.
     * 
     * Implementation with TBB to avoid first touch problem
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param row_start Output row_start array of CRS format
     * @param col_ind Output col_ind array of CRS format
     * @param CRS_data Output data array of CRS format
     * @param nnz Number of nonzeros in matrix
     */
    template<typename T, typename int_type>
    void TripletToCRSTBB(int_type* row_coord, int_type* col_coord, T* data, int_type* row_start, int_type* col_ind, T* CRS_data, int_type nnz, int_type nor) {
        // Sort triplets on row value
        int_type** coords = new int_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortOnCoord<T, int_type, int_type>(coords, data, 2, 0, nnz-1);

        // Fill CRS data with omp to avoid first touch
        tbb::parallel_for((int_type)0, nnz, [=](int_type i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];
        });

        // Fill CRS row_start
        row_start[0] = 0;
        int_type row_index = 0;
        for (int_type i = 0; i < nnz; ++i) {
            while (row_coord[i] != row_index) {
                row_index++;
                row_start[row_index] = i;
            }
        }
        
        // Fill last elements of row_start with nnz
        while (row_index < nor) {
            row_index++;
            row_start[row_index] = nnz;
        }

        // Sort columns of CRS data
        coords[0] = col_ind;
        tbb::parallel_for((int_type)0, row_coord[nnz-1]+1, [=](int_type row) {
            if (row_start[row+1] != 0) { // Needed for when the first row is empty and unsigned integers are used
                sortOnCoord<T, int_type, int_type>(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
            }
        });

        delete [] coords;
    }
#endif // NTBB

    /**
     * @brief Transforms Triplet format to CRS format
     * 
     * The output arrays are assumed to have the right size.
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param row_start Output row_start arrays of CRS format
     * @param col_ind Output col_ind arrays of CRS format
     * @param CRS_data Output data arrays of CRS format
     * @param partitions Amount of partitions for the CRS matrix (amount of arrays in row_start, col_ind, and CRS_data)
     * @param nnz Number of nonzeros in matrix
     */
    template<typename T, typename int_type>
    void TripletToMultipleCRS(int_type* row_coord, int_type* col_coord, T* data, int_type** row_start, int_type** col_ind, T** CRS_data, 
                              int partitions, int_type* thread_rows, int_type* first_rows, int_type nnz, int_type nor) {

        // Sort triplets on row value
        int_type** coords = new int_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortOnCoord<T, int_type, int_type>(coords, data, 2, 0, nnz-1);

        // Fill CRS datastructures
        int_type am_rows = std::round(nor/partitions);
        int_type last_row = 0;
        int_type nnz_index = 0;
        int_type part_index = 0;
        int_type row_index;
        for (int_type i = 0; i < partitions; ++i) {
            // Calculate first and last row (last row is exclusive)
            first_rows[i] = last_row;
            if (i == partitions - 1) last_row = nor;
            else last_row = first_rows[i] + am_rows;
            thread_rows[i] = last_row - first_rows[i];

            // Calculate nnz for the amount of rows
            int_type j = nnz_index;
            while (true) {
                if (j == nnz || row_coord[j] >= last_row) {
                    break;
                }

                j++;
            }

            // Create datastructures
            int_type nnz_this_part = j - nnz_index;
            row_start[i] = new int_type[thread_rows[i]+1];
            col_ind[i] = new int_type[nnz_this_part];
            CRS_data[i] = new T[nnz_this_part];

            // Fill datastructures
            row_start[i][0] = 0;
            row_index = 0;
            part_index = 0;
            while (true) {
                col_ind[i][part_index] = col_coord[nnz_index];
                CRS_data[i][part_index] = data[nnz_index];

                while (row_coord[nnz_index] != row_index+first_rows[i]) {
                    row_index++;
                    row_start[i][row_index] = part_index;
                }

                part_index++;
                nnz_index++;

                if (nnz_index >= nnz || row_coord[nnz_index] >= last_row) {
                    break;
                }
            }

            // Fill last elements of row_start with part_index
            while (row_index < thread_rows[i]) {
                row_index++;
                row_start[i][row_index] = part_index;
            }
            
            // Sort columns of CRS data
            coords[0] = col_ind[i];
            for (int_type row = 0; row < thread_rows[i]; ++row) {
                if (row_start[i][row+1] != 0) { // Needed for when the first row is empty and unsigned integers are used
                    sortOnCoord<T, int_type, int_type>(coords, CRS_data[i], 1, row_start[i][row], row_start[i][row+1]-1);
                }
            }
        }

        delete [] coords;        
    }

    /**
     * @brief Transforms Triplet format to ICRS format
     * 
     * The output arrays are assumed to have the right maximum size.
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param row_jump Output row_jump array of ICRS format
     * @param col_jump Output col_jump array of ICRS format
     * @param ICRS_data Output data array of ICRS format
     * @param nnz Number of nonzeros in matrix
     * @param size Size of the matrix
     * @return int_type Returns the index in the row_jump array as this is not always equal to nor+1
     */
    template<typename T, typename index_type, typename int_type>
    int_type TripletToICRS(index_type* row_coord, index_type* col_coord, T* data, index_type* row_jump, index_type* col_jump, T* ICRS_data, int_type nnz, int_type size) {
        // Sort triplets on row value
        index_type** coords = new index_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortOnCoord<T, index_type, int_type>(coords, data, 2, 0, nnz-1);

        // Sort column values in each row
        coords[0] = col_coord;
        int_type row_start = 0;
        int_type row_val = row_coord[0];
        for (int_type i = 1; i < nnz; ++i) {
            // If the row value jumps, we sort the row
            if (row_coord[i] != row_val) {
                sortOnCoord<T, index_type, int_type>(coords, data, 1, row_start, i-1);

                row_start = i;
                row_val = row_coord[i];
            }
        }

        // Sort last row
        sortOnCoord<T, index_type, int_type>(coords, data, 1, row_start, nnz-1);

        // Fill initial values of ICRS structure
        row_jump[0] = row_coord[0];
        col_jump[0] = col_coord[0];
        ICRS_data[0] = data[0];

        // Loop over values and fill ICRS structure
        int_type row_jump_index = 1;
        index_type cur_row = row_coord[0];
        for (int_type i = 1; i < nnz; ++i) {
            if (row_coord[i] != cur_row) {
                // We have a new row so the col_jump must overflow
                col_jump[i] = (col_coord[i] + size) - col_coord[i-1];
                row_jump[row_jump_index++] = row_coord[i] - row_coord[i-1];
                cur_row = row_coord[i];
            } else {
                col_jump[i] = col_coord[i] - col_coord[i-1];
            }

            ICRS_data[i] = data[i];
        }

        delete [] coords;

        return row_jump_index;
    }
} // namespace pwm


#endif // PWM_TRIPLETTOCRS_HPP