#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"
#include<cstdio>
#include<cmath>

using namespace std;

double experiment(int n_items, int mode, int n_rounds) {
    double mean = 0.0;
    if (n_rounds == 0)
        return .0;

    for(int i = 0; i < n_rounds; i++) {
        vector<double> weights = generate_input(n_items, mode);
        vector<double> profits = generate_input(n_items, mode);
        double W = generate_random_uniform_val(1, 0, n_items)[0];
        vector<candidate> r = nemhauser_ullman(weights, profits, W);

        double core_sol = core_algorithm(weights, profits, W);

        assert((!r.size() && core_sol == 0.0)|| fabs(r[r.size() - 1].profit) - core_sol < 1e-6);

        mean += (double) r.size();
    }

    //cout << "Solutions:\n" << endl;
    /* for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }*/

    mean /= (double) n_rounds; 

    return mean;
}

void run_experiments(int mode, int n_rounds, int n_start, int n_experiments) {

    if(n_start == 1)
        cout << "Starting experiments\nN\t|\tNumber of pareto optimal solutions\n";

    for(int i=n_start ; i < n_experiments + 1; i++) {
        double n_pareto_optimal_solutions = 
                    experiment(i, mode, n_rounds);

        cout << i << "\t|\t " << n_pareto_optimal_solutions << endl;
    }
}

