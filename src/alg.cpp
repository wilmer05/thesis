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

void make_ticks(vector<candidate> &v) {
	for(int i =0; i< v.size(); i++)
		v[i].tick();
}

vector<candidate> nemhauser_ullman(const vector<double> &weights, const vector<double> &profits, double W, bool print_drops, bool print_total_generated) {
    vector<candidate> p;
    p.push_back(candidate(0,0));
    
    int n = weights.size();
    int drops = 0;
    int drop_count = 0;
    int total_generated = 1;
    int total_generated_all_included = 1;

    for(int i=0; i<n; i++) {
        int sz = p.size();
        total_generated_all_included += sz;
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
                total_generated++;
            }
        }
        for(;cnt_p < p.size(); cnt_p++)
            if(!k || (k >0 && !tmp[k-1].dominates(p[cnt_p])))
                tmp[k++] = p[cnt_p];

        for(;cnt_q < q.size(); cnt_q++)
            if(!k || (k > 0 && !tmp[k-1].dominates(q[cnt_q]))) {
                tmp[k++] = q[cnt_q];
                total_generated++;
            }

        tmp.resize(k);
        p = tmp; 
    
        drops += min(0, k - sz); 
        
        //cout << k << endl;
        if( k - sz < 0 ) {
        //    cout << "Drop found: " << k - sz  << "... #POS before: " << sz << " and #POS after " << k << endl;
        //    cout << W << endl;
        //    for(int j = 0 ; j <= i; j++) {
        //        cout << weights[j] << " " << profits[j] << endl;
        //        cout << endl;
        //    }
        //    break;
            drop_count ++;
        }

		//make_ticks(p);
        //cout << k - sz << " ";
    }

    //cout << endl;
    //cout << "bla" << endl;
    if(print_drops) {
        cout << "Total drops = " << drops << " Total sols=" << p.size()<< " Drop count=" << drop_count << endl;
    }

    if(print_total_generated) {
        cout << "Total generated: " << total_generated << ", Total gen with all included " << total_generated_all_included << endl; 
    }

    assert(!p.size() || p[p.size() - 1].weight <= W);
	//cout << "Alive results: ";
	//for(int i = 0 ; i < p.size(); i++)
	//	cout << p[i].n_iterations_alive << " ";
	//cout << endl;
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
        vector<candidate> pos = nemhauser_ullman(ws ,ps, W, 0, 0);
        if(pos.size()) return pos[pos.size() - 1].profit;
        return 0.0;
    }
}

double core_algorithm(const vector<double> &weights, const vector<double> &profits, double W) {
    vector<item> items(weights.size());

    for(int i=0; i<weights.size(); i++) {
        items[i].weight = weights[i], items[i].profit = profits[i];
        items[i].belongs_to_fractional_solution = items[i].is_ray_item = false;
    }
    
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

double compute_epsilon(candidate &a, candidate &b) {

    double wa = a.weight;
    double ca = a.profit;
    double wb = b.weight;
    double cb = b.profit;

    if(wb < 1e-9) return 1e20; 

    return max(1 - ca / cb, wa / wb - 1);
}

//vector<pair<double, pair<int, int> > > tmp;
vector<bool> in_apprx_curve;
vector<int> current_sol ;
double approximate_pareto_curve(vector<candidate> &cs, int k) {
    int sz = cs.size(); 
    in_apprx_curve.resize(sz);
    current_sol.resize(k);

    for(int i =0 ; i < sz; i ++) {
        in_apprx_curve[i] = false;
    }

    for(int i=0 ; i< k; i ++) current_sol[i] = -1;
    current_sol[0] = 0;

    in_apprx_curve[0] = true;

    double ans = 1e12;

    for(int i =0 ; i < k; i++) {
        int worst_idx = -1;
        double worst_eps = 0.0;

        for(int j =0 ; j < sz; j++) {
            if(in_apprx_curve[j]) continue;
            
            double current_eps = 1e22;
            for(int idx = 0;idx < current_sol.size() && current_sol[idx] >= 0; idx++) {
                int center_idx = current_sol[idx];
                current_eps = min(current_eps, compute_epsilon(cs[center_idx], cs[j]));
            }

            if(current_eps > worst_eps || worst_idx == -1) {
                worst_idx = j;
                worst_eps = current_eps;
            }
        }

        if(i == k - 1) {
            ans = worst_eps;
            break;
        }

        current_sol[i+1] = worst_idx;
        in_apprx_curve[worst_idx] = true;
    }
    return ans;
}

bool exists_set_with_k(vector<candidate> &cs, int k, double eps) {
    k--;
    int last_sol = 0;
    int sz = cs.size();

    while(k > 0 && last_sol < sz - 1) {
        for(int i = last_sol + 1; i <= sz ; i++) {
           double current_eps = 0;

           for(int j = last_sol + 1; j < i ;  j++) {

                double new_eps = 1e20 ;

                if(i < sz)
                    new_eps = cs[i].weight / cs[j].weight - 1;
                
                if(last_sol)
                    new_eps = min(new_eps, 1 - cs[last_sol].profit / cs[j].profit);
            
                assert(new_eps >= 0);
                current_eps = max(
                    current_eps,
                    new_eps);
                //cout << i << " " << j << " " << k << endl;
           }
            
           if(current_eps > eps) {
                last_sol = i - 1;
                i--;
                k--;
                break;
           }
           if(i >= sz )  {
                k = 0;
                break;
           }
        }
    } 

    return 1.0 - cs[last_sol].profit/ cs[sz - 1].profit <= eps;
}

double optimal_pareto_curve(vector<candidate> &cs, int k) {

    double l, u;
    l = 0.;
    u = 1.0;

    for(int i =0 ; i < 10; i++) {
        double mid = (l + u) / 2;

        if(exists_set_with_k(cs, k, mid)) 
            u = mid;
        else l = mid;
    }

    return l;
}
