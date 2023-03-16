# POISSON DRIVER:
driver_poisson:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_ntbb:
	dpcpp -Wall -DNDEBUG -DNTBB -O3 -fopenmp -o driver_poisson driver_poisson.cpp -lboost_thread

driver_poisson_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_debug:
	dpcpp -Wall -Og -fopenmp -o driver_poisson driver_poisson.cpp -ltbb_debug -lboost_thread

driver_poisson_debug_ntbb:
	dpcpp -Wall -DNTBB -Og -fopenmp -o driver_poisson driver_poisson.cpp -lboost_thread

# MPI POISSON DRIVER
MPI_driver_poisson:
	mpicxx -Wall -DNDEBUG -O3 -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

MPI_driver_poisson_debug:
	mpicxx -Wall -Og -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

# INPUT DRIVER
driver_input:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_ntbb:
	dpcpp -Wall -DNTBB -DNDEBUG -O3 -fopenmp -o driver_input driver_input.cpp -lboost_thread

driver_input_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_debug:
	dpcpp -Wall -Og -fopenmp -o driver_input driver_input.cpp -ltbb_debug -lboost_thread

driver_input_debug_ntbb:
	dpcpp -Wall -DNTBB -Og -fopenmp -o driver_input driver_input.cpp -lboost_thread

# SPMV INPUT DRIVER
driver_spmv_input:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -o driver_spmv_input driver_spmv_input.cpp -ltbb -lboost_thread

driver_spmv_input_ntbb:
	dpcpp -Wall -DNTBB -DNDEBUG -O3 -fopenmp -o driver_spmv_input driver_spmv_input.cpp -lboost_thread

driver_spmv_input_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -fopenmp -o driver_spmv_input driver_spmv_input.cpp -ltbb -lboost_thread

driver_spmv_input_debug:
	dpcpp -Wall -Og -fopenmp -o driver_spmv_input driver_spmv_input.cpp -ltbb_debug -lboost_thread

driver_spmv_input_debug_ntbb:
	dpcpp -Wall -Og -DNTBB -fopenmp -o driver_spmv_input driver_spmv_input.cpp -lboost_thread

# SNIPER DRIVER (uses icx and NTBB because tbb and dpcpp (uses tbb) are not supported in sniper)
driver_sniper:
	icx -Wall -DNDEBUG -DNTBB -O3 -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -lboost_thread -lstdc++

driver_sniper_debug:
	icx -Wall -DNTBB -Og -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -lboost_thread -lstdc++

# TESTS
test:
	dpcpp -Wall -Og -fopenmp -o test test.cpp -ltbb_debug -lboost_thread