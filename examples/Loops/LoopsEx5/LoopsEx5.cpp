#include <iostream>

//Sine Taylor series:
//f(x) = x - x^3/3! + x^5/5! - x^7/7! + ... = sin(x)

int main(){
    double x1, x2, dx, eps;
    std::cout << "x1 x2 dx eps: ";
    std::cin >> x1 >> x2 >> dx >> eps;
    std::cout << "x\tf(x)\t\tsin(x)\n";
    for (; x1 <= x2; x1 += dx){
        std::cout << x1 << "\t";
        double curr = x1;
        double sum = 0;
        int cnt = 1;
        while (std::abs(curr) >= eps){
            sum += curr;
            cnt += 2;
            curr = -curr * x1 * x1 / (cnt * (cnt - 1));
        }
        std::cout << sum << "\t" << sin(x1) << "\n";
    }
    return 0;
}
