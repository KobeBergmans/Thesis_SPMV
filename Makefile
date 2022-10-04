driver:
	g++ -Wall -DNDEBUG -O3 -fopenmp -o driver driver.cpp -ltbb -lboost_thread

driver_debug:
	g++ -Wall -Og -fopenmp -o driver driver.cpp -ltbb_debug -lboost_thread