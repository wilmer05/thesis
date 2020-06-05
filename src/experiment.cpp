#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiment.hpp"

using namespace std;

double experiment(int n_items, int mode, int n_rounds) {
    double mean = 0.0;
    if (n_rounds == 0)
        return .0;


    for(int i = 0; i < n_rounds; i++) {
        vector<double> weights = generate_input(n_items, mode);
        vector<double> profits = generate_input(n_items, mode);
        vector<candidate> r = nemhauser_ullman(weights, profits);

        mean += (double) r.size();
    }

    //cout << "Solutions:\n" << endl;
    /* for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }*/

    mean /= (double) n_rounds; 

    return mean;
}
