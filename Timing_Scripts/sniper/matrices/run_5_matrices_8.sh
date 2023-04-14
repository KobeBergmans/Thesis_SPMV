# Runs simulations for the 5 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Matrix input file 4
#   - Matrix input file 5
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_8_thread.sh $1 $6 "8_thread_1_$7" &
sh Timing_Scripts/sniper/thread/run_8_thread.sh $2 $6 "8_thread_2_$7"
wait

sh Timing_Scripts/sniper/thread/run_8_thread.sh $3 $6 "8_thread_3_$7" &
sh Timing_Scripts/sniper/thread/run_8_thread.sh $4 $6 "8_thread_4_$7"
wait

sh Timing_Scripts/sniper/thread/run_8_thread.sh $5 $6 "8_thread_5_$7"