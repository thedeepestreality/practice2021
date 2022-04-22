#include <iostream>
static void static_foo();
inline void inline_foo();

inline void header_foo()
{
    std::cout << "I'm foo from header\n";
}