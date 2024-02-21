#include "RDT_CoreDefs.h"
#include "TypeTraits.hpp"

#include <gtest/gtest.h>

#include <type_traits>

RDT_BEGIN

using namespace rds;

TEST(Integral_Constant, Integral_Constant)
{
    EXPECT_EQ((Integral_Constant<int, 42>::Value), 42);
    Integral_Constant<int, 99> ic;

    EXPECT_EQ(int(ic), 99);
    EXPECT_EQ((ic.operator int()), 99);
    EXPECT_EQ((int)ic, 99);

    EXPECT_EQ(static_cast<int>(ic), 99);
    EXPECT_EQ(ic(), 99);
    EXPECT_EQ(ic.operator()(), 99);
}

RDT_END
