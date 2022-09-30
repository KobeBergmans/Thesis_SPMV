/**
 * @file SparseMatrix.hpp
 * @author Kobe Bergmans (kobe.bergmans@student.kuleuven.be)
 * @brief Base interface for all solvers
 * @version 0.1
 * @date 2022-09-30
 */

#ifndef PWM_SPARSEMATRIX_HPP
#define PWM_SPARSEMATRIX_HPP

namespace pwm {
    template<typename T, typename int_type>
    class SparseMatrix {
        protected:
            // Number of rows
            int_type nor;
            
            // Number of columns
            int_type noc;

            // Number of nonzeros
            int_type nnz;

        public:
            // Base constructor
            SparseMatrix() {}

            // Base constructor
            SparseMatrix(const int_type nzs, const int_type nr, const int_type nc)
                :nnz(nzs), nor(nr), noc(nc) {}

            /**
             * @brief Generate Sparse matrix comming from discretizised 2D laplace matrix
             * 
             * @param size size of the matrix
             */
            virtual void generatePoissonMatrix(const int_type size);
            
            
            /**
             * @brief Sparse matrix vector product calculation
             * 
             * @param x Vector to be modified with the matrix
             * @return T* Result vector
             */
            virtual T* mv(const T* x);

            /**
             * @brief Power method
             * 
             * @param x Input vector to start power method
             * @param it Amount of iterations
             * @return T* Resulting vector
             */
            virtual T* powerMethod(const T* x, const int_type it);

    };
} // namespace pwm



#endif // PWM_SPARSEMATRIX_HPP