# Runs simulations for the 4 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Matrix input file 4
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_16_thread.sh $1 $5 "16_thread_1_$6" &
sh Timing_Scripts/sniper/thread/run_16_thread.sh $2 $5 "16_thread_2_$6"
wait

sh Timing_Scripts/sniper/thread/run_16_thread.sh $3 $5 "16_thread_3_$6" &
sh Timing_Scripts/sniper/thread/run_16_thread.sh $4 $5 "16_thread_4_$6"