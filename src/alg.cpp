#include<iostream>
#include<vector>
#include<utility>
#include"alg.hpp"

using namespace std;


vector<candidate> nemhauser_ullman(const vector<double> &weights, const vector<double> &profits) {
    vector<candidate> p;
    p.push_back(candidate(0,0));
    
    int n = weights.size();
    for(int i=0; i<n; i++) {
        int sz = p.size();
        vector<candidate> q(sz);
        for(int j = 0 ; j < sz; j++ ) {
            q[j] = candidate(p[j].weight + weights[i], p[j].profit + profits[i]);
        }

        int k = 0, cnt_p = 0, cnt_q = 0;
        vector<candidate> tmp(sz << 1);
        
        while( cnt_p < p.size() || cnt_q < q.size()) {
            if(cnt_p >= p.size()) {
                tmp[k++] = q[cnt_q++];
                continue;
            }
            if(cnt_p >= p.size()) {
                tmp[k++] = p[cnt_p++];
                continue;
            }

            if(p[cnt_p].dominates(q[cnt_q])) {
                cnt_q++;
                continue;
            }

            if(q[cnt_q].dominates(p[cnt_p])) {
                cnt_p++;
                continue;
            }
            
            if(p[cnt_p].profit < q[cnt_q].profit) {
                tmp[k++] = p[cnt_p];
                tmp[k++] = q[cnt_q];
            } else {
                tmp[k++] = q[cnt_q];
                tmp[k++] = p[cnt_p]; 
            }
        
            cnt_p++,cnt_q++;
        }

        tmp.resize(k);
        p = tmp; 
    }

    return p;
}
