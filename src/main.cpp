#include<iostream>
#include<vector>
#include<stdlib.h>
#include"experiments.hpp"
#include<cstring>

using namespace std;


int main(int argc, char* argv[]) {

    if(argc < 8) {
        cout << "Usage: \n\t./run <mode> <n_rounds> <n_start> <n_experiments> <read_from_stdin_flag> <print_means> <print_drops> [--sort, --inverse-sort, --sort-by-weight-asc, --sort-by-weight-desc, --sort-by-profit-asc, --sort-by-profit-desc, --print-total-generated, --approx-pareto-experiment, --optimal-approx-experiment, --print-prob-dist, --compare-approx-experiment ]\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int with_sort = 0;
    bool print_total_generated = false;
    int approx_experiment = 0;

    bool print_prob_distr = false;
    for(int i = 8 ; i < argc; i++) {
        if(!strcmp(argv[i], "--sort")) {
            with_sort = 1;
        }

        if(!strcmp(argv[i], "--inverse-sort")) {
            with_sort = 2;
        }

        if(!strcmp(argv[i], "--sort-by-weight-asc")) {
            with_sort = 3;
        }

        if(!strcmp(argv[i], "--sort-by-weight-desc")) {
            with_sort = 4;
        }

        if(!strcmp(argv[i], "--sort-by-profit-asc")) {
            with_sort = 5;
        }

        if(!strcmp(argv[i], "--sort-by-profit-desc")) {
            with_sort = 6;
        }

        if(!strcmp(argv[i], "--sort-by-w-div-p")) {
            with_sort = 7;
        }

        if(!strcmp(argv[i], "--sort-by-w-div-p-inverse")) {
            with_sort = 8;
        }

        if(!strcmp(argv[i], "--print-total-generated")) {
            print_total_generated = true;
        }
        
        
        if(!strcmp(argv[i], "--approx-pareto-experiment")) {
            approx_experiment = 1;
        }

        if(!strcmp(argv[i], "--optimal-approx-experiment")) {
            approx_experiment = 2;
        }

        if(!strcmp(argv[i], "--compare-approx-experiment")) {
            approx_experiment = 3;
        }

        if(!strcmp(argv[i], "--print-prob-dist")) {
            print_prob_distr = true;
        }

    } 

    int mode = atoi(argv[1]);
    int n_rounds = atoi(argv[2]);
    int n_start = atoi(argv[3]);
    int n_experiments = atoi(argv[4]);
    string read_from_stdin(argv[5]);
    string print_means(argv[6]);
    string print_drops(argv[7]);

    if(approx_experiment) {
        run_approx_experiments(mode, n_rounds, n_start, n_experiments, approx_experiment);
    } else {
        run_experiments(mode, n_rounds, n_start, n_experiments, read_from_stdin == "1",  print_means == "1", print_drops=="1", with_sort, print_total_generated, print_prob_distr);
    }
    return 0;
}
