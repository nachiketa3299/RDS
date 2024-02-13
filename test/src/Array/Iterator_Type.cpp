#include <gtest/gtest.h>

#include <type_traits>

#include "Array.hpp"

using namespace rds;
using namespace testing;

class Array_Iterators_int_fixture: public Test
{
protected:
    void SetUp() override
    {}

    Array<int, 3>       arr{1, 2, 3};
    const Array<int, 3> carr{1, 2, 3};
};

TEST_F(Array_Iterators_int_fixture, type_normal_const)
{
    using Begin_t = decltype(arr.Begin());
    using End_t   = decltype(arr.End());

    using CBegin_t = decltype(arr.CBegin());
    using CEnd_t   = decltype(arr.CEnd());

    using Iter_t  = Array<int, 3>::Iterator;
    using CIter_t = Array<int, 3>::ConstIterator;

    EXPECT_TRUE((std::is_same_v<Begin_t, Iter_t>));
    EXPECT_TRUE((std::is_same_v<End_t, Iter_t>));
    EXPECT_TRUE((std::is_same_v<CBegin_t, CIter_t>));
    EXPECT_TRUE((std::is_same_v<CEnd_t, CIter_t>));

    EXPECT_FALSE((std::is_same_v<Begin_t, CIter_t>));
    EXPECT_FALSE((std::is_same_v<End_t, CIter_t>));
    EXPECT_FALSE((std::is_same_v<CBegin_t, Iter_t>));
    EXPECT_FALSE((std::is_same_v<CEnd_t, Iter_t>));
}