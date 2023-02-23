/**
 * @file TripletToCRS.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility file to transform Triplet format into CRS format
 */

#ifndef PWM_TRIPLETTOCRS_HPP
#define PWM_TRIPLETTOCRS_HPP

#include <stdlib.h>

#include "VectorUtill.hpp"

#include "oneapi/tbb.h"

namespace pwm {
    template<typename T, typename int_type>
    void swapArrayElems(int_type** coords, T* data, int am_coords, int_type index_1, int_type index_2) {
        for (int i = 0; i < am_coords; ++i) {
            int_type temp = coords[i][index_1];
            coords[i][index_1] = coords[i][index_2];
            coords[i][index_2] = temp;
        }

        T data_temp = data[index_1];
        data[index_1] = data[index_2];
        data[index_2] = data_temp;
    }

    template<typename T, typename int_type>
    int_type partitionArrays(int_type** coords, T* data, int am_coords, int_type low, int_type high) {
        // Select pivot (rightmost element)
        int_type pivot = coords[0][high];

        // Points to biggest element
        int_type i = (low - 1);
        for (int j = low; j < high; ++j) {
            if (coords[0][j] <= pivot) {
                // If element is smaller than pivot swap it with i+1
                i++;
                swapArrayElems(coords, data, am_coords, i, j);
            }
        }

        // Swap pivot with the greatest element at i+1
        swapArrayElems(coords, data, am_coords, i+1, high);

        // return the partitioning point
        return i+1;
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
    template<typename T, typename int_type>
    void sortCoordsForCRS(int_type** coords, T* data, int am_coords, int_type low, int_type high) {
        if (low < high) {
            swapArrayElems(coords, data, am_coords, (rand() % (high-low)) + low, high); // Random permutation of biggest element
            int_type middle = partitionArrays(coords, data, am_coords, low, high);

            sortCoordsForCRS(coords, data, am_coords, low, middle - 1);
            sortCoordsForCRS(coords, data, am_coords, middle + 1, high);
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
    template<typename T, typename int_type>
    void TripletToCRS(int_type* row_coord, int_type* col_coord, T* data, int_type* row_start, int_type* col_ind, T* CRS_data, int_type nnz, int_type nor) {
        // Sort triplets on row value
        int_type** coords = new int_type*[2];
        coords[0] = row_coord;
        coords[1] = col_coord;
        sortCoordsForCRS(coords, data, 2, 0, nnz-1);

        // Fill CRS datastructures
        row_start[0] = 0;
        int_type row_index = 0;
        for (int i = 0; i < nnz; ++i) {
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
            sortCoordsForCRS(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
        }
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
        sortCoordsForCRS(coords, data, 2, 0, nnz-1);

        // Fill CRS data with omp to avoid first touch
        #pragma omp parallel for shared(col_ind, col_coord, CRS_data, data, row_coord, row_start) schedule(dynamic, 8)
        for (int i = 0; i < nnz; ++i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];
        }

        // Fill CRS row_start
        row_start[0] = 0;
        int_type row_index = 0;
        for (int i = 0; i < nnz; ++i) {
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
        #pragma omp parallel for shared(col_ind, CRS_data, row_start) schedule(dynamic)
        for (int row = 0; row <= row_coord[nnz-1]; ++row) {
            sortCoordsForCRS(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
        }
    }

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
        sortCoordsForCRS(coords, data, 2, 0, nnz-1);

        // Fill CRS data with omp to avoid first touch
        tbb::parallel_for(0, nnz, [=](int_type i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];
        });

        // Fill CRS row_start
        row_start[0] = 0;
        int_type row_index = 0;
        for (int i = 0; i < nnz; ++i) {
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
        tbb::parallel_for(0, row_coord[nnz-1]+1, [=](int_type row) {
            sortCoordsForCRS(coords, CRS_data, 1, row_start[row], row_start[row+1]-1);
        });
    }

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
        sortCoordsForCRS(coords, data, 2, 0, nnz-1);

        // Fill CRS datastructures
        int_type am_rows = std::round(nor/partitions);
        int_type last_row = 0;
        int_type nnz_index = 0;
        int_type part_index = 0;
        int_type row_index;
        for (int i = 0; i < partitions; ++i) {
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
            for (int row = 0; row < thread_rows[i]; ++row) {
                sortCoordsForCRS(coords, CRS_data[i], 1, row_start[i][row], row_start[i][row+1]-1);
            }
        }        
    }
} // namespace pwm


#endif // PWM_TRIPLETTOCRS_HPP