#include <gtest/gtest.h>

#include "Array.hpp"

using namespace rds;
using namespace std;

class IntArray_test: public ::testing::Test
{
protected:
    void SetUp() override
    {
        arr[0] = arr_val[0];
        arr[1] = arr_val[1];
        arr[2] = arr_val[2];
        arr[3] = arr_val[3];
    }

    Array<int, 4> arr;

    int arr_val[4] = {0, 1, 2, 3};
};

TEST_F(IntArray_test, IntArray_op_subscript)
{
    EXPECT_EQ(arr.operator[](0), arr_val[0]);
    EXPECT_EQ(arr.operator[](1), arr_val[1]);
    EXPECT_EQ(arr.operator[](2), arr_val[2]);
    EXPECT_EQ(arr.operator[](3), arr_val[3]);
}

TEST_F(IntArray_test, IntArray_op_subscript_const)
{
    const auto& carr = static_cast<const decltype(arr)&>(arr);

    EXPECT_EQ(carr.operator[](0), arr_val[0]);
    EXPECT_EQ(carr.operator[](1), arr_val[1]);
    EXPECT_EQ(carr.operator[](2), arr_val[2]);
    EXPECT_EQ(carr.operator[](3), arr_val[3]);
}