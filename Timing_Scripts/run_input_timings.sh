#!/bin/sh

echo "Make executable..."
rm driver_input
make driver_input

echo "Running sequential algorithm..."
./driver_input $1 $2 $3 $4 1

echo "Running OpenMP implementation with 6 - 36 threads..."
./driver_input $1 $2 $3 $4 2 6
./driver_input $1 $2 $3 $4 2 12
./driver_input $1 $2 $3 $4 2 18
./driver_input $1 $2 $3 $4 2 24
./driver_input $1 $2 $3 $4 2 30
./driver_input $1 $2 $3 $4 2 36

echo "Running TBB implementation with 6 - 36 threads..."
./driver_input $1 $2 $3 $4 3 6 
./driver_input $1 $2 $3 $4 3 12
./driver_input $1 $2 $3 $4 3 18
./driver_input $1 $2 $3 $4 3 24
./driver_input $1 $2 $3 $4 3 30
./driver_input $1 $2 $3 $4 3 36

echo "Running TBB_graphs implementation with 6 - 36 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 4 6  12
./driver_input $1 $2 $3 $4 4 12 24
./driver_input $1 $2 $3 $4 4 18 36
./driver_input $1 $2 $3 $4 4 24 48
./driver_input $1 $2 $3 $4 4 30 60
./driver_input $1 $2 $3 $4 4 36 72

echo "Running TBB_graphs_pinned implementation with 6 - 36 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 5 6  12
./driver_input $1 $2 $3 $4 5 12 24
./driver_input $1 $2 $3 $4 5 18 36
./driver_input $1 $2 $3 $4 5 24 48
./driver_input $1 $2 $3 $4 5 30 60
./driver_input $1 $2 $3 $4 5 36 72

echo "Running Threadpool implementation with 6 - 36 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 6 6  12
./driver_input $1 $2 $3 $4 6 12 24
./driver_input $1 $2 $3 $4 6 18 36
./driver_input $1 $2 $3 $4 6 24 48
./driver_input $1 $2 $3 $4 6 30 60
./driver_input $1 $2 $3 $4 6 36 72

echo "Running Threadpool_pinned implementation with 6 - 36 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 7 6  12
./driver_input $1 $2 $3 $4 7 12 24
./driver_input $1 $2 $3 $4 7 18 36
./driver_input $1 $2 $3 $4 7 24 48
./driver_input $1 $2 $3 $4 7 30 60
./driver_input $1 $2 $3 $4 7 36 72