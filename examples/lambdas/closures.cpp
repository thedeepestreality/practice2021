#include <iostream>

int main(){
    int a = 0;
    int b = 2;
    auto foo = [&a, b](){return a+b;};
    // enclose everything by value
    // auto foo = [=](){return a+b;}; 

    // enclose everything by reference
    // auto foo = [&](){return a+b;};
    a = 2;
    b = 4;
    // int x = foo();
    std::cout << foo() << '\n';
    return 0;
}