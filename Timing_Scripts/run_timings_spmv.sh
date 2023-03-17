echo "Running sequential algorithm..."
./driver_spmv_input $1 $2 $3 1

echo "Running OpenMP implementation with 2 - 8 threads..."
./driver_spmv_input $1 $2 $3 2 2
./driver_spmv_input $1 $2 $3 2 3
./driver_spmv_input $1 $2 $3 2 4
./driver_spmv_input $1 $2 $3 2 5
./driver_spmv_input $1 $2 $3 2 6
./driver_spmv_input $1 $2 $3 2 7
./driver_spmv_input $1 $2 $3 2 8

echo "Running TBB implementation with 2 - 8 threads..."
./driver_spmv_input $1 $2 $3 3 2
./driver_spmv_input $1 $2 $3 3 3
./driver_spmv_input $1 $2 $3 3 4
./driver_spmv_input $1 $2 $3 3 5
./driver_spmv_input $1 $2 $3 3 6
./driver_spmv_input $1 $2 $3 3 7
./driver_spmv_input $1 $2 $3 3 8

echo "Running TBB_graphs implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_spmv_input $1 $2 $3 4 2 4
./driver_spmv_input $1 $2 $3 4 3 6
./driver_spmv_input $1 $2 $3 4 4 8
./driver_spmv_input $1 $2 $3 4 5 10
./driver_spmv_input $1 $2 $3 4 6 12
./driver_spmv_input $1 $2 $3 4 7 14
./driver_spmv_input $1 $2 $3 4 8 16


echo "Running Threadpool implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_spmv_input $1 $2 6 2 4
./driver_spmv_input $1 $2 6 3 6
./driver_spmv_input $1 $2 6 4 8
./driver_spmv_input $1 $2 6 5 10
./driver_spmv_input $1 $2 6 6 12
./driver_spmv_input $1 $2 6 7 14
./driver_spmv_input $1 $2 6 8 16

echo "Running CRS_merge implementation with 2-8 threads"
./driver_spmv_input $1 $2 $3 8 2
./driver_spmv_input $1 $2 $3 8 3
./driver_spmv_input $1 $2 $3 8 4
./driver_spmv_input $1 $2 $3 8 5
./driver_spmv_input $1 $2 $3 8 6
./driver_spmv_input $1 $2 $3 8 7
./driver_spmv_input $1 $2 $3 8 8

echo "Running CSB implementation with 2-8 threads"
./driver_spmv_input $1 $2 $3 9 2
./driver_spmv_input $1 $2 $3 9 3
./driver_spmv_input $1 $2 $3 9 4
./driver_spmv_input $1 $2 $3 9 5
./driver_spmv_input $1 $2 $3 9 6
./driver_spmv_input $1 $2 $3 9 7
./driver_spmv_input $1 $2 $3 9 8

echo "Running Block CO-H implementation with 2-8 threads"
./driver_spmv_input $1 $2 $3 10 2
./driver_spmv_input $1 $2 $3 10 3
./driver_spmv_input $1 $2 $3 10 4
./driver_spmv_input $1 $2 $3 10 5
./driver_spmv_input $1 $2 $3 10 6
./driver_spmv_input $1 $2 $3 10 7
./driver_spmv_input $1 $2 $3 10 8

echo "Running CRS_merge, CSB, Block CO-H with 10, 12 and 14 threads"
./driver_spmv_input $1 $2 $3 8 10
./driver_spmv_input $1 $2 $3 8 12
./driver_spmv_input $1 $2 $3 8 14
./driver_spmv_input $1 $2 $3 9 10
./driver_spmv_input $1 $2 $3 9 12
./driver_spmv_input $1 $2 $3 9 14
./driver_spmv_input $1 $2 $3 10 10
./driver_spmv_input $1 $2 $3 10 12
./driver_spmv_input $1 $2 $3 10 14