#include<iostream>
#include<vector>
#include"alg.hpp"
#include"utils.hpp"
#include"experiments.hpp"
#include<cstdio>
#include<cmath>
#include<chrono>
#include<algorithm>
#include<cassert>
#include<utility>

using namespace std;

vector<pair<double , double> > v;

bool sort_by_difference_to_ray(pair<double, double> a, pair<double, double > b) {
    if(a.second < 1e-9)
        return true;

    if(b.second < 1e-9)
        return false;

    return a.first / a.second > b.first / b.second;
}


bool sort_inverse_of_difference_to_ray(pair<double, double> a, pair<double, double > b) {
    if(a.second < 1e-9)
        return false;

    if(b.second < 1e-9)
        return true;

    return a.first / a.second < b.first / b.second;
}

bool sort_by_weight_div_profit(pair<double, double> a, pair<double, double > b) {
    if(a.first < 1e-9)
        return false;

    if(b.first < 1e-9)
        return true;

    return a.second / a.first < b.second / b.first;
}


bool sort_by_weight_div_profit_inverse(pair<double, double> a, pair<double, double > b) {
    if(a.first < 1e-9)
        return true;

    if(b.first < 1e-9)
        return false;

    return a.second / a.first > b.second / b.first;
}


bool sort_by_profit_asc(pair<double, double> a, pair<double, double > b) {
    return a.first < b.first;
}

bool sort_by_profit_desc(pair<double, double> a, pair<double, double > b) {
    return a.first > b.first;
}

bool sort_by_weight_asc(pair<double, double> a, pair<double, double > b) {
    return a.second < b.second;
}

bool sort_by_weight_desc(pair<double, double> a, pair<double, double > b) {
    return a.second > b.second;
}

double experiment(
        int n_items,
        int mode,
        int n_rounds,
        bool read_from_stdin,
        bool print_means,
        bool print_drops,
        int with_sort,
        bool print_total_generated,
        bool print_prob_dist) {

    double mean = 0.0;

    double mean_max_weight_diff = 0.0;
    double mean_max_profit_diff = 0.0;
    double mean_max_weight = 0.0;
    double mean_max_profit = 0.0;
    double mean_weight_diff = 0.0;

    if (n_rounds == 0)
        return .0;

    double t_core = 0.0;
    double t_nemhauser_ullman = 0.0;

    vector<double> counters(n_items, 0.0);

    cout << "Round with n="<< n_items << " items" << endl;
    vector<double> weights;
    vector<double> profits;
    vector<long long> range_cnt = vector<long long>(n_items, 0LL);

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

        v.clear(); 
        v = vector<pair<double, double> >(profits.size());
        for(int i =0 ;i < weights.size(); i++) {
            v[i].first = profits[i];
            v[i].second = weights[i];
        }
 
        switch(with_sort) {
            case 1:   
        //        cout << "Sort normal" << endl;
                sort(v.begin(), v.end(), sort_by_difference_to_ray);
                break;
            case 2:
        //        cout << "Sort inverse normal" << endl;
                sort(v.begin(), v.end(), sort_inverse_of_difference_to_ray);
                break;
            case 3:
          //      cout << "Sort by weight_asc" << endl;
                sort(v.begin(), v.end(), sort_by_weight_asc);
                break;
            case 4:
            //    cout << "Sort by weight_desc" << endl;
                sort(v.begin(), v.end(), sort_by_weight_desc);
                break;
            case 5:
              //  cout << "Sort by profit_asc" << endl;
                sort(v.begin(), v.end(), sort_by_profit_asc);
                break;
            case 6:
             //   cout << "Sort by profit_desc" << endl;
                sort(v.begin(), v.end(), sort_by_profit_desc);
                break;
            case 7:
//                cout << "Sort by w/p" << endl;
                sort(v.begin(), v.end(), sort_by_weight_div_profit);
                break;
            case 8:
//                cout << "Sort by w/p inverse" << endl;
                sort(v.begin(), v.end(), sort_by_weight_div_profit_inverse);
                break;
            default:
                break;

        }

        weights.clear();
        profits.clear();
        weights = vector<double>(v.size());
        profits = vector<double>(v.size());

        for(int i =0 ; i < v.size(); i++) {
            weights[i] = v[i].second;
            profits[i] = v[i].first;
        } 

        int last = weights.size() - 1;
        //double eps = 1e-2;
        //if(v.size()) {
        //    vector<double> deviation = generate_random_uniform_val(2, -eps, eps);
    	//    double ow = weights[last];
    	//    double op = profits[last];
        //    //weights[last] = max(0.0,min(1.0, weights[last] + deviation[0]));
        //    //profits[last] = max(0.0, min(1.0, profits[last] + deviation[1]));
        //}
        //            cout << v.size() << "\n";


        auto start = std::chrono::high_resolution_clock::now();
        vector<candidate> r = nemhauser_ullman(weights, profits, W, print_drops, print_total_generated);
        auto finish = std::chrono::high_resolution_clock::now(); 
        t_nemhauser_ullman += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        //r = nemhauser_ullman(weights, profits, W, false);

        //weights[last] = ow;
        //profits[last] = op;

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
        double local_weight_diff = 0.0;
        double avg_diff_weight = 0.0;


        for(int i=0 ; i + 1 < r.size() ; i++) {
            max_dist_profit = max(max_dist_profit, r[i+1].profit - r[i].profit);
            max_dist_weight = max(max_dist_weight, r[i+1].weight - r[i].weight);
            local_weight_diff += r[i+1].profit - r[i].profit;

            int idx = (int) ((r[i+1].weight - r[i].weight) * n_items);
            range_cnt[idx]++;
        }
        local_weight_diff /= (r.size() - 1);
        mean_weight_diff += local_weight_diff;

//        cout << max_dist_profit << "=max_dist_profit && " << max_dist_weight << "=max_dist_weight " << endl;
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
    mean_weight_diff /= (double) n_rounds;
    //avg_diff_weight /= (double) n_rounds;

    //t_core /= (double) n_rounds;
    t_nemhauser_ullman /= (double) n_rounds;

    //cout << "Time: \t" << t_nemhauser_ullman << "\t|\t" << t_core << endl;
    ////cout << "Time: \t" << t_core << endl;

    if(print_prob_dist) {
        cout << "Prob dist\n";
        for(int i =0 ; i < n_items; i++) {
            cout << range_cnt[i] << " ";
        }
    }

    //if(print_means) {
    //    cout <<"Means_for_N=" << n_items << " ";
    //    cout << "mean_max_weight_diff=" << mean_max_weight_diff << " ";
    //    cout << "mean_max_profit_diff=" << mean_max_profit_diff << " ";
    //    cout << "mean_max_weight=" << mean_max_weight << " ";
    //    cout << "mean_max_profit=" << mean_max_profit << " ";
    //    cout << "mean_weight_diff=" << mean_weight_diff << endl;
    //}
//    cout << "Counters:\n" << endl;
    
//    for(int i =0; i < counters.size();i++) {
//        cout << counters[i] / (double) n_rounds << " ";
//    }
//    cout << endl << endl;

    return mean;
}

void run_experiments(int mode, int n_rounds, int n_start, int n_experiments, bool read_from_stdin, bool print_means, bool print_drops, int with_sort, bool print_total_generated, bool print_prob_dist) {
        cout << "Sort mode: ";
        switch(with_sort) {
            case 1:   
                cout << "normal" << endl;
                break;
            case 2:
                cout << "inverse normal" << endl;
                break;
            case 3:
                cout << "by weight_asc" << endl;
                break;
            case 4:
                cout << "by weight_desc" << endl;
                break;
            case 5:
                cout << "by profit_asc" << endl;
                break;
            case 6:
                cout << "by profit_desc" << endl;
                break;
            case 7:
                cout << "by w/p" << endl;
                break;
            case 8:
                cout << "by w/p inverse" << endl;
                break;
            default:
                cout << "None" << endl;
                break;
        }



    if(n_start == 1)
        cout << "Starting experiments\nN\t|\tNumber of pareto optimal solutions\n";

    //cerr << "n-round " << n_rounds << endl;
    for(int i=n_start ; i < n_experiments + 1; i++) {
        double n_pareto_optimal_solutions = 
                    experiment(i, mode, n_rounds, read_from_stdin, print_means, print_drops, with_sort, print_total_generated, print_prob_dist);

        //cout << i << "\t|\t " << n_pareto_optimal_solutions << endl;
    }
}


double approx_experiment(
        int n_items,
        int mode,
        int n_rounds,
        int clusters,
        int type) {

    double mean = 0.0;

    double mean_max_weight_diff = 0.0;
    double mean_max_profit_diff = 0.0;
    double mean_max_weight = 0.0;
    double mean_max_profit = 0.0;
    double mean_weight_diff = 0.0;

    double mean_eps_diff = 0.0;

    if (n_rounds == 0)
        return .0;

    //cout << "Round with n="<< n_items << " items" << endl;
    vector<double> weights;
    vector<double> profits;
    for(int i = 0; i < n_rounds; i++) {

        double W;

        weights = generate_input(n_items, mode);
        profits = generate_input(n_items, mode);
        W = generate_random_uniform_val(1, 0, n_items)[0];

        if(type == 3) W = n_items;
        vector<candidate> r = nemhauser_ullman(weights, profits, W, 0, 0);
        double eps = (type == 1) ? 
                approximate_pareto_curve(r, min(clusters, (int)r.size())) : 
                optimal_pareto_curve(r, min(clusters, (int)r.size()));

        if(type == 3) {

            vector<candidate> greedy_sol;
            v = vector<pair<double, double> >(profits.size());
            for(int i =0 ;i < weights.size(); i++) {
                v[i].first = profits[i];
                v[i].second = weights[i];
            }

            sort(v.begin(), v.end(), sort_by_difference_to_ray);
            candidate c0;
            c0.weight = 0 ; c0.profit = 0;
            greedy_sol.push_back(c0);

            for(int i =0 ; i < v.size(); i++) {
                candidate ca;
                ca.weight = greedy_sol[greedy_sol.size() - 1].weight + v[i].second;
                ca.profit = greedy_sol[greedy_sol.size() - 1].profit + v[i].first;
                greedy_sol.push_back(ca);
            }

            double diff_eps = compute_epsilon_from(r, greedy_sol);
            assert(diff_eps >= 0);

            mean_eps_diff += diff_eps;

        }

        mean += eps;
        
    }

    mean /= (double) n_rounds; 
    mean_eps_diff /= (double) n_rounds;

    if (type == 3)
        cout << "Mean eps greedy = " << mean_eps_diff << endl;

    return mean;
}


void run_approx_experiments(int mode, int n_rounds, int n_start, int n_experiments, int type) {
    for(int i=n_start ; i < n_experiments + 1; i++) {
        cout << "Nitems =  " << i << endl;

        int be = 1 , end = 100;
        if (type == 3) 
            be = n_start+1, end = n_start + 2;

        for(int j = be ; j < end  ; j++) {
            double eps = 
                    approx_experiment(i, mode, n_rounds, j, type);
            cout << j << " clusters | eps = " << eps << endl;
            if(eps < 1e-6) break;
        }
    }
}


