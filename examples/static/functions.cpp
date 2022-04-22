#include <iostream>
#include "header.h"
extern int global_x;

int ext_foo()
{
    static_foo();
    inline_foo();
    return global_x;
}

void static_foo()
{
    std::cout << "I'm static from functions!\n";
}

void inline_foo()
{
    std::cout << "I'm inline from functions!\n";
}