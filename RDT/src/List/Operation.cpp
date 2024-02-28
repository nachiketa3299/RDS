/// @file Operation.cpp

#include <algorithm>

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;
using namespace std;

/** @brief RemoveIf(UnaryPredicate_t) */
TEST(RemoveIf, __UnaryPredicate_t)
{
    initializer_list<int> il = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto unary_pred = [](const int& i) { return i % 2 == 0; };
    auto ans_count  = count_if(il.begin(), il.end(), unary_pred);

    { // Nallocator
        List<int, Nallocator> ans_li;
        for (auto& i: il)
        {
            if (!unary_pred(i))
            {
                ans_li.PushBack(i);
            }
        }
        List<int, Nallocator> li(il);

        auto count = li.RemoveIf(unary_pred);

        EXPECT_EQ(count, ans_count);
        EXPECT_EQ(li.Size(), ans_li.Size());

        auto ans_it = ans_li.Begin();
        for (auto it = li.Begin(); it != li.End(); ++it, ++ans_it)
        {
            EXPECT_EQ(*it, *ans_it);
        }
    }
    { // Mallocator
        List<int, Mallocator> ans_li;
        for (auto& i: il)
        {
            if (!unary_pred(i))
            {
                ans_li.PushBack(i);
            }
        }
        List<int, Mallocator> li(il);

        auto count = li.RemoveIf(unary_pred);

        EXPECT_EQ(count, ans_count);
        EXPECT_EQ(li.Size(), ans_li.Size());

        auto ans_it = ans_li.Begin();
        for (auto it = li.Begin(); it != li.End(); ++it, ++ans_it)
        {
            EXPECT_EQ(*it, *ans_it);
        }
    }
}

TEST(Remove, __void)
{
    initializer_list<int> il     = {0, 1, 2};
    initializer_list<int> ans_il = {0, 2};

    { // Nallocator
        List<int, Nallocator> li(il);

        auto zero_count = li.Remove(99);
        EXPECT_EQ(zero_count, 0);

        auto count = li.Remove(1);

        EXPECT_EQ(count, 1);
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(li.Front(), 0);
        EXPECT_EQ(li.Back(), 2);
        EXPECT_EQ(*li.Begin(), 0);
        EXPECT_EQ(*--li.End(), 2);

        auto it_il = ans_il.begin();

        for (auto it = li.Begin(); it != li.End(); ++it, ++it_il)
        {
            EXPECT_EQ(*it, *it_il);
        }
    }
}

RDT_END