#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"
#include<cstdio>
#include<cmath>
#include<chrono>
#include<algorithm>

using namespace std;

double experiment(
        int n_items,
        int mode,
        int n_rounds,
        bool read_from_stdin) {
    double mean = 0.0;

    double mean_max_weight_diff = 0.0;
    double mean_max_profit_diff = 0.0;
    double mean_max_weight = 0.0;
    double mean_max_profit = 0.0;

    if (n_rounds == 0)
        return .0;

    double t_core = 0.0;
    double t_nemhauser_ullman = 0.0;

    vector<double> counters(n_items, 0.0);

    vector<double> weights;
    vector<double> profits;
    for(int i = 0; i < n_rounds; i++) {

        double W;

        if (!read_from_stdin) {
            weights = generate_input(n_items, mode);
            profits = generate_input(n_items, mode);
            W = generate_random_uniform_val(1, 0, n_items)[0];
        } else if(!i){
            double wi, pi;
            cin >> W;
            //cout << W << endl;
            //cerr << W << endl << endl;
            while(cin >> wi >> pi) {
                weights.push_back(wi);
                profits.push_back(pi);
            //cerr << wi << " " << pi << endl;
            
            }
            //cerr << endl;

        }
    

        int last = weights.size() - 1;
        double eps = 1e-2;
        vector<double> deviation = generate_random_uniform_val(2, -eps, eps);
	double ow = weights[last];
	double op = profits[last];

        weights[last] = max(0.0,min(1.0, weights[last] + deviation[0]));
        profits[last] = max(0.0, min(1.0, profits[last] + deviation[1]));

        auto start = std::chrono::high_resolution_clock::now();
        vector<candidate> r = nemhauser_ullman(weights, profits, W);
        auto finish = std::chrono::high_resolution_clock::now(); 
        t_nemhauser_ullman += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();


        weights[last] = ow;
        profits[last] = op;

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
        double max_dist_profit = 0.0;
        double max_dist_weight = 0.0;
        double cnt = r.size();
        mean_max_weight += r[r.size() - 1].weight;
        mean_max_profit += r[r.size() - 1].profit;
        for(int i=0 ; i + 1 < r.size() ; i++) {
            max_dist_profit = max(max_dist_profit, r[i+1].profit - r[i].profit);
            max_dist_weight = max(max_dist_weight, r[i+1].weight - r[i].weight);
        }

        cout << max_dist_profit << "=max_dist_profit && " << max_dist_weight << "=max_dist_weight " << endl;
        mean_max_weight_diff += max_dist_weight;
        mean_max_profit_diff += max_dist_profit;
    }

    //cout << "Solutions:\n" << endl;
    /* for(int i =0 ; i < r.size(); i++) {
        cout << "\t" << r[i].weight << " " << r[i].profit << endl;
    }*/

    mean /= (double) n_rounds; 
    mean_max_weight_diff /= (double) n_rounds;
    mean_max_profit_diff /= (double) n_rounds;
    mean_max_weight /= (double) n_rounds;
    mean_max_profit /= (double) n_rounds;

    //t_core /= (double) n_rounds;
    t_nemhauser_ullman /= (double) n_rounds;
    //cout << "Time: \t" << t_nemhauser_ullman << "\t|\t" << t_core << endl;
    //cout << "Time: \t" << t_core << endl;

    cout << "mean of max_weight diff = " << mean_max_weight_diff << endl;
    cout << "mean of max_profit diff = " << mean_max_profit_diff << endl;
    cout << "mean of max_weight = " << mean_max_weight << endl;
    cout << "mean of max_profit = " << mean_max_profit << endl;
//    cout << "Counters:\n" << endl;
    
//    for(int i =0; i < counters.size();i++) {
//        cout << counters[i] / (double) n_rounds << " ";
//    }
//    cout << endl << endl;

    return mean;
}

void run_experiments(int mode, int n_rounds, int n_start, int n_experiments, bool read_from_stdin) {

    if(n_start == 1)
        cout << "Starting experiments\nN\t|\tNumber of pareto optimal solutions\n";

    //cerr << "n-round " << n_rounds << endl;
    for(int i=n_start ; i < n_experiments + 1; i++) {
        double n_pareto_optimal_solutions = 
                    experiment(i, mode, n_rounds, read_from_stdin);

        //cout << i << "\t|\t " << n_pareto_optimal_solutions << endl;
    }
}

