#include<vector>

using namespace std;

#ifndef ALG
#define ALG

#define MAX_BRUTE_FORCE_CORE_SIZE 20

struct candidate {
    double weight;
    double profit;

	int n_iterations_alive;

    candidate() : n_iterations_alive(0) {}

    candidate(double w, double p) : weight(w), profit(p), n_iterations_alive(0) {}

	void tick() {
		n_iterations_alive++;
	}

    bool dominates(const candidate &other) const {
        return weight <= other.weight && profit >= other.profit && 
                (weight < other.weight || profit > other.profit);
    }
};

struct item {
    double weight;
    double profit;
    bool belongs_to_fractional_solution;
    bool is_ray_item;
    
    static double dantzig_slope;

    item() {}

    item(double w, double p) : weight(w), profit(p), belongs_to_fractional_solution(false), is_ray_item(false) {}

    bool operator<(const item &other) const {
        return profit/weight > other.profit/other.weight;
    }
};

vector<candidate> nemhauser_ullman(const vector<double> &, const vector<double> &, double, bool, bool);

double core_algorithm(const vector<double> &, const vector<double> &, double);

double get_loss(const item &);

bool smaller_loss(const item &, const item &);

double get_integral_solution(const vector<item> &, double);

double brute_force(const vector<item> &, double);

double get_mask_profit(const vector<item> &, int);

double get_mask_weight(const vector<item> &, int);

void make_ticks(vector<candidate> &);

double compute_epsilon(candidate&, candidate&);

double approximate_pareto_curve(vector<candidate> &, int);

bool exists_set_with_k(vector<candidate> &, int, double);

double optimal_pareto_curve(vector<candidate> &, int);

double compute_epsilon_from(vector<candidate> &, vector<candidate> &);

#endif
