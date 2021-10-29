#include <iostream>

//compute polynomial value
//using straightforward solution
//and Horner's schemes

int main()
{
    const int N = 3;
    double coeffs[N] = { 1,2,3 };
    double x;
    std::cout << "x = ";
    std::cin >> x;
    //straightforward solution,
    //3 operations per iteration
    double px = 1;
    double sum1 = 0;
    for (int i = 0; i < N; ++i) {
        sum1 += coeffs[i] * px;
        px *= x;
    }

    //Horner's scheme,
    //2 operations per iteration
    double sum2 = 0;
    for (int i = N - 1; i >= 0; --i)
        sum2 = coeffs[i] + sum2 * x;

    std::cout << "p1(" << x << ") = ";
    std::cout << sum1 << "\n";
    std::cout << "p2(" << x << ") = ";
    std::cout << sum2 << "\n";
    return 0;
}