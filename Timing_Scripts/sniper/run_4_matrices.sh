# Runs simulations for the 4 given matrices with a given config
# (Takes approximately 10h for test matrices and uses 32 threads)
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Matrix input file 4
#   - Sniper config file

sh Timing_Scripts/sniper/run_2_thread.sh $1 $5 "2_thread_1" & sh Timing_Scripts/sniper/run_2_thread.sh $2 $5 "2_thread_2"
wait
sh Timing_Scripts/sniper/run_2_thread.sh $3 $5 "2_thread_3" & sh Timing_Scripts/sniper/run_2_thread.sh $4 $5 "2_thread_4"
wait

sh Timing_Scripts/sniper/run_8_thread.sh $1 $5 "8_thread_1"
sh Timing_Scripts/sniper/run_8_thread.sh $2 $5 "8_thread_2"
sh Timing_Scripts/sniper/run_8_thread.sh $3 $5 "8_thread_3"
sh Timing_Scripts/sniper/run_8_thread.sh $4 $5 "8_thread_4"