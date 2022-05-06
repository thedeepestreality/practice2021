#include <iostream>



template <class Type>
void print(Type val){
    std::cout << val << "\n";
}

template <class Head, class ... Tail> // parameter pack
void print(Head val, Tail ... args){
    std::cout << val << ", ";
    print(args...);
}

int main(){
    int x = 2;
    char c = 'x';
    bool b = false;
    double d = 2.718;
    char str[] = "hello";
    print(x, c, b, d, str);
    print(str, d);
    print(b, x, str); // demo below
    return 0;
}

// demo for print(b, x, str)
// void print(bool b, int x, char str[])
// {
//     std::cout << b << ", ";
//     print(x, str);
// }

// void print(int x, char str[])
// {
//     std::cout << x << ", ";
//     print(str);
// }

// void print(char str[])
// {
//     std::cout << str << "\n";
// }