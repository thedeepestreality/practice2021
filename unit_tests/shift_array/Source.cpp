#include <iostream>
#include <cassert>
#include "functions.h"

// Unit-tests as a part of the same program
#ifdef TEST
bool compareArray(int* a, int* b, size_t size);
void testShift();
#endif

int main()
{
#ifdef TEST
    testShift();
#endif
    int const SZ = 5;
    int arr[SZ] = { 3, 4, 5, 1, 2 };
    shiftArray(arr, 5, 2);
    for (size_t i = 0; i < SZ; ++i)
        std::cout << arr[i] << " ";
    std::cout << '\n';
    return 0;
}

#ifdef TEST
bool compareArray(int* a, int* b, size_t size)
{
    for (size_t idx = 0; idx < size; ++idx)
        if (a[idx] != b[idx])
            return false;
    return true;
}

void testShift()
{
    int const SZ = 5;
    int arr[SZ] = { 3, 4, 5, 1, 2 };
    int shifted[SZ] = { 1,2,3,4,5 };
    shiftArray(arr, 5, 2);
    if (compareArray(arr, shifted, SZ))
        std::cout << "Test passed\n";
    else
        std::cout << "Test failed\n";
}
#endif