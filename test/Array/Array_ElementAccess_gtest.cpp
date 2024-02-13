/// @file Array_ElementAccess_gtest

#include <gtest/gtest.h>

#include "Array.hpp"

using namespace rds;
using namespace testing;

class Array_ElementAccess_int_fixture: public Test
{
protected:
    void SetUp() override
    {}

    Array<int, 5>       arr{0, 1, 2, 3, 4};
    const Array<int, 5> carr{0, 1, 2, 3, 4};
};

TEST_F(Array_ElementAccess_int_fixture, op_subscript_basic)
{
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(arr.operator[](i), i);
    }
}

TEST_F(Array_ElementAccess_int_fixture, const_op_subscript)
{
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(carr.operator[](i), i);
    }
}

TEST_F(Array_ElementAccess_int_fixture, at)
{

    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(arr.At(i), i);
    }
}

TEST_F(Array_ElementAccess_int_fixture, const_at)
{

    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(carr.At(i), i);
    }
}

TEST_F(Array_ElementAccess_int_fixture, exit_at)
{
    EXPECT_EXIT(arr.At(5), ExitedWithCode(EXIT_FAILURE), "");
    EXPECT_EXIT(arr.At(-1), ExitedWithCode(EXIT_FAILURE), ""); // maybe casted?
}

TEST_F(Array_ElementAccess_int_fixture, exit_const_at)
{
    EXPECT_EXIT(carr.At(5), ExitedWithCode(EXIT_FAILURE), "");
    EXPECT_EXIT(carr.At(-1), ExitedWithCode(EXIT_FAILURE), ""); // maybe casted?
}

TEST_F(Array_ElementAccess_int_fixture, front)
{
    EXPECT_EQ(arr.Front(), 0);
}

TEST_F(Array_ElementAccess_int_fixture, const_front)
{
    EXPECT_EQ(carr.Front(), 0);
}

TEST_F(Array_ElementAccess_int_fixture, back)
{
    EXPECT_EQ(arr.Back(), 4);
}

TEST_F(Array_ElementAccess_int_fixture, const_back)
{
    EXPECT_EQ(carr.Back(), 4);
}
