#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"
#include<cstdio>
#include<cmath>
#include<chrono>

using namespace std;

double experiment(int n_items, int mode, int n_rounds) {
    double mean = 0.0;
    if (n_rounds == 0)
        return .0;

    double t_core = 0.0;
    double t_nemhauser_ullman = 0.0;

    vector<double> counters(n_items, 0.0);

    for(int i = 0; i < n_rounds; i++) {
        vector<double> weights = generate_input(n_items, mode);
        vector<double> profits = generate_input(n_items, mode);
        double W = generate_random_uniform_val(1, 0, n_items)[0];
    
        auto start = std::chrono::high_resolution_clock::now();
        vector<candidate> r = nemhauser_ullman(weights, profits, W);
        auto finish = std::chrono::high_resolution_clock::now(); 
        t_nemhauser_ullman += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        double j = 0;
        for(int i=0; i < r.size(); i++) {
            while(r[i].profit >= ((double)j + 1)) j++;
            assert(j < counters.size());
            counters[j]++;
        }

        //start = std::chrono::high_resolution_clock::now();
        //double core_sol = core_algorithm(weights, profits, W);
        //finish = std::chrono::high_resolution_clock::now(); 
        //auto finish = std::chrono::high_resolution_clock::now(); 
        //t_core += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        //assert((!r.size() && core_sol == 0.0)|| fabs(r[r.size() - 1].profit) - core_sol < 1e-8);

        mean += (double) r.size();
    }

    //cout << "Solutions:\n" << endl;
    /* for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }*/

    mean /= (double) n_rounds; 
    //t_core /= (double) n_rounds;
    t_nemhauser_ullman /= (double) n_rounds;
    //cout << "Time: \t" << t_nemhauser_ullman << "\t|\t" << t_core << endl;
    //cout << "Time: \t" << t_core << endl;

//    cout << "Counters:\n" << endl;
    
//    for(int i =0; i < counters.size();i++) {
//        cout << counters[i] / (double) n_rounds << " ";
//    }
//    cout << endl << endl;

    return mean;
}

void run_experiments(int mode, int n_rounds, int n_start, int n_experiments) {

    if(n_start == 1)
        cout << "Starting experiments\nN\t|\tNumber of pareto optimal solutions\n";

    for(int i=n_start ; i < n_experiments + 1; i++) {
        double n_pareto_optimal_solutions = 
                    experiment(i, mode, n_rounds);

        //cout << i << "\t|\t " << n_pareto_optimal_solutions << endl;
    }
}

