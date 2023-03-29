echo "Running method $4 with 2-8 threads"

./driver_spmv_input $1 $2 $3 $4 2
./driver_spmv_input $1 $2 $3 $4 3
./driver_spmv_input $1 $2 $3 $4 4
./driver_spmv_input $1 $2 $3 $4 5
./driver_spmv_input $1 $2 $3 $4 6
./driver_spmv_input $1 $2 $3 $4 7
./driver_spmv_input $1 $2 $3 $4 8