# powerIteration implementation for Discretized Poisson equation matrix

## Prerequisites

driver_input & driver_poisson:
* dpcpp (version 2021.4.0 & 2022.2.1 tested)
* OpenMP 
* Boost (version 1.71 & 1.74 tested)
* oneapi TBB (2021.4.0 & 2021.7.1 tested)


## Running the code

driver_poisson:
* Compile the program with `make driver_poisson` or `make driver_poisson_debug`
* Run `./driver_poisson` with the right arguments:
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
     5) CRS parallelized using TBB graphs with each node pinned to a CPU
     6) CRS parallelized using Boost Thread Pool
     7) CRS parallelized using Boost Thread Pool with functions pinned to a CPU
  6° Amount of threads (only for a parallel method). -1 lets the program choose the amount of threads arbitrarily
  7° Amount of partitions the matrix is split up into (only for method 4, 5, 6 and 7)

```

driver_input:
* Compile the program with `make driver_input` or `make driver_input_debug`
* Run `./driver_input` with the right arguments:
```
  1° Filename of Matrix market (.mtx extension). Filename starts with: 
     1) Arbitrary matrix with no data present and filled in with ones
     2) Arbitrary matrix with no data present and random fill in
     3) Symmetric matrix with only lower half entries with data present
     4) Symmetric matrix with only lower half entries without data and filled in with ones
     5) Symmetric matrix with only lower half entries without data and filled in randomly
     Other) Arbitrary matrix with data present
  1° Kronecker graph input file (.bin extension). Filename starts with size and then an indicator: 
     1) Arbitrary matrix with no data present and filled in with ones
     2) Arbitrary matrix with no data present and random fill in
     3) Symmetric matrix with only lower half entries without data and filled in with ones
     Other) Symmetric matrix with only lower half entries without data and filled in randomly
  2° Amount of times the power algorithm is executed
  3° Amount of warm up runs for the power algorithm (not timed)
  4° Amount of iterations in the power method algorithm
  5° Method to use:
     1) Standard CRS (sequential)
     2) CRS parallelized using OpenMP
     3) CRS parallelized using TBB
     4) CRS parallelized using TBB graphs
     5) CRS parallelized using TBB graphs with each node pinned to a CPU
     6) CRS parallelized using Boost Thread Pool
     7) CRS parallelized using Boost Thread Pool with functions pinned to a CPU
  6° Amount of threads (only for a parallel method). -1 lets the program choose the amount of threads arbitrarily
  7° Amount of partitions the matrix is split up into (only for method 4, 5, 6 and 7)
```

## Remarks
* There was not a way found to pin threads of threadpool or TBB to a CPU for cache reuse. The only way found was to force this in execution of the function/node by setting the affinity. This does not mean that a thread is fixed to a CPU but that only the tasks are fixed to a CPU. This is thus suboptimal.
* Results for timings on different versions can be found in the folder Timing_Results.

