#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiment.hpp"

using namespace std;

double experiment(int n_items, int mode, int n_experiments) {
    double mean = 0.0;


    vector<double> weights = generate_input(n_items, mode);
    vector<double> profits = generate_input(n_items, mode);
    vector<candidate> r = nemhauser_ullman(weights, profits);

    cout << "Solutions:\n" << endl;
    for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }

    return mean;
}
