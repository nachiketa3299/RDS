/// @file Ctors.cpp

#include <gtest/gtest.h>

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;
using namespace std;

/** @brief List() */
TEST(Ctor, __default)
{
    { // Nallocator
        List<int, Nallocator> li;

        EXPECT_EQ(li.Size(), 0);
        EXPECT_EQ(li.GetSentinelPointer()->next, li.GetSentinelPointer());
        EXPECT_EQ(li.GetSentinelPointer()->prev, li.GetSentinelPointer());
    }

    { // Mallocator
        List<int, Mallocator> li;

        EXPECT_EQ(li.Size(), 0);
        EXPECT_EQ(li.GetSentinelPointer()->next, li.GetSentinelPointer());
        EXPECT_EQ(li.GetSentinelPointer()->prev, li.GetSentinelPointer());
    }
}

/** @brief List(Size_t, const Value_t&) */
TEST(Ctor, __Size_t__const_Valut_t_ref)
{
    const std::size_t size     = 2;
    const int         init_val = 1;

    { // Nallocator

        List<int, Nallocator> m_li(size, init_val);
        EXPECT_EQ(m_li.Size(), size);
        for (auto it = m_li.Begin(); it != m_li.End(); ++it)
        {
            EXPECT_EQ(*it, init_val);
        }
    }

    { // Mallocator

        List<int, Mallocator> n_li(size, init_val);
        EXPECT_EQ(n_li.Size(), size);
        for (auto it = n_li.Begin(); it != n_li.End(); ++it)
        {
            EXPECT_EQ(*it, init_val);
        }
    }
}

/** @brief List(Size_t) */
TEST(Ctor, __Size_t)
{
    const std::size_t size = 2;
    { // Nallocator

        List<int, Nallocator> li(size);
        EXPECT_EQ(li.Size(), size);
        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, int{});
        }
    }

    { // Mallocator
        List<int, Mallocator> li(size);
        EXPECT_EQ(li.Size(), size);
        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, int{});
        }
    }
}

/** @brief List(const std::initializer_list&) */
TEST(Ctor, __const_initializer_list_ref)
{

    initializer_list<int> il = {0, 1};

    { // Nallocator

        List<int, Nallocator> n_li(il);
        EXPECT_EQ(n_li.Size(), il.size());

        auto il_it = il.begin();

        for (auto it = n_li.Begin(); it != n_li.End(); ++it)
        {
            EXPECT_EQ(*it, *il_it);
            ++il_it;
        }
    }
    { // Mallocator

        List<int, Mallocator> m_li(il);

        EXPECT_EQ(m_li.Size(), il.size());

        auto il_it = il.begin();

        for (auto it = m_li.Begin(); it != m_li.End(); ++it)
        {
            EXPECT_EQ(*it, *il_it);
            ++il_it;
        }
    }
}

/** @brief List(const List&) */
TEST(Ctor, __const_List_ref)
{
    {     // Nallocator
        { // Empty Copy
            List<int, Nallocator> li_a;
            List<int, Nallocator> li(li_a);

            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // NonEmpty Copy
            initializer_list<int> il = {99, 100};

            List<int, Nallocator> li_a(il);
            List<int, Nallocator> li(li_a);

            EXPECT_EQ(li.Size(), li_a.Size());

            auto it_a = li_a.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }
    }
    {     // Mallocator
        { // Empty Copy
            List<int, Mallocator> li_a;
            List<int, Mallocator> li(li_a);

            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // NonEmpty Copy
            initializer_list<int> il = {99, 100};

            List<int, Mallocator> li_a(il);
            List<int, Mallocator> li(li_a);

            EXPECT_EQ(li.Size(), li_a.Size());

            auto it_a = li_a.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }
    }
}

/** @brief List(List&&) */
TEST(Ctor, __List_ref_ref)
{
    initializer_list<int> il = {99, 100};
    { // Nallocator

        List<int, Nallocator> li_a(il);
        List<int, Nallocator> li_a_copy(li_a);

        List<int, Nallocator> li(move(li_a));

        EXPECT_EQ(li.Size(), li_a_copy.Size());

        auto it_a = li_a_copy.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_a);
            ++it_a;
        }
    }
    { // Mallocator

        List<int, Mallocator> li_a(il);
        List<int, Mallocator> li_a_copy(li_a);

        List<int, Mallocator> li(move(li_a));

        EXPECT_EQ(li.Size(), li_a_copy.Size());

        auto it_a = li_a_copy.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_a);
            ++it_a;
        }
    }
}

/** @brief operator=(const List&) -> List&*/
TEST(Assignment, __const_List_ref)
{
    initializer_list<int> il = {99, 100};
    {     // Nallocator
        { // 다른 경우
            List<int, Nallocator> li;
            List<int, Nallocator> li_a(il);

            li.operator=(li_a); // Copy assign

            EXPECT_EQ(li.Size(), li_a.Size());

            auto* sn   = li.GetSentinelPointer();
            auto* sn_a = li_a.GetSentinelPointer();

            EXPECT_NE(sn->next, sn_a->next);
            EXPECT_NE(sn->prev, sn_a->prev);

            auto it_a = li_a.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }
        {     // 같은 경우
            { // 비어있음
                List<int, Nallocator> li;
                EXPECT_EQ(&li, &(li.operator=(li)));
            }
            { // 비어 있지 않음
                List<int, Nallocator> li(il);
                EXPECT_EQ(&li, &(li.operator=(li)));
            }
        }
    }

    {     // Mallocator
        { // 다른 경우
            List<int, Mallocator> li;
            List<int, Mallocator> li_a(il);

            li.operator=(li_a); // Copy assign

            EXPECT_EQ(li.Size(), li_a.Size());

            auto* sn   = li.GetSentinelPointer();
            auto* sn_a = li_a.GetSentinelPointer();

            EXPECT_NE(sn->next, sn_a->next);
            EXPECT_NE(sn->prev, sn_a->prev);

            auto it_a = li_a.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }
        {     // 같은 경우
            { // 비어있음
                List<int, Mallocator> li;
                EXPECT_EQ(&li, &(li.operator=(li)));
            }
            { // 비어 있지 않음
                List<int, Mallocator> li(il);
                EXPECT_EQ(&li, &(li.operator=(li)));
            }
        }
    }
}

/** @brief operator=(List&&) -> List&*/
TEST(Assignment, __List_ref_ref)
{
    initializer_list<int> il = {99, 100};
    { // Nallocator
        { // 이동 목적지가 비어있지 않고, 이동 원본이 비어있는 경우
            List<int, Nallocator> li(il);
            List<int, Nallocator> li_a;

            EXPECT_EQ(li.Size(), il.size());
            EXPECT_FALSE(li.Empty());

            li.operator=(move(li_a));

            EXPECT_TRUE(li.Empty());

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // 이동 목적지가 비어있고, 이동 원본이 비어있지 않음
            List<int, Nallocator> li;
            List<int, Nallocator> li_a(il);
            List<int, Nallocator> li_a_copy(li_a);

            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());

            auto* sn_a_next = li_a.GetSentinelPointer()->next;
            auto* sn_a_prev = li_a.GetSentinelPointer()->prev;

            li.operator=(move(li_a));

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn_a_next);
            EXPECT_EQ(sn->prev, sn_a_prev);

            EXPECT_EQ(li.Size(), li_a_copy.Size());
            EXPECT_FALSE(li.Empty());

            auto it_ac = li_a_copy.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ac);
                ++it_ac;
            }
        }
    }
    { // Mallocator
        { // 이동 목적지가 비어있지 않고, 이동 원본이 비어있는 경우
            List<int, Mallocator> li(il);
            List<int, Mallocator> li_a;

            EXPECT_EQ(li.Size(), il.size());
            EXPECT_FALSE(li.Empty());

            li.operator=(move(li_a));

            EXPECT_TRUE(li.Empty());

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // 이동 목적지가 비어있고, 이동 원본이 비어있지 않음
            List<int, Mallocator> li;
            List<int, Mallocator> li_a(il);
            List<int, Mallocator> li_a_copy(li_a);

            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());

            auto* sn_a_next = li_a.GetSentinelPointer()->next;
            auto* sn_a_prev = li_a.GetSentinelPointer()->prev;

            li.operator=(move(li_a));

            auto* sn = li.GetSentinelPointer();

            EXPECT_EQ(sn->next, sn_a_next);
            EXPECT_EQ(sn->prev, sn_a_prev);

            EXPECT_EQ(li.Size(), li_a_copy.Size());
            EXPECT_FALSE(li.Empty());

            auto it_ac = li_a_copy.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ac);
                ++it_ac;
            }
        }
    }
}

/** @brief operator=(const std::initializer_list&) -> List&*/
TEST(Assignment, __const_initializer_list_ref)
{
    initializer_list<int> il_base  = {0, 1};
    initializer_list<int> il       = {99, 100, 101};
    initializer_list<int> il_empty = {};

    {     // Nallocator
        { // 초기화 리스트가 비어있다
            List<int, Nallocator> li(il_base);

            li.operator=(il_empty);
            auto* sn = li.GetSentinelPointer();
            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());
            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // 초기화 리스트가 비어있지 않다
            List<int, Nallocator> li(il_base);

            li.operator=(il);

            EXPECT_EQ(li.Size(), il.size());

            auto il_it = il.begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *il_it);
                ++il_it;
            }
        }
    }

    {     // Mallocator
        { // 초기화 리스트가 비어있다
            List<int, Mallocator> li(il_base);

            li.operator=(il_empty);
            auto* sn = li.GetSentinelPointer();
            EXPECT_EQ(li.Size(), 0);
            EXPECT_TRUE(li.Empty());
            EXPECT_EQ(sn->next, sn);
            EXPECT_EQ(sn->prev, sn);
        }
        { // 초기화 리스트가 비어있지 않다
            List<int, Mallocator> li(il_base);

            li.operator=(il);

            EXPECT_EQ(li.Size(), il.size());

            auto il_it = il.begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *il_it);
                ++il_it;
            }
        }
    }
}

RDT_END