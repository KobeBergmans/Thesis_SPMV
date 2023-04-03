# Runs simulations for the given config for the 4 methods using a given amount of threads
# Inputs:
#   - Matrix input file
#   - Amount of threads used
#   - Sniper config file
#   - Output directory name

rm -f driver_sniper
make driver_sniper

rm -rf Sniper_Out/$4
mkdir Sniper_Out/$4
mkdir Sniper_Out/$4/CRSOMP
mkdir Sniper_Out/$4/MergeCRS
mkdir Sniper_Out/$4/CSB
mkdir Sniper_Out/$4/BlockCOH

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/CRSOMP/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 2 $2
cd Sniper_Out/$4/CRSOMP
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/MergeCRS/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 8 $2
cd Sniper_Out/$4/MergeCRS
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/CSB/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 9 $2
cd Sniper_Out/$4/CSB
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/BlockCOH -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 10 $2
cd Sniper_Out/$4/BlockCOH
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../../..