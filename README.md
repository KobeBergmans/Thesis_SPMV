# Powermethod implementation

## Prerequisites

* Boost
* oneTBB 

## Running the code

* Compile driver with `make driver` or `make driver_debug`
* Run the driver with the right arguments:
```
1° Amount of times the power algorithm is executed
2° Amount of warm up runs for the power algorithm (not timed)
3° Amount of iterations in the power method algorithm
4° Poisson equation discretization steps
5° Method to use:
   1) Standard CRS (sequential)
   2) CRS parallelized using OpenMP
   3) CRS parallelized using TBB
   4) CRS parallelized using TBB graphs
   5) CRS parallelized using Boost Thread Pool
6° Amount of threads (only for a parallel method). -1 lets the program choose the amount of threads arbitrarily
7° Amount of partitions the matrix is split up into (only for method 4 and 5)
```