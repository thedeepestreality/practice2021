#include <iostream>

template <int arg1, int ... Args>
constexpr int Accumulate = arg1 + Accumulate<Args...>;

template<int arg1>
constexpr int Accumulate<arg1> = arg1;

template <int arg1, int ... Args>
constexpr int AccumulateSqr = arg1*arg1 + AccumulateSqr<Args...>;

template<int arg1>
constexpr int AccumulateSqr<arg1> = arg1*arg1;

int main(){
    std::cout << Accumulate<3, 6, -2, 100500> << '\n';
    std::cout << AccumulateSqr<1,2,3> << '\n';
    return 0;
}
