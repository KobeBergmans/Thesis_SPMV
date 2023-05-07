# Runs simulations for the 6 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_256_thread.sh $1 $4 "256_thread_1_$5"
sh Timing_Scripts/sniper/thread/run_256_thread.sh $2 $4 "256_thread_2_$5"
sh Timing_Scripts/sniper/thread/run_256_thread.sh $3 $4 "256_thread_3_$5"