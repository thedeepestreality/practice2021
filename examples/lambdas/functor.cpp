#include <iostream>
#include <algorithm>
#include <functional>

struct greater{
    bool operator()(int a, int b){
        return a > b;
    }
};

struct less{
    bool operator()(int a, int b){
        return a < b;
    }
};

int main()
{
    int arr[] = {-1,-5,8,3,4};
    std::sort(arr, arr+5, greater());
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';
    
    //less l;
    std::function<bool(int,int)> l = less();
    std::cout << " 1 < 2 = " << l(1, 2) << "\n";
    std::sort(arr, arr+5, l);
    for (int const& val: arr)
        std::cout << val << ' ';
    std::cout << '\n';

    return 0;
}