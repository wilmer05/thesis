#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>

#define EPS 1e-9

using namespace std;


vector<double> xs,ys;

double compute_error(double b, double a) {
    double error = 0.;
    for(int i=0 ; i < xs.size(); i++) {
        error += pow(ys[i] - b * pow((double)xs[i] + 1, a), 2.0);
    }
    //cout << b << " " << a << " error: " << error << endl; 
    //cout << b * pow((double)xs.size() + 1, a) << " " << ys[ys.size()-1]<< endl;

    return error;
}

double compute_best_a_for_b(double b) {
    double l = .5;
    double r = 2.;
    while( fabs(r - l) > EPS ) {
        double l1 = l + (r-l)/3.0;
        double l2 = l + ((r-l) * 2.0)/3.0;
        double error = compute_error(b, l1);
        double error2 = compute_error(b, l2);
        if(error < error2) r = l2;
        else l = l1;
    }
    return l;
}

int main() {

    double x, y;
    while(scanf("%lf\t|\t%lf\n", &x, &y) == 2) {
        xs.push_back(x);
        ys.push_back(y);
        //cout << x << " " << y << endl;
    }

    double best_b=0, best_a=0.5;
    double lb=0.001, rb=2000;

    while(rb - lb > EPS) {
        double l1 = lb + (rb-lb) / 3.0;
        double l2 = lb + (2.0 * (rb-lb)) / 3.0;

        double a1 = compute_best_a_for_b(l1);
        double a2 = compute_best_a_for_b(l2);
        if(compute_error(l1,a1) < compute_error(l2,a2))
            rb = l2;
        else lb = l1; 
    }
    best_b = lb;
    best_a = compute_best_a_for_b(lb);

    //for(int i = 1 ; i < 2000; i++) {
    //    double b = .001 * ((double) i);
    //    cout << "b = " << b << " Error=";

    //    double l = .5;
    //    double r = 2.;
    //    while( fabs(r - l) > EPS ) {
    //        double l1 = l + (r-l)/3.0;
    //        double l2 = l + ((r-l) * 2.0)/3.0;
    //        double error = compute_error(b, l1);
    //        double error2 = compute_error(b, l2);
    //        if(error < error2) r = l2;
    //        else l = l1;
    //    }
    //    cout << compute_error(b,l) << endl;
    //    if(compute_error(b, l) < compute_error(best_b, best_a)) 
    //        best_b = b, best_a = l;
    //} 

    printf("Best function %.8lf * x ^ %.8lf\n\tError: %.4lf\n", best_b, best_a, compute_error(best_b, best_a));

    return 0;
}
