driver:
	g++ -Wall -DNDEBUG -O3 -fopenmp -o driver driver.cpp

driver_debug:
	g++ -Wall -Og -fopenmp -o driver driver.cpp