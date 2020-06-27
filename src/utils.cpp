#include<random>
#include<vector>
#include<cmath>
#include"utils.hpp"

using namespace std;

vector<double> generate_random_uniform_val(int n, double min, double max) {
    random_device rd;
    mt19937 gen(rd());
    default_random_engine generator;
    uniform_real_distribution<double> distribution(min,max);

    vector<double> ret(n);

    for(int i=0; i < n; i++)  {
        ret[i] = floor(SIGNIFICANT_PART * distribution(gen))/SIGNIFICANT_PART;
    }

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

