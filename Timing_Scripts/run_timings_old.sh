#!/bin/sh

echo "Make executables..."
rm driver_poisson
make driver_poisson
rm MPI_driver_poisson
make MPI_driver_poisson

echo "Running sequential algorithm..."
./driver_poisson $1 $2 $3 $4 1

echo "Running OpenMP implementation with 2 - 8 threads..."
./driver_poisson $1 $2 $3 $4 2 2
./driver_poisson $1 $2 $3 $4 2 3
./driver_poisson $1 $2 $3 $4 2 4
./driver_poisson $1 $2 $3 $4 2 5
./driver_poisson $1 $2 $3 $4 2 6
./driver_poisson $1 $2 $3 $4 2 7
./driver_poisson $1 $2 $3 $4 2 8

echo "Running TBB implementation with 2 - 8 threads..."
./driver_poisson $1 $2 $3 $4 3 2
./driver_poisson $1 $2 $3 $4 3 3
./driver_poisson $1 $2 $3 $4 3 4
./driver_poisson $1 $2 $3 $4 3 5
./driver_poisson $1 $2 $3 $4 3 6
./driver_poisson $1 $2 $3 $4 3 7
./driver_poisson $1 $2 $3 $4 3 8

echo "Running TBB graphs implementation with 2 - 8 threads and partitions equal to threads"
./driver_poisson $1 $2 $3 $4 4 2 2
./driver_poisson $1 $2 $3 $4 4 3 3
./driver_poisson $1 $2 $3 $4 4 4 4
./driver_poisson $1 $2 $3 $4 4 5 5
./driver_poisson $1 $2 $3 $4 4 6 6
./driver_poisson $1 $2 $3 $4 4 7 7
./driver_poisson $1 $2 $3 $4 4 8 8

echo "Running TBB graphs implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_poisson $1 $2 $3 $4 4 2 4
./driver_poisson $1 $2 $3 $4 4 3 6
./driver_poisson $1 $2 $3 $4 4 4 8
./driver_poisson $1 $2 $3 $4 4 5 10
./driver_poisson $1 $2 $3 $4 4 6 12
./driver_poisson $1 $2 $3 $4 4 7 14
./driver_poisson $1 $2 $3 $4 4 8 16

echo "Running TBB graphs pinned implementation with 2 - 8 threads and partitions equal to threads"
./driver_poisson $1 $2 $3 $4 5 2 2
./driver_poisson $1 $2 $3 $4 5 3 3
./driver_poisson $1 $2 $3 $4 5 4 4
./driver_poisson $1 $2 $3 $4 5 5 5
./driver_poisson $1 $2 $3 $4 5 6 6
./driver_poisson $1 $2 $3 $4 5 7 7
./driver_poisson $1 $2 $3 $4 5 8 8

echo "Running TBB graphs pinned implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_poisson $1 $2 $3 $4 5 2 4
./driver_poisson $1 $2 $3 $4 5 3 6
./driver_poisson $1 $2 $3 $4 5 4 8
./driver_poisson $1 $2 $3 $4 5 5 10
./driver_poisson $1 $2 $3 $4 5 6 12
./driver_poisson $1 $2 $3 $4 5 7 14
./driver_poisson $1 $2 $3 $4 5 8 16

echo "Running Threadpool implementation with 2 - 8 threads and partitions equal to threads"
./driver_poisson $1 $2 $3 $4 6 2 2
./driver_poisson $1 $2 $3 $4 6 3 3
./driver_poisson $1 $2 $3 $4 6 4 4
./driver_poisson $1 $2 $3 $4 6 5 5
./driver_poisson $1 $2 $3 $4 6 6 6
./driver_poisson $1 $2 $3 $4 6 7 7
./driver_poisson $1 $2 $3 $4 6 8 8

echo "Running Threadpool implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_poisson $1 $2 $3 $4 6 2 4
./driver_poisson $1 $2 $3 $4 6 3 6
./driver_poisson $1 $2 $3 $4 6 4 8
./driver_poisson $1 $2 $3 $4 6 5 10
./driver_poisson $1 $2 $3 $4 6 6 12
./driver_poisson $1 $2 $3 $4 6 7 14
./driver_poisson $1 $2 $3 $4 6 8 16

echo "Running Threadpool pinned implementation with 2 - 8 threads and partitions equal to threads"
./driver_poisson $1 $2 $3 $4 7 2 2
./driver_poisson $1 $2 $3 $4 7 3 3
./driver_poisson $1 $2 $3 $4 7 4 4
./driver_poisson $1 $2 $3 $4 7 5 5
./driver_poisson $1 $2 $3 $4 7 6 6
./driver_poisson $1 $2 $3 $4 7 7 7
./driver_poisson $1 $2 $3 $4 7 8 8

echo "Running Threadpool pinned implementation with 2 - 8 threads and double the amount of partitions than threads"
./driver_poisson $1 $2 $3 $4 7 2 4
./driver_poisson $1 $2 $3 $4 7 3 6
./driver_poisson $1 $2 $3 $4 7 4 8
./driver_poisson $1 $2 $3 $4 7 5 10
./driver_poisson $1 $2 $3 $4 7 6 12
./driver_poisson $1 $2 $3 $4 7 7 14
./driver_poisson $1 $2 $3 $4 7 8 16

echo "Running MPI implementation with 2-4 cores"
mpirun -n 2 ./MPI_driver_poisson $1 $2 $3 $4
mpirun -n 3 ./MPI_driver_poisson $1 $2 $3 $4
mpirun -n 4 ./MPI_driver_poisson $1 $2 $3 $4