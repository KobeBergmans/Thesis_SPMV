#!/bin/sh

echo "Make executable..."
rm driver_input
make driver_input

echo "Running sequential algorithm..."
./driver_input $1 $2 $3 $4 1

echo "Running OpenMP implementation with 2 - 8 threads..."
./driver_input $1 $2 $3 $4 2 2
./driver_input $1 $2 $3 $4 2 3
./driver_input $1 $2 $3 $4 2 4
./driver_input $1 $2 $3 $4 2 5
./driver_input $1 $2 $3 $4 2 6
./driver_input $1 $2 $3 $4 2 7
./driver_input $1 $2 $3 $4 2 8

echo "Running TBB implementation with 2 - 8 threads..."
./driver_input $1 $2 $3 $4 3 2
./driver_input $1 $2 $3 $4 3 3
./driver_input $1 $2 $3 $4 3 4
./driver_input $1 $2 $3 $4 3 5
./driver_input $1 $2 $3 $4 3 6
./driver_input $1 $2 $3 $4 3 7
./driver_input $1 $2 $3 $4 3 8

echo "Running TBB_graphs implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 4 2 4
./driver_input $1 $2 $3 $4 4 3 6
./driver_input $1 $2 $3 $4 4 4 8
./driver_input $1 $2 $3 $4 4 5 10
./driver_input $1 $2 $3 $4 4 6 12
./driver_input $1 $2 $3 $4 4 7 14
./driver_input $1 $2 $3 $4 4 8 16

echo "Running TBB_graphs_pinned implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 5 2 4
./driver_input $1 $2 $3 $4 5 3 6
./driver_input $1 $2 $3 $4 5 4 8
./driver_input $1 $2 $3 $4 5 5 10
./driver_input $1 $2 $3 $4 5 6 12
./driver_input $1 $2 $3 $4 5 7 14
./driver_input $1 $2 $3 $4 5 8 16

echo "Running Threadpool implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 6 2 4
./driver_input $1 $2 $3 $4 6 3 6
./driver_input $1 $2 $3 $4 6 4 8
./driver_input $1 $2 $3 $4 6 5 10
./driver_input $1 $2 $3 $4 6 6 12
./driver_input $1 $2 $3 $4 6 7 14
./driver_input $1 $2 $3 $4 6 8 16

echo "Running Threadpool_pinned implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_input $1 $2 $3 $4 7 2 4
./driver_input $1 $2 $3 $4 7 3 6
./driver_input $1 $2 $3 $4 7 4 8
./driver_input $1 $2 $3 $4 7 5 10
./driver_input $1 $2 $3 $4 7 6 12
./driver_input $1 $2 $3 $4 7 7 14
./driver_input $1 $2 $3 $4 7 8 16