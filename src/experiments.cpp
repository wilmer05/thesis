#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"
#include<cstdio>

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

        printf("NU Sol=%.20lf and Core Sol = %.20lf\n", r.size() ? r[r.size() - 1].profit : 0, core_sol);
        fflush(stdout);
        ///printf("Core Sol = %.6lf\n", core_sol);

        assert((!r.size() && core_sol == 0.0)|| core_sol == r[r.size() - 1].profit);

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

