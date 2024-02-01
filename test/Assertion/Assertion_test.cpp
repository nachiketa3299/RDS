#include <gtest/gtest.h>

#include "Assertion.h"
using namespace rds;

TEST(test01, Assertion_Test)
{
    RDS_Assert(1 == 1);
    RDS_Assert(1 == 2);
}