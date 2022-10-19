/**
 * @file TripletToCRS.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Utility file to transform Triplet format into CRS format
 * @version 0.1
 * @date 2022-10-18
 */

#ifndef PWM_TRIPLETTOCRS_HPP
#define PWM_TRIPLETTOCRS_HPP

#include "VectorUtill.hpp"

namespace pwm {
    template<typename T, typename int_type>
    void swapArrayElems(int_type* row_coord, int_type* col_coord, T* data, int_type index_1, int_type index_2) {
        int_type row_temp = row_coord[index_1];
        int_type col_temp = col_coord[index_1];
        T data_temp = data[index_1];
        
        row_coord[index_1] = row_coord[index_2];
        col_coord[index_1] = col_coord[index_2];
        data[index_1] = data[index_2];

        row_coord[index_2] = row_temp;
        col_coord[index_2] = col_temp;
        data[index_2] = data_temp;
    }

    template<typename T, typename int_type>
    int_type partitionArrays(int_type* row_coord, int_type* col_coord, T* data, int_type low, int_type high) {
        // Select pivot (rightmost element)
        int_type pivot = row_coord[high];

        // Points to biggest element
        int_type i = (low - 1);
        for (int j = low; j < high; j++) {
            if (row_coord[j] <= pivot) {
                // If element is smaller than pivot swap it with i+1
                i++;
                swapArrayElems(row_coord, col_coord, data, i, j);
            }
        }

        // Swap pivot with the greatest element at i+1
        swapArrayElems(row_coord, col_coord, data, i+1, high);

        // return the partitioning point
        return i+1;
    }

    /**
     * @brief Quicksort implementation to sort the triplets by rows
     * 
     * https://www.programiz.com/dsa/quick-sort
     * 
     * @param row_coord Array of row coordinates of Triplet format
     * @param col_coord Array of column coordinates of Triplet format
     * @param data Data array for Triplet format
     * @param low Start index of quicksort
     * @param high End index of quicksort
     */
    template<typename T, typename int_type>
    void sortTripletsForCRS(int_type* row_coord, int_type* col_coord, T* data, int_type low, int_type high) {
        if (low < high) {
            int_type middle = partitionArrays(row_coord, col_coord, data, low, high);

            sortTripletsForCRS(row_coord, col_coord, data, low, middle - 1);
            sortTripletsForCRS(row_coord, col_coord, data, middle + 1, high);
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
    void TripletToCRS(int_type* row_coord, int_type* col_coord, T* data, int_type* row_start, int_type* col_ind, T* CRS_data, int_type nnz) {
        // Sort triplets on row value
        sortTripletsForCRS(row_coord, col_coord, data, 0, nnz-1);

        // Fill CRS datastructures
        row_start[0] = 0;
        int_type row_index = 0;
        for (int i = 0; i < nnz; ++i) {
            col_ind[i] = col_coord[i];
            CRS_data[i] = data[i];

            if (row_coord[i] != row_index) {
                row_index++;
                row_start[row_index] = i;
            }
        }

        row_start[row_index + 1] = nnz;

        // TODO: Sort columns of CRS data

    }
} // namespace pwm


#endif // PWM_TRIPLETTOCRS_HPP