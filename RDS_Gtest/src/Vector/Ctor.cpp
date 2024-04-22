/// @file Ctor.cpp

#include "RDT_CoreDefs.h"
#include <gtest/gtest.h>
#include <vector>

#include "Vector.hpp"

RDT_BEGIN

using namespace rds;

TEST(Vector_Ctor, size_init_val)
{
    Vector<int> vec(5, 3);
}

TEST(Vector_Ctor, init_list)
{
    Vector<int> vec{1, 2, 3, 4, 5};
}

TEST(Vector_Subscript, Const)
{
    const Vector<int> cvec{0, 1, 2, 3, 4};
    for (int i = 0; i < cvec.Size(); ++i)
    {
        EXPECT_EQ(cvec[i], i);
    }
}

TEST(Vector_Subscript, NonConst)
{
    Vector<int> vec{0, 1, 2, 3, 4};
    for (int i = 0; i < vec.Size(); ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(Vector_Reserve, NonConst)
{
    Vector<int> vec{0, 1, 2};
    EXPECT_EQ(vec.Capacity(), 3);
    vec.Reserve(5);
    EXPECT_EQ(vec.Capacity(), 5);
}

TEST(Vector_Assign, basic)
{
    Vector<int> vec{0, 1, 2, 3};
    vec.Assign(5, 3);

    std::vector<int> stdvec{0, 1, 2, 3};
    stdvec.assign(5, 3);
}

RDT_END