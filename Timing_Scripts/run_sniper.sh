rm -f driver_sniper
make driver_sniper

rm -rf Sniper_Out/$4
mkdir Sniper_Out/$4
mkdir Sniper_Out/$4/CRSOMP
mkdir Sniper_Out/$4/BlockCOH
mkdir Sniper_Out/$4/CSB
mkdir Sniper_Out/$4/MergeCRS

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/CRSOMP/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 2 $2
cd Sniper_Out/CRSOMP
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/BlockCOH/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 8 $2
cd Sniper_Out/BlockCOH
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/CSB/ -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 9 $2
cd Sniper_Out/CSB
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/$4/MergeCRS -s markers:verbose:stats -s roi-iter::3:3 --roi-script --no-cache-warming -- ./driver_sniper $1 10 $2
cd Sniper_Out/MergeCRS
${SNIPER}/tools/cpistack.py --partial="marker-1-3:marker-2-3"
${SNIPER}/tools/gen_simout.py --partial="marker-1-3:marker-2-3" > part_sim.out
cd ../..