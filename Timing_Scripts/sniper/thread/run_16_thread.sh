# Runs simulations for the given config for the 4 methods using 16 threads with the first and last methods in parallel
# Inputs:
#   - Matrix input file
#   - Sniper Config file
#   - Output directory name

rm -rf Sniper_Out/$3
mkdir Sniper_Out/$3
mkdir Sniper_Out/$3/CRSOMP
mkdir Sniper_Out/$3/MergeCRS
mkdir Sniper_Out/$3/CSB
mkdir Sniper_Out/$3/BlockCOH

../snipersim/run-sniper -c $2 -n 16 -d ./Sniper_Out/$3/CRSOMP/ -s markers:verbose:stats -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 2 16 &
../snipersim/run-sniper -c $2 -n 16 -d ./Sniper_Out/$3/MergeCRS/ -s markers:verbose:stats -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 8 16 &
../snipersim/run-sniper -c $2 -n 16 -d ./Sniper_Out/$3/CSB/ -s markers:verbose:stats -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 9 16 &
../snipersim/run-sniper -c $2 -n 16 -d ./Sniper_Out/$3/BlockCOH -s markers:verbose:stats -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 10 16
wait

cd Sniper_Out/$3/CRSOMP
${SNIPER}/tools/cpistack.py --partial="marker-1-2:marker-2-2"
${SNIPER}/tools/gen_simout.py --partial="marker-1-2:marker-2-2" > part_sim.out
cd ../../..

cd Sniper_Out/$3/MergeCRS
${SNIPER}/tools/cpistack.py --partial="marker-1-2:marker-2-2"
${SNIPER}/tools/gen_simout.py --partial="marker-1-2:marker-2-2" > part_sim.out
cd ../../..

cd Sniper_Out/$3/CSB
${SNIPER}/tools/cpistack.py --partial="marker-1-2:marker-2-2"
${SNIPER}/tools/gen_simout.py --partial="marker-1-2:marker-2-2" > part_sim.out
cd ../../..

cd Sniper_Out/$3/BlockCOH
${SNIPER}/tools/cpistack.py --partial="marker-1-2:marker-2-2"
${SNIPER}/tools/gen_simout.py --partial="marker-1-2:marker-2-2" > part_sim.out
cd ../../..