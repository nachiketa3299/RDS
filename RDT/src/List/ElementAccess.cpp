/// @file ElementAccess.cpp

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;
using namespace std;

#ifndef NDEBUG
/** @brief Front() -> Value_t& && Front() const -> const Value_t&
 *  리스트가 비어있는 경우, 비정상 종료 확인
 */
TEST(Front, __void__const__Assertion)
{
    { // Nallocator
        List<int, Nallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.Front(), "");
        RDT_EXPECT_EXIT_FAILURE(const_cast<const decltype(li)&>(li).Front(),
                                "");
    }
    { // Mallocator
        List<int, Mallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.Front(), "");
        RDT_EXPECT_EXIT_FAILURE(const_cast<const decltype(li)&>(li).Front(),
                                "");
    }
}

/** @brief Back() -> Value_t& && Back() const -> const Value_t&
 *  리스트가 비어있는 경우, 비정상 종료 확인
 */
TEST(Back, __void__const__Assertion)
{
    { // Nallocator
        List<int, Nallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.Back(), "");
        RDT_EXPECT_EXIT_FAILURE(const_cast<const decltype(li)&>(li).Back(), "");
    }
    { // Mallocator
        List<int, Mallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.Back(), "");
        RDT_EXPECT_EXIT_FAILURE(const_cast<const decltype(li)&>(li).Back(), "");
    }
}
#endif

/** @brief Front() -> Value_t& && Front() const -> const Value_t& */
TEST(Front, __void__const)
{
    initializer_list il = {0, 1};
    { // Nallocator
        List<int, Nallocator> li(il);

        EXPECT_EQ(li.Front(), *il.begin());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), *il.begin());

        EXPECT_EQ(li.Front(), *li.Begin());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), *li.Begin());

        li.Front() = 99;
        EXPECT_EQ(li.Front(), 99);
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), 99);
        EXPECT_EQ(*li.Begin(), 99);
    }
    { // Mallocator
        List<int, Mallocator> li(il);

        EXPECT_EQ(li.Front(), *il.begin());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), *il.begin());

        EXPECT_EQ(li.Front(), *li.Begin());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), *li.Begin());

        li.Front() = 99;
        EXPECT_EQ(li.Front(), 99);
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Front(), 99);
        EXPECT_EQ(*li.Begin(), 99);
    }
}

TEST(Back, __void__const)
{
    initializer_list il = {99, 100};
    { // Nallocator
        List<int, Nallocator> li(il);

        EXPECT_EQ(li.Back(), *(il.end() - 1));
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), *(il.end() - 1));

        EXPECT_EQ(li.Back(), *--li.End());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), *--li.End());

        li.Back() = 0;
        EXPECT_EQ(li.Back(), 0);
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), 0);
        EXPECT_EQ(*--li.End(), 0);
    }
    { // Mallocator
        List<int, Mallocator> li(il);

        EXPECT_EQ(li.Back(), *(il.end() - 1));
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), *(il.end() - 1));

        EXPECT_EQ(li.Back(), *--li.End());
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), *--li.End());

        li.Back() = 0;
        EXPECT_EQ(li.Back(), 0);
        EXPECT_EQ(const_cast<const decltype(li)&>(li).Back(), 0);
        EXPECT_EQ(*--li.End(), 0);
    }
}

TEST(GetSentinelPointer, __void)
{
    { // Nallocator
        List<int, Nallocator> li;
        EXPECT_EQ(li.GetSentinelPointer(), li.GetSentinelPointer()->next);
        EXPECT_EQ(li.GetSentinelPointer(), li.GetSentinelPointer()->prev);
    }
    { // Mallocator
        List<int, Mallocator> li;
        EXPECT_EQ(li.GetSentinelPointer(), li.GetSentinelPointer()->next);
        EXPECT_EQ(li.GetSentinelPointer(), li.GetSentinelPointer()->prev);
    }
}

RDT_END