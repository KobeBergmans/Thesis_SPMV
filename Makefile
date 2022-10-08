driver:
	g++ -Wall -DNDEBUG -O3 -fopenmp -o driver driver.cpp -ltbb -lboost_thread

driver_debug:
	g++ -Wall -Og -fopenmp -o driver driver.cpp -ltbb_debug -lboost_thread

MPI_driver:
	mpicxx -Wall -DNDEBUG -O3 -o MPI_driver MPI_driver.cpp

MPI_driver_debug:
	mpicxx -Wall -Og -o MPI_driver MPI_driver.cpp