#include <iostream>
#include <chrono>

// exponential Taylor series
// f(x) = 1 + x/1! + x^2/2! + ... = e^x

double fact(int n);

int main()
{
    double x = 0.9;
    double res = 0;
    double curr = 1;
    int const N = 8000000;
    auto start = std::chrono::steady_clock::now();
    for (int count = 1; count <= N; ++count) {
        res += curr;
        //Bad and slow
        //curr = pow(x, count) / fact(count);

        //Amazing and fast
        curr *= x / count;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::cout << "res\texp(x)\n";
    std::cout << res << "\t" << exp(x) << "\n";
    return 0;
}

double fact(int n)
{
    double res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}