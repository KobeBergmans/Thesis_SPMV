# Runs spmv input driver for a given matrix and a specified amount of times for all partioning methods with a given amount of threads and partitions
# Inputs:
# - Matrix file
# - Amount of timed runs
# - Amount of warmup runs
# - Starting thread amount
# - End thread amount
# - Starting partition multiplier
# - Ending partition multiplier

for partition in $(seq $6 $7)
do
    echo "Running TBB_graphs_$partition implementation"
    for thread in $(seq $4 $5)
    do
        ./driver_spmv_input $1 $2 $3 4 $thread $(($thread*$partition))
    done


    echo "Running Threadpool_$partition implementation"
    for thread in $(seq $4 $5)
    do
        ./driver_spmv_input $1 $2 $3 6 $thread $(($thread*$partition))
    done
done