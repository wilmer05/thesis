#! /bin/bash
./run 1 $3 $1 $2 0 0 0 --sort-by-w-div-p-inverse > ../experiments/sort_experiment_sort_by_w_div_p_inverse_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --sort-by-w-div-p > ../experiments/sort_experiment_sort_by_w_div_p_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --sort-by-profit-desc > ../experiments/sort_experiment_sort_by_profit_desc_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --sort-by-profit-asc > ../experiments/sort_experiment_sort_by_profit_asc_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --sort-by-weight-desc > ../experiments/sort_experiment_sort_by-weight_desc_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --sort-by-weight-asc > ../experiments/sort_experiment_sort_by-weight_asc_$1_$2 &
./run 1 $3 $1 $2 0 0 0 --inverse-sort > ../experiments/sort_experiment_sort_inverse_$1_$2 &
./run 1 $3 $1 $2 0 0 0 > ../experiments/sort_experiment_sort_none_$1_$2 &
