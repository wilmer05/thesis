#include<iostream>
#include<vector>
#include<stdlib.h>
#include<random>
#include"alg.hpp"
using namespace std;

vector<double> generate_random_uniform_val(int n, double min, double max) {
    random_device rd;
    mt19937 gen(rd());
    default_random_engine generator;
    uniform_real_distribution<double> distribution(min,max);

    vector<double> ret(n);

    for(int i=0; i < n; i++) 
        ret[i] = distribution(gen);

    return ret;
}

vector<double> generate_input(int n, int mode) {
    vector<double> ret;

    if(mode == 1) {
        ret = generate_random_uniform_val(n, 0.0, 1.);
    } else if(mode == 2) {
        ret = generate_random_uniform_val(n, -1., 1.);
    }
    return ret;
} 

int main(int argc, char* argv[]) {

    if(argc < 3) {
        cout << "Usage: \n\t./run <n_inputs> <mode>\n\n\t" << 
                "modes\n\t\t1 : uniform distribution in [0,1]" <<
                "\n\t\t2 : uniform distribution in [-1,1]" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int mode = atoi(argv[2]);
    vector<double> weights = generate_input(n, mode);
    vector<double> profits = generate_input(n, mode);
    vector<candidate> r = nemhauser_ullman(weights, profits);
    cout << "Solutions:\n" << endl;
    for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }
    return 0;
}
