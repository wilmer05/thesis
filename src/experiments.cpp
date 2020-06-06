#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"

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

void run_experiments(int mode, int n_rounds, int n_experiments) {

    cout << "Starting experiments\nN\t|\tNumber of pareto optimal solutions\n";
    for(int i=1 ; i < n_experiments + 1; i++) {
        double n_pareto_optimal_solutions = 
                    experiment(i, mode, n_rounds);

        cout << i << "\t|\t " << n_pareto_optimal_solutions << endl;
    }
}

