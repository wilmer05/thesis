#include<iostream>
#include<vector>
#include<stdlib.h>
#include"experiments.hpp"
#include<cstring>

using namespace std;


int main(int argc, char* argv[]) {

    if(argc < 8) {
        cout << "Usage: \n\t./run <mode> <n_rounds> <n_start> <n_experiments> <read_from_stdin_flag> <print_means> <print_drops> [--sort, --inverse-sort, --sort-by-weight-asc, --sort-by-weight-desc, --sort-by-profit-asc, --sort-by-profit-desc]\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int with_sort = 0;
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
    } 

    int mode = atoi(argv[1]);
    int n_rounds = atoi(argv[2]);
    int n_start = atoi(argv[3]);
    int n_experiments = atoi(argv[4]);
    string read_from_stdin(argv[5]);
    string print_means(argv[6]);
    string print_drops(argv[7]);
    run_experiments(mode, n_rounds, n_start, n_experiments, read_from_stdin == "1",  print_means == "1", print_drops=="1", with_sort);
    return 0;
}
