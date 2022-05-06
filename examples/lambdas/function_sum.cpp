#include <iostream>
#include <cmath>
#include <functional>

typedef std::function<double(double)> dfun;

double sqr(double x){
    return x*x;
}

auto sum(dfun f1, dfun f2){
    return [f1,f2] (double x) { return f1(x) + f2(x); };
}

int main(){

    auto sin_sqr = sum(sin, sqr);
    auto sin_sqr_sqrt = sum(sin_sqr, sqrt);
    double res = sin_sqr(1.57);
    std::cout << res << "\n";

    res = sin_sqr_sqrt(1.57);
    std::cout << res << "\n";

    return 0;
}