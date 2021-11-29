#include <iostream>
#include <stdexcept>
int divide(int a, int b, int& res)
{
    if (b == 0)
    {
        std::cout << "zero denumerator!\n";
        return 1;
    }
    res = a / b;
    return 0;
}

int divide_with_exception(int a, int b)
{
    if (b == 0)
        throw "division by zero";
       /// throw std::runtime_error("division bye zero");
    return a / b;
}

int f2(int x)
{
    //int res;
    //divide(1, x, res);
    int res = divide_with_exception(1, x);
    std::cout << "success\n";
    return res;
}

void f1()
{
    int val = f2(5);
    std::cout << "result is " << val << "\n";
}

int main()
{
    try {
        f1();
    }
    catch (const char* msg)
    {
        std::cout << "error happened: " << msg << "\n";
        return 1;
    }
    /*int result;
    if (divide(1, 0, result) != 0)
    {
        std::cout << "Division by zero\n";
        return -1;
    }*/
    return 0;
}