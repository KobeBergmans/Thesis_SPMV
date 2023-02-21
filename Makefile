driver_poisson:
	icx -Wall -DNDEBUG -O3 -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread -lstdc++

driver_poisson_vtune:
	icx -Wall -DNDEBUG -O3 -g -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread -lstdc++

driver_poisson_debug:
	icx -Wall -Og -fopenmp -o driver_poisson driver_poisson.cpp -ltbb -lboost_thread -lstdc++

MPI_driver_poisson:
	mpicxx -Wall -DNDEBUG -O3 -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb

MPI_driver_poisson_debug:
	mpicxx -Wall -Og -fopenmp -o MPI_driver_poisson MPI_driver_poisson.cpp -ltbb 

driver_input:
	icx -Wall -DNDEBUG -O3 -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread -lstdc++

driver_input_vtune:
	icx -Wall -DNDEBUG -O3 -g -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread -lstdc++

driver_input_debug:
	icx -Wall -Og -fopenmp -o driver_input driver_input.cpp -ltbb -lboost_thread -lstdc++

driver_sniper:
	icx -Wall -DNDEBUG -O3 -fopenmp -I${SNIPER}/include -o driver_sniper driver_sniper.cpp -ltbb -lboost_thread -lstdc++

sniper:
	${SNIPER}/run-sniper -n 2 -c gainestown --roi -d ./Sniper_Out/ --viz -- ./driver_sniper "Input/23_3_mycielskian5.bin" 1 1 1 2 -1

test:
	icx -Wall -Og -fopenmp -o test test.cpp -ltbb -lboost_thread -lstdc++