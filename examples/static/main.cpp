#include <iostream>
#include "header.h"

static int static_x = 0;
int global_x = 0;

int ext_foo();

void static_foo()
{
    std::cout << "I'm static from main!\n";
}

void inline_foo()
{
    std::cout << "I'm inline from main!\n";
}

void foo()
{
    int x = 0;
    ++x;
    static int sx = 0;
    ++sx;
    std::cout << "x = " << x << "\n";
    std::cout << "sx = " << sx << "\n";
}

int main()
{
    // foo();
    // foo();
    // foo();
    ext_foo();
    static_foo();
    inline_foo();
    return 0;
}