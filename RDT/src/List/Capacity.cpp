/// @file Capacity.cpp

#include "RDT_CoreDefs.h"

#include "List.hpp"

RDT_BEGIN

using namespace rds;
using namespace std;

using ValueType = int;

using NListType                      = List<ValueType, Nallocator>;
using MListType                      = List<ValueType, Mallocator>;
const initializer_list<ValueType> il = {ValueType{0}, ValueType{1}};

TEST(Capacity, __Size__Empty_default)
{
    {
        NListType li;
        EXPECT_EQ(li.Size(), 0);
        EXPECT_TRUE(li.Empty());
        li = NListType(il);
        EXPECT_EQ(li.Size(), il.size());
        EXPECT_FALSE(li.Empty());
    }
    {
        MListType li;
        EXPECT_EQ(li.Size(), 0);
        EXPECT_TRUE(li.Empty());
        li = MListType(il);
        EXPECT_EQ(li.Size(), il.size());
        EXPECT_FALSE(li.Empty());
    }
}

TEST(Clear, __default)
{
    {
        const initializer_list<int> il   = {0, 1, 2};
        const size_t                size = il.size();

        {     // Nallocator
            { // case a : 비어있지 않았던 경우
                List<int, Nallocator> li(il);
                li.Clear();

                EXPECT_NE(li.Size(), size);
                EXPECT_TRUE(li.Empty());
                auto* sn = li.GetSentinelPointer();
                EXPECT_EQ(sn->next, sn);
                EXPECT_EQ(sn->prev, sn);
            }

            { // case b : 비어 있었던 경우
                List<int, Nallocator> li;
                li.Clear();

                EXPECT_TRUE(li.Empty());
                auto* sn = li.GetSentinelPointer();
                EXPECT_EQ(sn->next, sn);
                EXPECT_EQ(sn->prev, sn);
            }
        }

        {     // Mallocator
            { // case a : 비어있지 않았던 경우
                List<int, Mallocator> li(il);
                li.Clear();

                EXPECT_NE(li.Size(), size);
                EXPECT_TRUE(li.Empty());
                auto* sn = li.GetSentinelPointer();
                EXPECT_EQ(sn->next, sn);
                EXPECT_EQ(sn->prev, sn);
            }

            { // case b : 비어 있었던 경우
                List<int, Mallocator> li;
                li.Clear();

                EXPECT_TRUE(li.Empty());
                auto* sn = li.GetSentinelPointer();
                EXPECT_EQ(sn->next, sn);
                EXPECT_EQ(sn->prev, sn);
            }
        }
    }
}

{
    auto d_0 = EmplaceType(999, 999.f, 'Z');
    auto d_1 = EmplaceType(1'000, 1000.f, 'Y');
    auto d_2 = EmplaceType(1'001, 1001.f);

    { // Nallocator
        List<EmplaceType, Nallocator> li;

        auto it_ret = li.EmplaceBack(d_0.a, d_0.b, d_0.c);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*(--li.End()), d_0);

        it_ret = li.EmplaceBack(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*(--li.End()), d_1);

        it_ret = li.EmplaceBack(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*(--li.End()), d_2);

        auto it = li.Begin();
        EXPECT_EQ(*it, d_0);
        ++it;
        EXPECT_EQ(*it, d_1);
        ++it;
        EXPECT_EQ(*it, d_2);
    }
    { // Mallocator
        List<EmplaceType, Mallocator> li;

        auto it_ret = li.EmplaceBack(d_0.a, d_0.b, d_0.c);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*(--li.End()), d_0);

        it_ret = li.EmplaceBack(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*(--li.End()), d_1);

        it_ret = li.EmplaceBack(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*(--li.End()), d_2);

        auto it = li.Begin();
        EXPECT_EQ(*it, d_0);
        ++it;
        EXPECT_EQ(*it, d_1);
        ++it;
        EXPECT_EQ(*it, d_2);
    }
}
RDT_END