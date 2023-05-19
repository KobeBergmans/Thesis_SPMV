# SpMV multiplication and powermethod implementation for the 2D discretized poisson matrix or input matrices in matrix market format

The code in this repository was written to perform the needed tests for my thesis to finish my master in mathematical engineering at the department of engineering of the KU Leuven.

The code consists of code to perform a sparse matrix-vector (SpMV) multiplication for the discretized poisson matrix or a matrix which is loaded in from matrix market format. These SpMV multiplications are performed by [executing the drivers](README#running-the-code). These drivers are not made to inspect the resulting output, but they are used to time the execution of the code, they include options to specify the amount of timed runs and warmup runs. All code is also testable by [running the tests](README#running-the-tests). Finally, there is also a driver which is used to simulate the code execution: driver_sniper. This driver includes special directives of the [sniper simulator](snipersim.org). This driver includes one warmup run and a timed run.

The different implementations of the SpMV multiplications can be categorized. First, there is a sequential implementation of the CRS algorithm. This method is implemented in [Matrix/CRS](Matrix/CRS.hpp). Then, there is a class of methods which are parallelizations of the basic CRS algorithm. These parallelizations are performed with different parallel libraries. These methods are stored in the folder [Env_Implementations](Env_Implementations/). Following methods are available:
* [CRSOMP](Env_Implementations/CRSOMP.hpp): Dynamic parallelization using OpenMP pragma's.
* [CRSTBB](Env_Implementations/CRSTBB.hpp): Dynamic parallelization using TBB parallel_for function.
* [CRSTBBGraph](Env_Implementations/CRSTBBGraph.hpp): Static parallelization using a TBB graph object.
* [CRSTBBGraphPinned](Env_Implementations/CRSTBBGraphPinned.hpp): Identical to the previous parallelization but with partitions always pinned to the same threads.
* [CRSThreadPool](Env_Implementations/CRSThreadPool.hpp): Static parallelization using functions posted to a Boost thread_pool.
* [CRSThreadPoolPinned](Env_Implementations/CRSThreadPoolPinned.hpp): Identical to the previous parallelization but with partitions always pinned to the same threads.

Finally, there are also the state of the art methods which are taken from research. These methods are stored in the [SOA_Implementations](SOA_Implementations/) folder and contain the following methods:
* [Row distributed block CO-H](SOA_Implementations/BlockCOH.hpp) [1]: Parallelization which statically splits up nonzeros amongst threads. The respective block row per thread is split up into blocks which are ordered in hilbert order.
* [Compressed sparse blocks](SOA_Implementations/CSB.hpp) [2]: Parallelization which uses openMP tasking. The matrix is split up completely in hypersparse blocks. The resulting block rows are considered as tasks. If a block row consists of too many nonzeros this block row is split up into multiple tasks. Furthermore, if there are any dense blocks, these blocks are considered as individual tasks, and they can be split up if they contain too many nonzeros. Based on: A. Buluç, J. T. Fineman, M. Frigo, J. R. Gilbert, and C. E. Leiserson. Parallel sparse matrix-vector and matrix-transpose-vector multiplication using compressed sparse blocks. In Proceedings of the Twenty-First Annual Symposium on Parallelism in Algorithms and Architectures, SPAA ’09, pages 233–244, New York, NY, USA, 2009. Association for Computing Machinery.
* [Merge-based CRS](SOA_Implementations/CRS_Merge.hpp) [3]: Static parallelization of the CRS structure, which tries to obtain optimal load balancing.

## Prerequisites

driver_input, driver_poisson and driver_spmv_input:
* dpcpp (version 2021.4.0 & 2022.2.1 tested)
* OpenMP 
* Boost (version 1.71 & 1.74 tested)
* oneapi TBB (2021.4.0 & 2021.7.1 tested)

driver_sniper:
* icx (version 2021.4.0 tested)
* OpenMP
* Boost (version 1.71 tested)
* snipersim (tested on commit [b58797c](https://github.com/snipersim/snipersim/commit/b58797c3993148174c7de23a18f71fc22e92340f)) installed in directory $SNIPER

## Running the code


driver_poisson, driver_input, driver_spmv_input:
* Compile the program with `make driver_name` or `make driver_name_debug`
* Run `./driver_name` with the right arguments. To check the arguments, run the code without specifying arguments and a help message will pop up.

driver_sniper:
* Compile the program with `make driver_sniper` or `make driver_sniper_debug`
* To run simulations there are two options. You can run `make run_sniper` with the correct arguments to quickly run a sniper simulation. Or the the driver program can be inputted to the sniper simulator manually.

## Running the tests

The tests are made such that each implementation of SpMV multiplication is correct for a couple of matrices and different amounts of threads. The tests can be compiled by running `make test` and then run by performing `./test`.

The input matrices on which the tests are run are obtained from the university of Florida sparse matrix collection [4].

## Remarks
* There was not a way found to pin threads of threadpool or TBB to a CPU for cache reuse. The only way found was to force this in execution of the function/node by setting the affinity. This does not mean that a thread is fixed to a CPU but that only the tasks are fixed to a CPU. This is thus suboptimal.
* Results for timings on different versions can be found in the folder Timing_Results.

## References
[1]: A.-J. N. Yzelman and D. Roose. High-level strategies for parallel shared-memory sparse matrix-vector multiplication. IEEE Transactions on Parallel and Distributed Systems, 25(1):116–125, 2014.

[2]: A. Buluç, J. T. Fineman, M. Frigo, J. R. Gilbert, and C. E. Leiserson. Parallel sparse matrix-vector and matrix-transpose-vector multiplication using compressed sparse blocks. In Proceedings of the Twenty-First Annual Symposium on Parallelism in Algorithms and Architectures, SPAA ’09, pages 233–244, New York, NY, USA, 2009. Association for Computing Machinery.

[3]: D. Merrill and M. Garland. Merge-based parallel sparse matrix-vector multiplication. In SC ’16: Proceedings of the International Conference for High Performance Computing, Networking, Storage and Analysis, pages 678–689, 2016.

[4]: T. A. Davis and Y. Hu. The university of florida sparse matrix collection. ACM Trans. Math. Softw., 38(1), dec 2011.