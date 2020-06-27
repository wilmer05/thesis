#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<cstdio>
#include"utils.hpp"
#include"alg.hpp"


using namespace std;

double item::dantzig_slope = .0;

/* Nemhauser Ullman algorithm that looks for the pareto optimal solutions
 * of a knapsack problem till some maximum weight
 * */

vector<candidate> nemhauser_ullman(const vector<double> &weights, const vector<double> &profits, double W) {
    vector<candidate> p;
    p.push_back(candidate(0,0));
    
    int n = weights.size();
    for(int i=0; i<n; i++) {
        int sz = p.size();
        vector<candidate> q(sz);
        int last = 0;
        for(int j = 0 ; j < sz; j++ ) {
            if (p[j].weight + weights[i] <= W) 
                q[last++] = candidate(p[j].weight + weights[i], p[j].profit + profits[i]);
        }
        q.resize(last);

        int k = 0, cnt_p = 0, cnt_q = 0;
        vector<candidate> tmp(sz << 1);
        
        while( cnt_p < p.size() && cnt_q < q.size()) {
            if(p[cnt_p].dominates(q[cnt_q])) {
                cnt_q++;
                continue;
            }

            if(q[cnt_q].dominates(p[cnt_p])) {
                cnt_p++;
                continue;
            }
            
            if(p[cnt_p].profit < q[cnt_q].profit) {
                tmp[k++] = p[cnt_p++];
            } else {
                tmp[k++] = q[cnt_q++];
            }
        }
        for(;cnt_p < p.size(); cnt_p++)
            if(!k || (k >0 && !tmp[k-1].dominates(p[cnt_p])))
                tmp[k++] = p[cnt_p];

        for(;cnt_q < q.size(); cnt_q++)
            if(!k || (k > 0 && !tmp[k-1].dominates(q[cnt_q]))) 
                tmp[k++] = q[cnt_q];

        tmp.resize(k);
        p = tmp; 
    }

    assert(!p.size() || p[p.size() - 1].weight <= W);
    return p;
}



/* Core Algorithm to solve knapsack problem with capacity W
 *
 * */

double get_loss(const item &a) {
    return fabs(a.profit - item::dantzig_slope * a.weight);
}

bool smaller_loss(const item &a, const item &b) {
    return get_loss(b) > get_loss(a);
}

double get_mask_profit(const vector<item> &core, int mask) {
    double total_profit = 0.0;
    for(int i =0 ; i < MAX_BRUTE_FORCE_CORE_SIZE; i++) 
        if(mask & (1 << i)) total_profit += core[i].profit;
    
    return total_profit;
}


double get_mask_weight(const vector<item> &core, int mask) {
    double total_weight = 0.0;
    for(int i =0 ; i < MAX_BRUTE_FORCE_CORE_SIZE; i++) 
        if(mask & (1 << i)) total_weight += core[i].weight;
    
    return total_weight;
}


double brute_force(const vector<item> &core, double W) {
    assert(core.size() <= MAX_BRUTE_FORCE_CORE_SIZE);

    double best_sol = 0.0;

    for(int mask=0 ;mask < (1 << ((int)core.size())); mask++)
        if(get_mask_weight(core, mask) <= W)
            best_sol = max(best_sol, get_mask_profit(core, mask)); 

    return best_sol;
}

double get_integral_solution(const vector<item> &core, double W) {
    if(core.size() <= MAX_BRUTE_FORCE_CORE_SIZE) 
        return brute_force(core, W);
    else {
        vector<double> ws,ps;
        for(int i =0;i < core.size(); i++) {
            ws.push_back(core[i].weight);
            ps.push_back(core[i].profit);
        }
        vector<candidate> pos = nemhauser_ullman(ws ,ps, W);
        if(pos.size()) return pos[pos.size() - 1].profit;
        return 0.0;
    }
}

double core_algorithm(const vector<double> &weights, const vector<double> &profits, double W) {
    vector<item> items(weights.size());

    for(int i=0; i<weights.size(); i++) 
        items[i].weight = weights[i], items[i].profit = profits[i];
    
    sort(items.begin(), items.end()); 

    int break_item = 0;
    double fractional_solution = 0.0;
    double integral_solution_without_core = 0.0;
    while(break_item < items.size() && W >= items[break_item].weight) {
        fractional_solution += items[break_item].profit;
        integral_solution_without_core += items[break_item].profit;
        W -= items[break_item].weight;
        items[break_item].belongs_to_fractional_solution = true;
        break_item++;
    }

    if(break_item >= items.size()) return fractional_solution;
    fractional_solution += (W * items[break_item].profit)/ items[break_item].weight;

    items[break_item].is_ray_item = true;
    item::dantzig_slope = items[break_item].profit / items[break_item].weight;

    sort(items.begin(), items.end(), smaller_loss);
    for(int i =0 ; i< items.size() -1; i ++) assert(get_loss(items[i]) <= get_loss(items[i+1]));
    assert(items[0].is_ray_item);

    double gamma = 0;
    double integral_solution = 0.0;
    int last_core_item = 0;

    vector<item> core;

    do{ 
        if(last_core_item < items.size()) {
            core.push_back(items[last_core_item]);
            gamma = get_loss(items[last_core_item]);
            if(items[last_core_item].belongs_to_fractional_solution) {
                integral_solution_without_core -= items[last_core_item].profit;
                W += items[last_core_item].weight;
            }
        }

        double core_solution = get_integral_solution(core, W);
        integral_solution = core_solution + integral_solution_without_core;
        last_core_item++; 
    } while(fractional_solution - integral_solution > gamma && last_core_item < items.size());

    assert(fractional_solution >= integral_solution);
    return integral_solution;
}
