echo "Running sequential algorithm..."
./driver_spmv_input $1 $2 $3 1

echo "Running CRSMerge with 10, 12 and 14 threads"
./driver_spmv_input $1 $2 $3 8 10
./driver_spmv_input $1 $2 $3 8 12
./driver_spmv_input $1 $2 $3 8 14

echo "Running CSB with 10, 12, 14 threads"
./driver_spmv_input $1 $2 $3 9 10
./driver_spmv_input $1 $2 $3 9 12
./driver_spmv_input $1 $2 $3 9 14

echo "Running BlockCOH with 10, 12 and 14 threads"
./driver_spmv_input $1 $2 $3 10 10
./driver_spmv_input $1 $2 $3 10 12
./driver_spmv_input $1 $2 $3 10 14