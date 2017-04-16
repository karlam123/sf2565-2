#include "myexp.hpp"
#include <cmath>
double myexp(const double x, const double tol) {
    double sum = 1;
    double term = 1;
    const double fx = std::fabs(x);
    int n = 0;
    while (std::fabs(term)/(1-fx/(n+2)) > tol || n+2 < fx) {
        term *= x/(n+1);
        sum+=term;
        ++n;
    }
    return sum;
}
