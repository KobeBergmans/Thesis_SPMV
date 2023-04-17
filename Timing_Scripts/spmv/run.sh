# Runs spmv input driver for a given matrix and a specified amount of times for all methods using a given amount of threads
# Inputs:
# - Matrix file
# - Amount of timed runs
# - Amount of warmup runs
# - Starting thread amount
# - End thread amount

rm -f driver_spmv_input
make driver_spmv_input

echo "Running sequential algorithm"
./driver_spmv_input $1 $2 $3 1

echo "Running OpenMP implementation"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 2 $thread
done

echo "Running TBB implementation"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 3 $thread
done

echo "Running TBB_graphs_6 implementation with double the amount of partitions than threads"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 4 $thread $(($thread*6))
done


echo "Running Threadpool_10 implementation with double the amount of partitions than threads"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 6 $thread $(($thread*10))
done

echo "Running CRSMerge implementation"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 8 $thread
done

echo "Running CSB implementation"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 9 $thread
done

echo "Running BlockCOH implementation"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 10 $thread
done