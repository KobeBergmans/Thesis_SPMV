rm -f driver_sniper
make driver_sniper

rm -rf Sniper_Out
mkdir Sniper_Out
mkdir Sniper_Out/CRSOMP
mkdir Sniper_Out/BlockCOH
mkdir Sniper_Out/CSB
mkdir Sniper_Out/MergeCRS

../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/CRSOMP/ -s markers -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 2 $2
../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/BlockCOH/ -s markers -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 8 $2
../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/CSB/ -s markers -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 9 $2
../snipersim/run-sniper -c $3 -n $2 -d ./Sniper_Out/MergeCRS -s markers -s roi-iter::2:2 --roi-script --no-cache-warming -- ./driver_sniper $1 10 $2