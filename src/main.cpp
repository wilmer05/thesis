#include<iostream>
#include<vector>
#include<stdlib.h>
#include"experiments.hpp"

using namespace std;


int main(int argc, char* argv[]) {

    if(argc < 6) {
        cout << "Usage: \n\t./run <mode> <n_rounds> <n_start> <n_experiments> <read_from_stdin_flag>\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int mode = atoi(argv[1]);
    int n_rounds = atoi(argv[2]);
    int n_start = atoi(argv[3]);
    int n_experiments = atoi(argv[4]);
    string read_from_stdin(argv[5]);
    run_experiments(mode, n_rounds, n_start, n_experiments, read_from_stdin == "1");
    return 0;
}
