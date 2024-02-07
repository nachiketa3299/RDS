#include <gtest/gtest.h>

#include "Node_D.hpp"

TEST(Initialization, DefaultConstructForPrimitiveTypes)
{
    rds::Node_D<int>    n_0;
    rds::Node_D<char>   n_1;
    rds::Node_D<bool>   n_2;
    rds::Node_D<float>  n_3;
    rds::Node_D<double> n_4;
}

struct Foo
{
    Foo() = default;

    Foo(int ia)
        : a(ia)
    {}

    int a;
};

TEST(Initialization, DefaultConstructForNonPrimitiveTypes)
{

    rds::Node_D<Foo> n_0;
}