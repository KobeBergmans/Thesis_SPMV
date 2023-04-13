# Runs simulations for the 4 given matrices with a given config
# Inputs:
#   - Matrix input file 1
#   - Sniper config file 1
#   - Sniper config file 2
#   - Extra suffix for config 1 to folder names to have more simulations than 1 run
#   - Extra suffix for config 2 to folder names to have more simulations than 1 run

rm -rf driver_sniper
make driver_sniper

sh Timing_Scripts/sniper/run_8_thread.sh $1 $2 "8_thread_1_$4" &
sh Timing_Scripts/sniper/run_8_thread.sh $1 $3 "8_thread_1_$5"
wait