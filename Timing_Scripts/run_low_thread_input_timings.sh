#!/bin/sh

echo "Make executable..."
rm driver_input
make driver_input

echo "Running sequential algorithm..."
./driver_input $1 $2 $3 $4 1

echo "Running TBB implementation with 2 - 8 threads..."
./driver_input $1 $2 $3 $4 3 2 
./driver_input $1 $2 $3 $4 3 3
./driver_input $1 $2 $3 $4 3 4
./driver_input $1 $2 $3 $4 3 5
./driver_input $1 $2 $3 $4 3 6
./driver_input $1 $2 $3 $4 3 7
./driver_input $1 $2 $3 $4 3 8