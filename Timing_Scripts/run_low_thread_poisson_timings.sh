#!/bin/sh

echo "Make executable..."
rm driver_poisson
make driver_poisson

echo "Running sequential algorithm..."
./driver_poisson $1 $2 $3 $4 1

echo "Running TBB implementation with 2 - 8 threads..."
./driver_poisson $1 $2 $3 $4 3 2 
./driver_poisson $1 $2 $3 $4 3 3
./driver_poisson $1 $2 $3 $4 3 4
./driver_poisson $1 $2 $3 $4 3 5
./driver_poisson $1 $2 $3 $4 3 6
./driver_poisson $1 $2 $3 $4 3 7
./driver_poisson $1 $2 $3 $4 3 8