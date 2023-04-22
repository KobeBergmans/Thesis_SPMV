# Runs simulations for the 6 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Matrix input file 4
#   - Matrix input file 5
#   - Matrix input file 6
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_32_thread.sh $1 $7 "32_thread_1_$8"
sh Timing_Scripts/sniper/thread/run_32_thread.sh $2 $7 "32_thread_2_$8"
sh Timing_Scripts/sniper/thread/run_32_thread.sh $3 $7 "32_thread_3_$8"
sh Timing_Scripts/sniper/thread/run_32_thread.sh $4 $7 "32_thread_4_$8"
sh Timing_Scripts/sniper/thread/run_32_thread.sh $5 $7 "32_thread_5_$8"
sh Timing_Scripts/sniper/thread/run_32_thread.sh $6 $7 "32_thread_6_$8"