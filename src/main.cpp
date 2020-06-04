#include<iostream>
#include<vector>
#include<stdlib.h>
#include"experiment.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    if(argc < 3) {
        cout << "Usage: \n\t./run <n_inputs> <mode>\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int mode = atoi(argv[2]);

    experiment(n, mode, 1);
    return 0;
}
