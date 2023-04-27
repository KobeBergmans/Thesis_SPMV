# Runs simulations for the 4 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Matrix input file 2
#   - Sniper config file
#   - Extra suffix to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/thread/run_16_thread.sh $1 $3 "16_thread_1_$4" &
sh Timing_Scripts/sniper/thread/run_16_thread.sh $2 $3 "16_thread_2_$4"
wait