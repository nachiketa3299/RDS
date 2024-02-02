#include <array>

#include <gtest/gtest.h>

#include "Array.hpp"

using namespace rds;
using namespace std;

TEST(Array_test, BasicAccess)
{
    Array<int, 3> arr;
    arr.operator[](0) = 0;
    arr.operator[](1) = 1;
    arr.operator[](2) = 2;

    array<int, 3> tarr;
    tarr.operator[](0) = 0;
    tarr.operator[](1) = 1;
    tarr.operator[](2) = 2;

    for (auto it = arr.CBegin(); it != arr.CEnd(); ++it)
    {
        const auto index = it - arr.CBegin();
        EXPECT_EQ(it.operator*(), tarr.operator[](index));
    }
}