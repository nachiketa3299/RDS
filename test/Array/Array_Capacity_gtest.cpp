#include <gtest/gtest.h>

#include "Array.hpp"

using namespace rds;
using namespace testing;

class Array_Capacity_int_fixture: public Test
{
protected:
    Array<int, 1> arr_s1;
    Array<int, 2> arr_s2;
    Array<int, 3> arr_s3;
};

TEST_F(Array_Capacity_int_fixture, size)
{
    EXPECT_EQ(arr_s1.Size(), 1);
    EXPECT_EQ(arr_s2.Size(), 2);
    EXPECT_EQ(arr_s3.Size(), 3);
}

TEST_F(Array_Capacity_int_fixture, max_size)
{
    EXPECT_EQ(arr_s1.MaxSize(), 1);
    EXPECT_EQ(arr_s2.MaxSize(), 2);
    EXPECT_EQ(arr_s3.MaxSize(), 3);
}

TEST_F(Array_Capacity_int_fixture, empty)
{
    EXPECT_FALSE(arr_s1.Empty());
    EXPECT_FALSE(arr_s2.Empty());
    EXPECT_FALSE(arr_s3.Empty());
}