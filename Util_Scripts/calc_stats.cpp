/**
 * @file calc_stats.cpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Calculates statistics for matrices
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

#include "../Matrix/Triplet.hpp"
#include "../Util/Constants.hpp"
#include "../Util/Math.hpp"
#include "../Util/DriverUtil.hpp"

void printErrorMsg() {
    std::cout << "You need to provide the correct command line arguments:" << std::endl;
    std::cout << "  1° Filename of Matrix market (.mtx extension). Filename starts with: " << std::endl;
    std::cout << "     1) Arbitrary matrix with no data present and filled in with ones" << std::endl;
    std::cout << "     2) Arbitrary matrix with no data present and random fill in" << std::endl;
    std::cout << "     3) Symmetric matrix with only lower half entries with data present" << std::endl;
    std::cout << "     4) Symmetric matrix with only lower half entries without data and filled in with ones" << std::endl;
    std::cout << "     5) Symmetric matrix with only lower half entries without data and filled in randomly" << std::endl;
    std::cout << "     Other) Arbitrary matrix with data present" << std::endl;
    std::cout << "  1° Kronecker graph input file (.bin extension). Filename starts with size and then an indicator: " << std::endl;
    std::cout << "     1) Arbitrary matrix with no data present and filled in with ones" << std::endl;
    std::cout << "     2) Arbitrary matrix with no data present and random fill in" << std::endl;
    std::cout << "     3) Symmetric matrix with only lower half entries without data and filled in with ones" << std::endl;
    std::cout << "     Other) Symmetric matrix with only lower half entries without data and filled in randomly" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printErrorMsg();
        return -1;
    }

    std::string input_file = argv[1];

    // Input matrix & initialize vectors
    pwm::Triplet<data_t, index_t> input_mat;
    pwm::loadMatrixFromFile(&input_mat, input_file);

    double rows_avg = (double)input_mat.nnz / (double)input_mat.row_size;

    index_t lg_sqrt_size = (index_t)(std::ceil(std::log2(std::sqrt((double)input_mat.row_size))));
    index_t block_bits = std::min<index_t>(16, 3+lg_sqrt_size);
    index_t block_size = (index_t)(std::pow(2, block_bits));
    index_t nb_blocks = pwm::integerCeil(input_mat.row_size, block_size);

    index_t* rows_nnz = new index_t[input_mat.row_size];
    std::fill(rows_nnz, rows_nnz+input_mat.row_size, 0);

    index_t** block_nnz = new index_t*[nb_blocks];
    for (index_t i = 0; i < nb_blocks; ++i) {
        block_nnz[i] = new index_t[nb_blocks];
        std::fill(block_nnz[i], block_nnz[i]+nb_blocks, 0);
    }

    for (index_t i = 0; i < input_mat.nnz; ++i) {
        rows_nnz[input_mat.row_coord[i]]++;
        block_nnz[input_mat.row_coord[i] / block_size][input_mat.col_coord[i] / block_size]++;
    }

    double rows_var = 0;
    for (index_t i = 0; i < input_mat.row_size; ++i) {
        rows_var += std::pow(rows_nnz[i]-rows_avg, 2)/input_mat.row_size;
    }

    if (input_mat.row_size % block_size != 0) {
        // If the block size does not evenly divide the matrix size we only take into account the whole blocks
        nb_blocks--;
    }

    double block_avg = 0;
    for (index_t i = 0; i < nb_blocks; ++i) {
        for (index_t j = 0; j < nb_blocks; ++j) {
            block_avg += (double)block_nnz[i][j] / std::pow((double)nb_blocks, 2);
        }
    }

    double block_var = 0;
    for (index_t i = 0; i < nb_blocks; ++i) {
        for (index_t j = 0; j < nb_blocks; ++j) {
            block_var += std::pow((double)block_nnz[i][j]-block_avg, 2) / std::pow((double)nb_blocks, 2);
        }
    }

    std::cout << "Average nnz per row:       " << rows_avg << std::endl;
    std::cout << "Variance of nnz per row:   " << rows_var << std::endl;
    std::cout << "Average nnz per block:     " << block_avg << std::endl;
    std::cout << "Variance of nnz per block: " << block_var << std::endl;

    delete [] rows_nnz;
    for (index_t i = 0; i < nb_blocks; ++i) {
        delete [] block_nnz[i];
    }
    delete [] block_nnz;
}