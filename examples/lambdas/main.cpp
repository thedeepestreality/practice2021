#include <iostream>
#include <algorithm>
#include <functional>

bool greater(int a, int b){
    return a > b;
}

bool less(int a, int b){
    return a < b;
}

int main()
{
    int arr[] = {-1,-5,8,3,4};
    std::sort(arr, arr+5, greater);
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';

    std::function<bool(int,int)> l = less;
    std::sort(arr, arr+5, l);
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}