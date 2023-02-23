#include <iostream>
#include <unistd.h>

// #include "oneapi/tbb.h"
#include <tbb/parallel_for.h>

int main() {
    tbb::parallel_for(0, 10, [=](int i) {
        sleep(1);
        std::cout << "Iteration: " << i << std::endl;
    });

    
    return 0;
}