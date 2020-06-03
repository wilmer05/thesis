#include<vector>

using namespace std;

#ifndef ALG
#define ALG

struct candidate {
    double weight;
    double profit;

    candidate() {}

    candidate(double w, double p) : weight(w), profit(p) {}

    bool dominates(const candidate &other) const {
        return weight <= other.weight && profit >= other.profit && 
                (weight < other.weight || profit > other.profit);
    }
};

vector<candidate> nemhauser_ullman(const vector<double> &, const vector<double> &);

#endif
