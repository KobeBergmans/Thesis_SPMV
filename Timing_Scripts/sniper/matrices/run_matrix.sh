# Runs simulations for the given matrices with a given config with 2 and 8 threads
# Inputs:
#   - Matrix input file
#   - Sniper config file

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_2_thread.sh $1 $2 "2_thread_matrix" & 
sh Timing_Scripts/sniper/thread/run_8_thread.sh $1 $2 "8_thread_matrix"

wait