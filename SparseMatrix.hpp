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
             * @brief Fill the given matrix as a 2D discretized poisson matrix with equal discretization steplength in x and y
             * 
             * @param n The amount of discretization steps in the x direction
             * @param m The amount of discretization steps in the y direction
             */
            virtual void generatePoissonMatrix(const int_type n, const int_type m) = 0;
            
            
            /**
             * @brief Sparse matrix vector product calculation
             * 
             * @param x Vector to be modified with the matrix
             * @return T* Result vector
             */
            virtual void mv(const T* x, T* y) = 0;

            /**
             * @brief Power method
             * 
             * @param x Input vector to start power method
             * @param it Amount of iterations
             * @return T* Resulting vector
             */
            virtual void powerMethod(T* x, T* y, const int_type it) = 0;

    };
} // namespace pwm



#endif // PWM_SPARSEMATRIX_HPP