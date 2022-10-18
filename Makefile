driver_poisson:
	g++ -Wall -DNDEBUG -O3 -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_debug:
	g++ -Wall -Og -fopenmp -o driver_poisson driver_poisson.cpp -ltbb_debug -lboost_thread

MPI_driver_poisson:
	mpicxx -Wall -DNDEBUG -O3 -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp

MPI_driver_poisson_debug:
	mpicxx -Wall -Og -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp