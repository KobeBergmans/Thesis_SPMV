driver_poisson:
	dpcpp -Wall -DNDEBUG -O3 -qopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -qopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_debug:
	dpcpp -Wall -Og -qopenmp -o driver_poisson driver_poisson.cpp -ltbb_debug -lboost_thread

MPI_driver_poisson:
	mpicxx -Wall -DNDEBUG -O3 -qopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

MPI_driver_poisson_debug:
	mpicxx -Wall -Og -qopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

driver_input:
	dpcpp -Wall -DNDEBUG -O3 -qopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -qopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_debug:
	dpcpp -Wall -Og -qopenmp -o driver_input driver_input.cpp -ltbb_debug -lboost_thread

test:
	dpcpp -Wall -Og -qopenmp -o test test.cpp -ltbb_debug -lboost_thread