/// @file List_Basic.cpp

#include <gtest/gtest.h>
#include <stdexcept>

#include "List.hpp"
#include "Mallocator.hpp"
#include "Nallocator.hpp"
#include "Node_D.hpp"
#include "RDT_CoreDefs.h"
#include <utility>

/*!
--------------------------------------------------------------------------------
[Ctor] List()
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 센티넬 노드 하나만 있는 리스트가 제대로 생성되는지?
    * 센티넬 노드의 `next`와 `prev`가 제대로 초기화되는지?
    * `size`가 0으로 초기화되는지?
--------------------------------------------------------------------------------
[Ctor] explicit List(Size_t)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 크기가 제대로 할당되는지?
    * 제대로 Default Initialize 되는지?
--------------------------------------------------------------------------------
[Ctor] List(Size_t, const Value_t&)
--------------------------------------------------------------------------------
[Ctor] List(std::initializer_list<Value_t>&)
--------------------------------------------------------------------------------
[Node] CreateNode(const Value_t&)
*/

RDT_BEGIN

using namespace rds;
using namespace std;

TEST(Ctor, __default)
{
    List<int, Nallocator> n_li;

    EXPECT_EQ(n_li.Size(), 0);
    EXPECT_EQ(n_li.GetSentinelPointer()->next, n_li.GetSentinelPointer());
    EXPECT_EQ(n_li.GetSentinelPointer()->prev, n_li.GetSentinelPointer());

    List<int, Mallocator> m_li;

    EXPECT_EQ(n_li.Size(), 0);
    EXPECT_EQ(n_li.GetSentinelPointer()->next, n_li.GetSentinelPointer());
    EXPECT_EQ(n_li.GetSentinelPointer()->prev, n_li.GetSentinelPointer());
}

TEST(Ctor, __only_size)
{
    List<int, Nallocator> n_li(2);
    EXPECT_EQ(n_li.Size(), 2);
    for (auto it = n_li.Begin(); it != n_li.End(); ++it)
    {
        EXPECT_EQ(*it, int{});
    }

    List<int, Mallocator> m_li(2);
    EXPECT_EQ(m_li.Size(), 2);
    for (auto it = m_li.Begin(); it != m_li.End(); ++it)
    {
        EXPECT_EQ(*it, int{});
    }
}

TEST(Ctor, __size__init_val)
{
    const std::size_t size     = 2;
    const int         init_val = 1;

    List<int, Nallocator> n_li(size, init_val);
    EXPECT_EQ(n_li.Size(), size);
    for (auto it = n_li.Begin(); it != n_li.End(); ++it)
    {
        EXPECT_EQ(*it, init_val);
    }

    List<int, Mallocator> m_li(size, init_val);
    EXPECT_EQ(m_li.Size(), size);
    for (auto it = m_li.Begin(); it != m_li.End(); ++it)
    {
        EXPECT_EQ(*it, init_val);
    }
}

TEST(Ctor, __initializer_list)
{

    initializer_list<int> il = {0, 1};

    auto il_it = il.begin();

    List<int, Nallocator> n_li(il);
    EXPECT_EQ(n_li.Size(), il.size());

    for (auto it = n_li.Begin(); it != n_li.End(); ++it)
    {
        EXPECT_EQ(*it, *il_it);
        ++il_it;
    }

    il_it = il.begin();

    List<int, Mallocator> m_li(il);

    EXPECT_EQ(m_li.Size(), il.size());

    for (auto it = m_li.Begin(); it != m_li.End(); ++it)
    {
        EXPECT_EQ(*it, *il_it);
        ++il_it;
    }
}

TEST(NodeManagement, __default)
{
    const int node_val = 99;

    auto* node_ptr = List<int, Nallocator>::CreateNode(node_val);
    EXPECT_EQ(node_ptr->val, node_val);
    EXPECT_EQ(node_ptr->next, nullptr);
    EXPECT_EQ(node_ptr->prev, nullptr);

    List<int, Nallocator>::DeleteNode(node_ptr);

    /// @todo 시발 Nallocator 로 생성한걸 Mallocator 로 없애도 왜 되는거지 이거
    /// 메모리 누수 있나 확인하려면 우주적 시간이 걸릴듯
    node_ptr = List<int, Mallocator>::CreateNode(node_val);
    EXPECT_EQ(node_ptr->val, node_val);
    EXPECT_EQ(node_ptr->next, nullptr);
    EXPECT_EQ(node_ptr->prev, nullptr);
    // List<int, Nallocator>::DeleteNode(node_ptr);
    List<int, Mallocator>::DeleteNode(node_ptr);
}

using ValueType = int;

using NListType                      = List<ValueType, Nallocator>;
using MListType                      = List<ValueType, Mallocator>;
const initializer_list<ValueType> il = {ValueType{0}, ValueType{1}};

TEST(Access, __Front____Back)
{

    {
        NListType li(il);

        auto f_it = li.Begin();
        auto b_it = --li.End();

        const auto& cli = const_cast<const NListType&>(li);

        EXPECT_EQ(li.Front(), *f_it);
        EXPECT_EQ(li.Back(), *b_it);

        EXPECT_EQ(cli.Front(), *f_it);
        EXPECT_EQ(cli.Back(), *b_it);
    }

    {
        MListType li(il);

        auto f_it = li.Begin();
        auto b_it = --li.End();

        const auto& cli = const_cast<const MListType&>(li);

        EXPECT_EQ(li.Front(), *f_it);
        EXPECT_EQ(li.Back(), *b_it);

        EXPECT_EQ(cli.Front(), *f_it);
        EXPECT_EQ(cli.Back(), *b_it);
    }
}

TEST(Access, __GetSentinelPointer)
{
    {
        NListType li(il);
        EXPECT_EQ(li.GetSentinelPointer(), li.End().GetDataPointer());
    }

    {
        MListType li(il);
        EXPECT_EQ(li.GetSentinelPointer(), li.End().GetDataPointer());
    }
}

TEST(Ctor, __Copy__Move)
{
    { // Copy
        List<int, Nallocator> n_li({99, 100});
        List<int, Nallocator> n_li_a(n_li);
        *n_li_a.Begin() = 999;
    }
    { // Move
        List<int, Nallocator> n_li({99, 100});
        List<int, Nallocator> n_li_a(std::move(n_li));
        *n_li_a.Begin() = 999;
    }

    { // Copy
        List<int, Mallocator> n_li({99, 100});
        List<int, Mallocator> n_li_a(n_li);
        *n_li_a.Begin() = 999;
    }
    { // Move
        List<int, Mallocator> n_li({99, 100});
        List<int, Mallocator> n_li_a(std::move(n_li));
        *n_li_a.Begin() = 999;
    }
}

TEST(Assignment, __Copy__Move)
{
    {     // Copy Assign
        { // Nallocator
            List<int, Nallocator> li;
            List<int, Nallocator> li_a({99, 100});
            EXPECT_NE(li.Size(), li_a.Size());
            EXPECT_NE(li.GetSentinelPointer(), li_a.GetSentinelPointer());

            li.operator=(li_a); // Copy assign
            EXPECT_EQ(li.Size(), li_a.Size());
            EXPECT_NE(li.GetSentinelPointer(), li_a.GetSentinelPointer());

            auto it_a = li_a.CBegin();
            for (auto it = li.CBegin(); it != li.CEnd(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }

        { // Mallocator
            List<int, Mallocator> li;
            List<int, Mallocator> li_a({99, 100});
            EXPECT_NE(li.Size(), li_a.Size());
            EXPECT_NE(li.GetSentinelPointer(), li_a.GetSentinelPointer());

            li.operator=(li_a); // Copy assign
            EXPECT_EQ(li.Size(), li_a.Size());
            EXPECT_NE(li.GetSentinelPointer(), li_a.GetSentinelPointer());

            auto it_a = li_a.CBegin();
            for (auto it = li.CBegin(); it != li.CEnd(); ++it)
            {
                EXPECT_EQ(*it, *it_a);
                ++it_a;
            }
        }
    }
    {         // Move Assign
        {     // Nallocator
            { // Move Assign - case a
                List<int, Nallocator> li;
                List<int, Nallocator> li_a({99, 100});

                auto* li_a_fnode = li_a.GetSentinelPointer()->next;

                auto li_ac(li_a);

                EXPECT_EQ(li.Size(), 0);
                EXPECT_TRUE(li.Empty());

                li.operator=(std::move(li_a)); // Move assign

                auto* li_fnode = li.GetSentinelPointer()->next;

                EXPECT_EQ(li_a_fnode, li_fnode);

                EXPECT_EQ(li.Size(), li_ac.Size());
                EXPECT_FALSE(li.Empty());

                auto it_ac = li_ac.CBegin();

                for (auto it = li.CBegin(); it != li.CEnd(); ++it)
                {
                    EXPECT_EQ(*it, *it_ac);
                    ++it_ac;
                }
            }
            { // Move Assign - case b 비어있는 리스트를 Move 시키기
                List<int, Nallocator> li({99, 100});
                List<int, Nallocator> li_a;

                EXPECT_EQ(li.Size(), 2);
                EXPECT_FALSE(li.Empty());

                li.operator=(std::move(li_a)); // Move assign

                EXPECT_TRUE(li.Empty());

                // and also it is empty too
                for (auto it = li.CBegin(); it != li.CEnd(); ++it) {}
            }
        }

        {     // Mallocator
            { // Move Assign - case a
                List<int, Mallocator> li;
                List<int, Mallocator> li_a({99, 100});

                auto* li_a_fnode = li_a.GetSentinelPointer()->next;

                auto li_ac(li_a);

                EXPECT_EQ(li.Size(), 0);
                EXPECT_TRUE(li.Empty());

                li.operator=(std::move(li_a)); // Move assign

                auto* li_fnode = li.GetSentinelPointer()->next;

                EXPECT_EQ(li_a_fnode, li_fnode);

                EXPECT_EQ(li.Size(), li_ac.Size());
                EXPECT_FALSE(li.Empty());

                auto it_ac = li_ac.CBegin();

                for (auto it = li.CBegin(); it != li.CEnd(); ++it)
                {
                    EXPECT_EQ(*it, *it_ac);
                    ++it_ac;
                }
            }
            { // Move Assign - case b 비어있는 리스트를 Move 시키기
                List<int, Mallocator> li({99, 100});
                List<int, Mallocator> li_a;

                EXPECT_EQ(li.Size(), 2);
                EXPECT_FALSE(li.Empty());

                li.operator=(std::move(li_a)); // Move assign

                EXPECT_TRUE(li.Empty());

                // and also it is empty too
                for (auto it = li.CBegin(); it != li.CEnd(); ++it) {}
            }
        }
    }
}

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

#ifndef NDEBUG
// Assertion이 제대로 걸리는지 확인
// (1) 유효하지 않은 반복자에 대해 종료하는지
// (2) 호환되지 않는 반복자에 대해 종료하는지
TEST(InsertBefore, __Constiterator_t__Size_t__const_Value_t_Assertion)
{
    { // Nallocator
        List<int, Nallocator> li;
        List<int, Nallocator> li_a;

        List<int, Nallocator>::Iterator_t it_pos;

        RDT_EXPECT_EXIT_FAILURE(li.InsertBefore(it_pos, 1, 99), "");

        it_pos = li_a.End();

        RDT_EXPECT_EXIT_FAILURE(li.InsertBefore(it_pos, 1, 99), "");
    }
    { // Mallocator
        List<int, Mallocator> li;
        List<int, Mallocator> li_a;

        List<int, Mallocator>::Iterator_t it_pos;

        RDT_EXPECT_EXIT_FAILURE(li.InsertBefore(it_pos, 1, 99), "");

        it_pos = li_a.End();

        RDT_EXPECT_EXIT_FAILURE(li.InsertBefore(it_pos, 1, 99), "");
    }
}
#else
#endif

TEST(InsertBefore, __Constiterator_t__Size_t__const_Value_t)
{
    const std::size_t count = 2;
    const int         val   = 99;

    {     // Nallocator
        { // Count is Empty
            List<int, Nallocator> li{0, 1, 2};

            auto it = li.Begin();

            auto it_ret = li.InsertBefore(it, 0, val);

            EXPECT_TRUE(it == it_ret);
        }

        { // Empty
            List<int, Nallocator> li;
            List<int, Nallocator> li_ans = {val, val};

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            EXPECT_EQ(li.Size(), count);

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, val);
            }
        }

        { // Not Empty - case a
            List<int, Nallocator> li({0, 1, 2});
            List<int, Nallocator> li_ans = {val, val, 0, 1, 2};

            const auto prev_size = li.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty - case b
            List<int, Nallocator> li({0, 1, 2});
            List<int, Nallocator> li_ans = {0, val, val, 1, 2};

            const auto prev_size = li.Size();

            auto it_pos = ++li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty - case c
            List<int, Nallocator> li({0, 1, 2});
            List<int, Nallocator> li_ans = {0, 1, 2, val, val};

            const auto prev_size = li.Size();

            auto it_pos = li.End();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }

    {     // Mallocator
        { // Count is Empty
            List<int, Mallocator> li{0, 1, 2};

            auto it = li.Begin();

            auto it_ret = li.InsertBefore(it, 0, val);

            EXPECT_TRUE(it == it_ret);
        }

        { // Empty
            List<int, Mallocator> li;
            List<int, Mallocator> li_ans = {val, val};

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            EXPECT_EQ(li.Size(), count);

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, val);
            }
        }

        { // Not Empty - case a
            List<int, Mallocator> li({0, 1, 2});
            List<int, Mallocator> li_ans = {val, val, 0, 1, 2};

            const auto prev_size = li.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty - case b
            List<int, Mallocator> li({0, 1, 2});
            List<int, Mallocator> li_ans = {0, val, val, 1, 2};

            const auto prev_size = li.Size();

            auto it_pos = ++li.Begin();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty - case c
            List<int, Mallocator> li({0, 1, 2});
            List<int, Mallocator> li_ans = {0, 1, 2, val, val};

            const auto prev_size = li.Size();

            auto it_pos = li.End();
            auto it_ret = li.InsertBefore(it_pos, count, val);

            const auto new_size = li.Size();

            EXPECT_EQ(prev_size + count, new_size);

            EXPECT_EQ(*it_ret, val);
            EXPECT_EQ(*(++it_ret), val);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }
}

TEST(InsertBefore, __ConstIterator_t__initializer_list)
{
    std::initializer_list il  = {99, 100, 101};
    auto                  ilb = il.begin();

    {     // Nallocator
        { // Empty
            List<int, Nallocator> li;
            List<int, Nallocator> li_ans(il);

            auto prev_size = li.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, il);

            auto new_size = li.Size();

            EXPECT_EQ((prev_size + il.size()), new_size);

            auto it_ans = li_ans.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }

            // 지우고 End에 대해 다시 넣어보기
            li.Clear();
            EXPECT_TRUE(li.Empty());
            prev_size = li.Size();
            it_pos    = li.End();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();
            EXPECT_EQ((prev_size + il.size()), new_size);

            it_ans = li_ans.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty
            List<int, Nallocator> li     = {0, 1, 2};
            List<int, Nallocator> li_ans = {*(ilb), *(ilb + 1), *(ilb + 2),
                                            0,      1,          2};
            // case a
            auto                  it_pos = li.Begin();

            auto prev_size = li.Size();
            auto it_ret    = li.InsertBefore(it_pos, il);
            auto new_size  = li.Size();
            EXPECT_EQ(prev_size + il.size(), new_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
            // case b
            li     = {0, 1, 2};
            li_ans = {0, *(ilb), *(ilb + 1), *(ilb + 2), 1, 2};
            it_pos = ++li.Begin();

            prev_size = li.Size();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();

            EXPECT_EQ(prev_size + il.size(), new_size);

            it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }

            // case c

            li     = {0, 1, 2};
            li_ans = {0, 1, 2, *(ilb), *(ilb + 1), *(ilb + 2)};
            it_pos = li.End();

            prev_size = li.Size();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();

            EXPECT_EQ(prev_size + il.size(), new_size);

            it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }

    {     // Mallocator
        { // Empty
            List<int, Mallocator> li;
            List<int, Mallocator> li_ans(il);

            auto prev_size = li.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.InsertBefore(it_pos, il);

            auto new_size = li.Size();

            EXPECT_EQ((prev_size + il.size()), new_size);

            auto it_ans = li_ans.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }

            // 지우고 End에 대해 다시 넣어보기
            li.Clear();
            EXPECT_TRUE(li.Empty());
            prev_size = li.Size();
            it_pos    = li.End();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();
            EXPECT_EQ((prev_size + il.size()), new_size);

            it_ans = li_ans.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Not Empty
            List<int, Mallocator> li     = {0, 1, 2};
            List<int, Mallocator> li_ans = {*(ilb), *(ilb + 1), *(ilb + 2),
                                            0,      1,          2};
            // case a
            auto                  it_pos = li.Begin();

            auto prev_size = li.Size();
            auto it_ret    = li.InsertBefore(it_pos, il);
            auto new_size  = li.Size();
            EXPECT_EQ(prev_size + il.size(), new_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
            // case b
            li     = {0, 1, 2};
            li_ans = {0, *(ilb), *(ilb + 1), *(ilb + 2), 1, 2};
            it_pos = ++li.Begin();

            prev_size = li.Size();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();

            EXPECT_EQ(prev_size + il.size(), new_size);

            it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }

            // case c

            li     = {0, 1, 2};
            li_ans = {0, 1, 2, *(ilb), *(ilb + 1), *(ilb + 2)};
            it_pos = li.End();

            prev_size = li.Size();
            it_ret    = li.InsertBefore(it_pos, il);
            new_size  = li.Size();

            EXPECT_EQ(prev_size + il.size(), new_size);

            it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }
}

RDT_END