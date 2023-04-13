# Runs simulations for the 7 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Matrix input file 3
#   - Matrix input file 4
#   - Matrix input file 5
#   - Matrix input file 6
#   - Matrix input file 7
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/run_8_thread.sh $1 $8 "8_thread_1_$9" &
sh Timing_Scripts/sniper/run_8_thread.sh $2 $8 "8_thread_2_$9"
wait

sh Timing_Scripts/sniper/run_8_thread.sh $3 $8 "8_thread_3_$9" &
sh Timing_Scripts/sniper/run_8_thread.sh $4 $8 "8_thread_4_$9"
wait

sh Timing_Scripts/sniper/run_8_thread.sh $5 $8 "8_thread_5_$9" &
sh Timing_Scripts/sniper/run_8_thread.sh $6 $8 "8_thread_6_$9"
wait

sh Timing_Scripts/sniper/run_8_thread.sh $7 $8 "8_thread_7_$9"