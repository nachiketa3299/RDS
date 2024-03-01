/// @file Iterator.cpp

#include "Iterator.hpp"
#include "RDT_CoreDefs.h"

#include "List.hpp"

RDT_BEGIN

using namespace rds;
using namespace std;

TEST(Basic, Basic)
{
    List<int> li{1, 2, 3};

    auto dist = DistanceBetween(li.Begin(), li.End());
    EXPECT_EQ(dist, li.Size());

    {
        auto it = li.Begin();
        Advance(it, 2);
        EXPECT_EQ(*it, 3);
    }
    {
        auto it = li.End();
        Advance(it, -2);
        EXPECT_EQ(*it, 2);
    }
}

RDT_END