#include "pch.h"
#include "../shift_array/functions.h"

TEST(TestReverse, TestSimpleArray) {
    size_t const SZ = 3;
    int arr[SZ] = { 1,2,3 };
    int res[SZ] = { 3,2,1 };
    reverseArray(arr, SZ);
    for (size_t idx = 0; idx < SZ; ++idx)
        EXPECT_EQ(arr[idx], res[idx]) << "wrong!";
}

TEST(TestReverse, TestUnitArray) {
    size_t const SZ = 1;
    int arr[SZ] = { 1 };
    int res[SZ] = { 1 };
    reverseArray(arr, SZ);
    for (size_t idx = 0; idx < SZ; ++idx)
        EXPECT_EQ(arr[idx], res[idx]);
}