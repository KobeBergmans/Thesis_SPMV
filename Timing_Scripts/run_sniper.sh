rm -f driver_sniper
make driver_sniper

rm -rf Sniper_Out
mkdir Sniper_Out
mkdir Sniper_Out/CRSOMP
mkdir Sniper_Out/BlockCOH
mkdir Sniper_Out/CSB
mkdir Sniper_Out/MergeCRS

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/CRSOMP/ -s markers:verbose:stats -s roi-iter::2:3 --roi-script --no-cache-warming -- ./driver_sniper $1 2 $2
cd Sniper_Out/CRSOMP
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/BlockCOH/ -s markers:verbose:stats -s roi-iter::2:3 --roi-script --no-cache-warming -- ./driver_sniper $1 8 $2
cd Sniper_Out/BlockCOH
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/CSB/ -s markers:verbose:stats -s roi-iter::2:3 --roi-script --no-cache-warming -- ./driver_sniper $1 9 $2
cd Sniper_Out/CSB
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/MergeCRS -s markers:verbose:stats -s roi-iter::2:3 --roi-script --no-cache-warming -- ./driver_sniper $1 10 $2
cd Sniper_Out/MergeCRS
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..