#pragma once
#include <utility>

inline void reverseArray(int* arr, int size)
{
    for (size_t i = 0; i < size / 2; ++i)
        std::swap(arr[i], arr[size - i - 1]);
}

inline void shiftArray(int* arr, int size, int shift)
{
    shift %= size;
    reverseArray(arr, size);
    reverseArray(arr + size - shift, shift);
    reverseArray(arr, size - shift);
}