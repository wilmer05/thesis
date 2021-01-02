#! /bin/bash
./run 1 $1 30 30 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_30 &
./run 1 $1 50 50 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_50 &
./run 1 $1 100 100 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_100 &
./run 1 $1 200 200 0 0 0 --approx-pareto-experiment > ../experiments/approximated_curve_N_200 &
