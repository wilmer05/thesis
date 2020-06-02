#include<iostream>
#include<vector>
using namespace std;

struct solution {
    double weight;
    double cost;

    bool operator<(const solution &other) const {
        return weight >= other.weight && cost <= other.cost;
    }
};
