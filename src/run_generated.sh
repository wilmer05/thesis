#! /bin/bash
./run 1 $3 $1 $2 0 0 0 --sort-by-w-div-p-inverse --print-total-generated > ../experiments/sort_experiment_sort_by_w_div_p_inverse_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --sort-by-w-div-p --print-total-generated > ../experiments/sort_experiment_sort_by_w_div_p_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --sort-by-profit-desc --print-total-generated > ../experiments/sort_experiment_sort_by_profit_desc_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --sort-by-profit-asc --print-total-generated > ../experiments/sort_experiment_sort_by_profit_asc_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --sort-by-weight-desc --print-total-generated > ../experiments/sort_experiment_sort_by-weight_desc_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --sort-by-weight-asc --print-total-generated > ../experiments/sort_experiment_sort_by-weight_asc_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --inverse-sort --print-total-generated > ../experiments/sort_experiment_sort_inverse_$1_$2_generated &
./run 1 $3 $1 $2 0 0 0 --print-total-generated > ../experiments/sort_experiment_sort_none_$1_$2_generated &
