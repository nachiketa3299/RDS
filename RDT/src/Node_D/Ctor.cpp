/// @file Node_D_Ctor_gtest.cpp

#include <gtest/gtest.h>

#include "Node_D.hpp"

using namespace rds;

#define NODE_DEF_TESTCASE(Typename)                                                    \
    {                                                                                  \
        rds::Node_D<Typename> node;                                                    \
        Typename              val{};                                                   \
        EXPECT_EQ(node.val, val);                                                      \
        EXPECT_EQ(node.next, nullptr);                                                 \
        EXPECT_EQ(node.prev, nullptr);                                                 \
    }

TEST(Ctor_default, primitive_types)
{
    NODE_DEF_TESTCASE(int);
    NODE_DEF_TESTCASE(long);
    NODE_DEF_TESTCASE(short)
    NODE_DEF_TESTCASE(long long);
    NODE_DEF_TESTCASE(float);
    NODE_DEF_TESTCASE(double);
    NODE_DEF_TESTCASE(long double);
    NODE_DEF_TESTCASE(bool);
    NODE_DEF_TESTCASE(char);
    NODE_DEF_TESTCASE(int*);
    NODE_DEF_TESTCASE(long*);
    NODE_DEF_TESTCASE(short*)
    NODE_DEF_TESTCASE(long long*);
    NODE_DEF_TESTCASE(float*);
    NODE_DEF_TESTCASE(double*);
    NODE_DEF_TESTCASE(long double*);
    NODE_DEF_TESTCASE(bool*);
    NODE_DEF_TESTCASE(char*);
}

#undef NODE_DEF_TESTCASE

TEST(Ctor_default, user_defined_types)
{
    struct ud_s
    {
        ud_s() = delete;
    };

    /*
    > Should not compile !!
        rds::Node_D<ud_s> node;
        ud_s              val{};
    */
}

TEST(Ctor_value, primitive_types)
{
    EXPECT_EQ(rds::Node_D<int>(1).val, 1);
    EXPECT_EQ(rds::Node_D<float>(1.f).val, 1.f);
}