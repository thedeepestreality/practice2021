#include <iostream>

//transform decimal number to binary

int main(){
    int num;
    std::cout << "num = ";
    std::cin >> num;
    int num_tmp = num;
    int deg = 0;
    while ((num_tmp /= 2) != 0)
        ++deg;
    int two_deg = 1 << deg;
    while (two_deg != 0) {
        std::cout << (num / two_deg);
        num %= two_deg;
        two_deg >>= 1;
    }
    std::cout << "\n";
    return 0;
}