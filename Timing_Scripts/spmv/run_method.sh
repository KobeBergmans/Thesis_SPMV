# Runs spmv input driver for a given matrix and a specified amount of times for a given method using a given amount of threads
# Inputs:
# - Matrix file
# - Amount of timed runs
# - Amount of warmup runs
# - Method
# - Starting thread amount
# - End thread amount

rm -f driver_spmv_input
make driver_spmv_input

echo "Running method $4"
for thread in $(seq $4 $5)
do
./driver_spmv_input $1 $2 $3 $4 $thread
done