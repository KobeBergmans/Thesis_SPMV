driver_poisson:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread

driver_poisson_debug:
	dpcpp -Wall -Og -fopenmp -o driver_poisson driver_poisson.cpp -ltbb_debug -lboost_thread

MPI_driver_poisson:
	mpicxx -Wall -DNDEBUG -O3 -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

MPI_driver_poisson_debug:
	mpicxx -Wall -Og -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

driver_input:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_vtune:
	dpcpp -Wall -DNDEBUG -O3 -g -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread

driver_input_debug:
	dpcpp -Wall -Og -fopenmp -o driver_input driver_input.cpp -ltbb_debug -lboost_thread

driver_sniper:
	dpcpp -Wall -DNDEBUG -O3 -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -ltbb -lboost_thread

sniper:
	${SNIPER}/run-sniper -n 8 -c gainestown --roi -d ./Sniper_Out/ --viz -- ./driver_sniper "Input/2_wikipedia-20061104.mtx" 1 1 1 1

test:
	dpcpp -Wall -Og -fopenmp -o test test.cpp -ltbb_debug -lboost_thread