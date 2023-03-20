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

driver_spmv_input_mkl:
	dpcpp -Wall -DNDEBUG -DMKL -O3 -fsycl -DMKL_ILP64  -I"${MKLROOT}/include" -fopenmp -o driver_spmv_input driver_spmv_input.cpp -ltbb -lboost_thread -fsycl  -L${MKLROOT}/lib/intel64 -lmkl_sycl -lmkl_intel_ilp64 -lmkl_tbb_thread -lmkl_core -lsycl -lOpenCL -lpthread -lm -ldl

driver_spmv_input_debug_mkl:
	dpcpp -Wall -DMKL -Og -fsycl -DMKL_ILP64  -I"${MKLROOT}/include" -fopenmp -o driver_spmv_input driver_spmv_input.cpp -ltbb -lboost_thread -fsycl  -L${MKLROOT}/lib/intel64 -lmkl_sycl -lmkl_intel_ilp64 -lmkl_tbb_thread -lmkl_core -lsycl -lOpenCL -lpthread -lm -ldl

# SNIPER DRIVER (uses icx and NTBB because tbb and dpcpp (uses tbb) are not supported in sniper)
driver_sniper:
	icx -Wall -DNDEBUG -DNTBB -O3 -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -lboost_thread -lstdc++

driver_sniper_debug:
	icx -Wall -DNTBB -Og -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -lboost_thread -lstdc++

run_sniper:
	rm driver_sniper
	driver_sniper
	../snipersim/run-sniper -n ${core} -d ./Sniper_Out/ -s markers -s roi-iter::2:2 --roi-script --no-cache-warming --viz -- ./driver_sniper ${file} ${method} ${core}

# TESTS
test:
	dpcpp -Wall -Og -fopenmp -o test test.cpp -ltbb_debug -lboost_thread