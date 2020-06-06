#include<iostream>
#include<vector>
#include<stdlib.h>
#include"experiments.hpp"

using namespace std;


int main(int argc, char* argv[]) {

    if(argc < 4) {
        cout << "Usage: \n\t./run <mode> <n_rounds> <n_experiments>\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int mode = atoi(argv[1]);
    int n_rounds = atoi(argv[2]);
    int n_experiments = atoi(argv[3]);
    run_experiments(mode, n_rounds, n_experiments);
    return 0;
}
