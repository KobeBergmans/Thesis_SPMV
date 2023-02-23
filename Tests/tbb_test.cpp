#include <iostream>

// #include "oneapi/tbb.h"
#include <tbb/parallel_for.h>

int main(int argc, char** argv) {
    tbb::parallel_for(0, 10, [=](int i) {
        std::cout << "Iteration: " << i << std::endl;
    });

    
    return 0;
}