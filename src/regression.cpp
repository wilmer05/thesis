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
        error += pow(ys[i] - b * pow((double)i + 1, a), 2.0);
    }
    //cout << b << " " << a << " error: " << error << endl; 
    //cout << b * pow((double)xs.size() + 1, a) << " " << ys[ys.size()-1]<< endl;

    return error;
}

int main() {

    double x, y;
    while(scanf("%lf\t|\t%lf\n", &x, &y) == 2) {
        xs.push_back(x);
        ys.push_back(y);
        //cout << x << " " << y << endl;
    }

    double best_b=0, best_a=0.5;

    for(int i = 0 ; i < 200; i++) {
        double b = .01 * ((double) i);

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
        //cout << compute_error(b,l) << endl;
        if(compute_error(b, l) < compute_error(best_b, best_a)) 
            best_b = b, best_a = l;
    } 

    printf("Best function %.4lf * x ^ %.4lf\n\tError: %.4lf\n", best_b, best_a, compute_error(best_b, best_a));

    return 0;
}
