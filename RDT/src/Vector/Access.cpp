#include <gtest/gtest.h>

#include "RDT_CoreDefs.h"

#include "Vector.hpp"
#include <limits>

RDT_BEGIN

using namespace rds;

/// @brief \ref Vector 클래스의 원소 접근자 테스트
class Vector_Access: public testing::Test
{
protected:
    Vector<int>       vec{0, 1, 2, 3};
    const Vector<int> cvec{0, 1, 2, 3};
};

TEST_F(Vector_Access, Front)
{
    EXPECT_EQ(vec.Front(), 0);
}

TEST_F(Vector_Access, Front_const)
{
    EXPECT_EQ(cvec.Front(), 0);
}

TEST_F(Vector_Access, Back)
{
    EXPECT_EQ(vec.Back(), 3);
}

TEST_F(Vector_Access, Back_const)
{
    EXPECT_EQ(cvec.Back(), 3);
}

TEST_F(Vector_Access, op_Subscript_const)
{
    for (std::size_t i = 0; i < vec.Size(); ++i)
    {
        EXPECT_EQ(cvec.operator[](i), i);
        EXPECT_EQ(cvec[i], i);
    }
}

TEST_F(Vector_Access, op_Subscript)
{
    for (std::size_t i = 0; i < vec.Size(); ++i)
    {
        EXPECT_EQ(vec.operator[](i), i);
        EXPECT_EQ(vec[i], i);
    }
}

// TEST_F(Vector_Access, op_Subscript_EXIT_posdir)
// {
//     RDT_EXPECT_EXIT_FAILURE(vec.operator[](vec.Size()), "");
//     RDT_EXPECT_EXIT_FAILURE(vec[vec.Size()], "");
// }

TEST_F(Vector_Access, At_const)
{
    for (std::size_t i = 0; i < vec.Size(); ++i)
    {
        EXPECT_EQ(cvec.At(i), i);
    }
}

TEST_F(Vector_Access, At_const_EXIT)
{
    RDT_EXPECT_EXIT_FAILURE(cvec.At(vec.Size()), "");
    RDT_EXPECT_EXIT_FAILURE(cvec.At(std::numeric_limits<std::size_t>::max()),
                            "");
    RDT_EXPECT_EXIT_FAILURE(cvec.At(-1), "");
}

TEST_F(Vector_Access, At)
{
    for (std::size_t i = 0; i < vec.Size(); ++i)
    {
        EXPECT_EQ(cvec.At(i), i);
    }
}

TEST_F(Vector_Access, At_EXIT)
{
    RDT_EXPECT_EXIT_FAILURE(vec.At(vec.Size()), "");
    RDT_EXPECT_EXIT_FAILURE(vec.At(std::numeric_limits<std::size_t>::max()),
                            "");
    RDT_EXPECT_EXIT_FAILURE(vec.At(-1), "");
}

RDT_END