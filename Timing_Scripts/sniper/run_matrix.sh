# Runs simulations for the given matrices with a given config with 2 and 8 threads
# Inputs:
#   - Matrix input file
#   - Sniper config file

sh Timing_Scripts/sniper/run_2_thread.sh $1 $2 "2_thread_matrix" & 
sh Timing_Scripts/sniper/run_8_thread.sh $1 $2 "8_thread_matrix"

wait