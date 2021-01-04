#! /bin/bash
#./run 1 $1 300 300 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_300 &
#./run 1 $1 500 500 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_500 &
#./run 1 $1 1000 1000 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_1000 &
#./run 1 $1 2000 2000 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_2000 &

./run 1 $1 30 30 0 0 0 --optimal-approx-experiment > ../experiments/optimal_curve_N_30 &
./run 1 $1 50 50 0 0 0 --optimal-approx-experiment > ../experiments/optimal_curve_N_50 &
./run 1 $1 75 75 0 0 0 --optimal-approx-experiment > ../experiments/optimal_curve_N_75 &
./run 1 $1 100 100 0 0 0 --optimal-approx-experiment > ../experiments/optimal_curve_N_100 &
 

