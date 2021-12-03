#include <iostream>
#include <ctime>
#include "duration.h"

void fancy_new()
{
    us_duration::tic();
    //some dummy calculations
    for (size_t i = 0; i < 1e6; ++i)
        double val = pow(0.1, 0.7) + pow(0.7, 0.1);
    std::cout << "elapsed time: " << us_duration::toc() << " us\n";
}

void ugly_oldschool()
{
    clock_t start = clock();
    //some dummy calculations
    for (size_t i = 0; i < 1e6; ++i)
        double val = pow(0.1, 0.7) + pow(0.7, 0.1);
    clock_t finish = clock();
    std::cout << "Elapsed time: ";
    std::cout << 1e6*(finish - start) / CLOCKS_PER_SEC << " us\n";
}

int main()
{
    ugly_oldschool();
    fancy_new();

    //compilation error, hidden field
    //us_duration::start = std::chrono::steady_clock::now();
    
    return 0;
}