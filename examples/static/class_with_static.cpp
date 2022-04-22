#include <iostream>

struct Dummy{
    int x;
    static int sx;
    void foo(){
        std::cout << "x = " << x << "\n";
        std::cout << "sx = " << sx << "\n";
    }
    static void static_foo(){
        std::cout << "sx = " << sx << "\n";
    }
    Dummy():x(0){
        ++x;
        ++sx;
    }
};

int Dummy::sx = 0;

template <class T>
struct Dummier{
    T x;
    static int sx;
    Dummier(){
        ++sx;
    }
    int getSx(){
        return sx;
    }
};

int main()
{
    Dummy::static_foo();
    std::cout << Dummy::sx << "\n";
    Dummy d1;
    d1.foo();
    d1.static_foo();
    Dummy d2;
    d2.foo();
    d2.static_foo();

    Dummier<int> di1;
    Dummier<int> di2;
    Dummier<double> dd1;
    Dummier<double> dd2;
    //dd2.getSx() == ?

    return 0;
}