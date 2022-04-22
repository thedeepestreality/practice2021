#include <iostream>
#include <algorithm>
#include <functional>

int main()
{
    int arr[] = {-1,-5,8,3,4};
    std::sort(arr, arr+5, [](int a, int b){return a > b;});
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';
    
    // auto less = [](int a, int b){return a < b;};
    std::function<bool(int,int)> less = [](int a, int b){return a < b;};
    std::cout << " 1 < 2 = " << less(1, 2) << "\n";

    std::sort(arr, arr+5, less);
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}