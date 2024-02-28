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

    // clang-format off
    struct DummyType 
    {
        DummyType() = default;
        DummyType(int a, float b): a(a), b(b) {}
        explicit DummyType(int a): a(a) {}
        int a{};
        float b{};
    };

    // clang-format on
    { // Nallocator
        auto* node_ptr = List<int, Nallocator>::CreateNode(node_val);
        EXPECT_EQ(node_ptr->val, node_val);
        EXPECT_EQ(node_ptr->next, nullptr);
        EXPECT_EQ(node_ptr->prev, nullptr);

        List<int, Nallocator>::DeleteNode(node_ptr);

        auto d = DummyType(1);

        auto* dnode_ptr = List<DummyType, Nallocator>::CreateNode(d.a);

        EXPECT_EQ(dnode_ptr->val.a, d.a);
        EXPECT_EQ(dnode_ptr->val.b, d.b);

        List<DummyType, Nallocator>::DeleteNode(dnode_ptr);
    }

    { // Mallocator
        /// @todo 시발 Nallocator 로 생성한걸 Mallocator 로 없애도 왜 되는거지
        /// 이거 메모리 누수 있나 확인하려면 우주적 시간이 걸릴듯
        auto* node_ptr = List<int, Mallocator>::CreateNode(node_val);
        EXPECT_EQ(node_ptr->val, node_val);
        EXPECT_EQ(node_ptr->next, nullptr);
        EXPECT_EQ(node_ptr->prev, nullptr);
        // List<int, Nallocator>::DeleteNode(node_ptr);
        List<int, Mallocator>::DeleteNode(node_ptr);

        auto d = DummyType(1);

        auto* dnode_ptr = List<DummyType, Mallocator>::CreateNode(d.a);

        EXPECT_EQ(dnode_ptr->val.a, d.a);
        EXPECT_EQ(dnode_ptr->val.b, d.b);

        List<DummyType, Mallocator>::DeleteNode(dnode_ptr);
    }
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

TEST(Assignment, __initializer_list)
{
    const std::initializer_list<int> il = {99, 100};

    { // Nallocator
        List<int, Nallocator> li = {0, 1, 2, 3, 4, 5};
        List<int, Nallocator> li_ans(il);

        li = il;

        EXPECT_EQ(li.Size(), il.size());

        auto it_ans = li_ans.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
        }
    }

    { // Mallocator
        List<int, Mallocator> li = {0, 1, 2, 3, 4, 5};
        List<int, Mallocator> li_ans(il);

        li = il;

        EXPECT_EQ(li.Size(), il.size());

        auto it_ans = li_ans.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
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
TEST(InsertBefore, __Constiterator_t__Size_t__const_Value_t__Assertion)
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

TEST(InsertBefore, __ConstIterator_t__Size_t__const_Value_t)
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

#ifndef NDEBUG
// Erase 에 대해 Assertion이 제대로 걸리는지 확인
// (1) it_first 가 역참조 불가능한 경우 (End)
// (2) it_last 가 유효하지 않은 경우
// (3) it_fist 와 it_last가 Erase가 호출된 리스트와 호환되지 않는 경우
TEST(Erase, __ConstIterator_t__ConstIterator_t__Assertion)
{
    {
        List<int, Nallocator> li   = {0, 1, 2};
        List<int, Nallocator> li_a = {0, 1, 2};

        auto it_noderef = li.End();
        auto it_invalid = List<int, Nallocator>::Iterator_t(&li, nullptr);

        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_noderef, li.Begin()), "");
        RDT_EXPECT_EXIT_FAILURE(li.Erase(li.Begin(), it_invalid), "");

        auto it_ab = li_a.Begin();
        auto it_ae = li_a.End();

        RDT_EXPECT_EXIT_FAILURE(li.Erase(li.Begin(), it_ae), "");
        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_ab, li.End()), "");
    }

    {
        List<int, Mallocator> li   = {0, 1, 2};
        List<int, Mallocator> li_a = {0, 1, 2};

        auto it_noderef = li.End();
        auto it_invalid = List<int, Mallocator>::Iterator_t(&li, nullptr);

        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_noderef, li.Begin()), "");
        RDT_EXPECT_EXIT_FAILURE(li.Erase(li.Begin(), it_invalid), "");

        auto it_ab = li_a.Begin();
        auto it_ae = li_a.End();

        RDT_EXPECT_EXIT_FAILURE(li.Erase(li.Begin(), it_ae), "");
        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_ab, li.End()), "");
    }
}
#endif

TEST(Erase, __ConstIterator_t__ConstIterator_t)
{
    {     // Nallocator
        { // Fast return
            List<int, Nallocator> li{0, 1, 2};

            auto it_first = li.Begin();
            auto it_last  = li.Begin();
            auto it_ret   = li.Erase(it_first, it_last);

            EXPECT_TRUE(it_first == it_ret);
            EXPECT_TRUE(it_last == it_ret);
        }
        {     // Normal Case
            { // Begin 부터 시작해서 한 칸 지우기
                List<int, Nallocator> li{0, 1, 2, 3};
                List<int, Nallocator> li_ans{1, 2, 3};

                auto expect_size = li_ans.Size();

                auto it_first = li.Begin();
                auto it_last  = ++li.Begin();

                auto it_ret = li.Erase(it_first, it_last); // li{1, 2, 3}
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
            { // Begin 부터 시작해서 두 칸 지우기
                List<int, Nallocator> li{0, 1, 2, 3};
                List<int, Nallocator> li_ans{2, 3};

                auto expect_size = li_ans.Size();

                auto it_first = li.Begin();
                auto it_last  = ++(++li.Begin());

                auto it_ret = li.Erase(it_first, it_last);
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
            { // Begin 부터 시작해서 전체 지우기
                List<int, Nallocator> li{0, 1, 2, 3};
                List<int, Nallocator> li_ans{};

                auto expect_size = li_ans.Size();
                auto it_first    = li.Begin();
                auto it_last     = li.End();

                auto it_ret = li.Erase(it_first, it_last);
                EXPECT_TRUE(it_ret == li.End());
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);
                EXPECT_TRUE(li.Empty());
                EXPECT_EQ(li.Size(), 0);

                auto* sn_ptr = li.GetSentinelPointer();
                EXPECT_EQ(sn_ptr, sn_ptr->next);
                EXPECT_EQ(sn_ptr, sn_ptr->prev);
            }
            { // Begin 이후 시작해서 중간 지우기
                List<int, Nallocator> li{0, 1, 2, 3};
                List<int, Nallocator> li_ans{0, 3};

                auto expect_size = li_ans.Size();

                auto it_first = ++li.Begin();
                auto it_last  = ++(++(++li.Begin()));
                auto it_ret   = li.Erase(it_first, it_last);

                EXPECT_TRUE(it_ret == --(li.End()));
                EXPECT_TRUE(it_ret == it_last);

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
        }
    }

    {     // Mallocator
        { // Fast return
            List<int, Mallocator> li{0, 1, 2};

            auto it_first = li.Begin();
            auto it_last  = li.Begin();
            auto it_ret   = li.Erase(it_first, it_last);

            EXPECT_TRUE(it_first == it_ret);
            EXPECT_TRUE(it_last == it_ret);
        }
        {     // Normal Case
            { // Begin 부터 시작해서 한 칸 지우기
                List<int, Mallocator> li{0, 1, 2, 3};
                List<int, Mallocator> li_ans{1, 2, 3};

                auto expect_size = li_ans.Size();

                auto it_first = li.Begin();
                auto it_last  = ++li.Begin();

                auto it_ret = li.Erase(it_first, it_last); // li{1, 2, 3}
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
            { // Begin 부터 시작해서 두 칸 지우기
                List<int, Mallocator> li{0, 1, 2, 3};
                List<int, Mallocator> li_ans{2, 3};

                auto expect_size = li_ans.Size();

                auto it_first = li.Begin();
                auto it_last  = ++(++li.Begin());

                auto it_ret = li.Erase(it_first, it_last);
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
            { // Begin 부터 시작해서 전체 지우기
                List<int, Mallocator> li{0, 1, 2, 3};
                List<int, Mallocator> li_ans{};

                auto expect_size = li_ans.Size();
                auto it_first    = li.Begin();
                auto it_last     = li.End();

                auto it_ret = li.Erase(it_first, it_last);
                EXPECT_TRUE(it_ret == li.End());
                EXPECT_TRUE(it_ret == li.Begin());

                EXPECT_EQ(li.Size(), expect_size);
                EXPECT_TRUE(li.Empty());
                EXPECT_EQ(li.Size(), 0);

                auto* sn_ptr = li.GetSentinelPointer();
                EXPECT_EQ(sn_ptr, sn_ptr->next);
                EXPECT_EQ(sn_ptr, sn_ptr->prev);
            }
            { // Begin 이후 시작해서 중간 지우기
                List<int, Mallocator> li{0, 1, 2, 3};
                List<int, Mallocator> li_ans{0, 3};

                auto expect_size = li_ans.Size();

                auto it_first = ++li.Begin();
                auto it_last  = ++(++(++li.Begin()));
                auto it_ret   = li.Erase(it_first, it_last);

                EXPECT_TRUE(it_ret == --(li.End()));
                EXPECT_TRUE(it_ret == it_last);

                EXPECT_EQ(li.Size(), expect_size);

                auto it_ans = li_ans.Begin();
                for (auto it = li.Begin(); it != li.End(); ++it)
                {
                    EXPECT_EQ(*it, *it_ans);
                    ++it_ans;
                }
            }
        }
    }
}

#ifndef NDEBUG
/// 하나의 위치를 받는 Erase 에 대해 Assertion이 제대로 걸리는지 확인
/// 더이상 증가시킬 수 없는 반복자에 대해서 종료하는지 확인
TEST(Erase, __ConstIterator_t__Assertion)
{
    { // Nallocator
        List<int, Nallocator> li{0, 1};

        auto it_pos = li.End();

        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_pos), "");
    }
    { // Mallocator
        List<int, Mallocator> li{0, 1};

        auto it_pos = li.End();

        RDT_EXPECT_EXIT_FAILURE(li.Erase(it_pos), "");
    }
}
#endif
TEST(Erase, __ConstIterator_t)
{
    {     // Nallocator
        { // Begin 에서 하나
            List<int, Nallocator> li{0, 1, 2};
            List<int, Nallocator> li_ans{1, 2};

            auto expect_size = li_ans.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == li.Begin());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Begin 다음에 하나
            List<int, Nallocator> li{0, 1, 2};
            List<int, Nallocator> li_ans{0, 2};

            auto expect_size = li_ans.Size();

            auto it_pos = ++li.Begin();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == --li.End());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // 마지막 전
            List<int, Nallocator> li{0, 1, 2};
            List<int, Nallocator> li_ans{0, 1};

            auto expect_size = li_ans.Size();

            auto it_pos = --li.End();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == li.End());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }

    {     // Mallocator
        { // Begin 에서 하나
            List<int, Mallocator> li{0, 1, 2};
            List<int, Mallocator> li_ans{1, 2};

            auto expect_size = li_ans.Size();

            auto it_pos = li.Begin();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == li.Begin());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // Begin 다음에 하나
            List<int, Mallocator> li{0, 1, 2};
            List<int, Mallocator> li_ans{0, 2};

            auto expect_size = li_ans.Size();

            auto it_pos = ++li.Begin();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == --li.End());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }

        { // 마지막 전
            List<int, Mallocator> li{0, 1, 2};
            List<int, Mallocator> li_ans{0, 1};

            auto expect_size = li_ans.Size();

            auto it_pos = --li.End();
            auto it_ret = li.Erase(it_pos);

            EXPECT_TRUE(it_ret == li.End());
            EXPECT_EQ(li.Size(), expect_size);

            auto it_ans = li_ans.Begin();

            for (auto it = li.Begin(); it != li.End(); ++it)
            {
                EXPECT_EQ(*it, *it_ans);
                ++it_ans;
            }
        }
    }
}

TEST(Erase, __PushBack)
{
    { // Nallocator
        List<int, Nallocator> li;
        List<int, Nallocator> li_ans{99, 100};

        auto expect_size = li_ans.Size();

        li.PushBack(99);
        li.PushBack(100);

        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_FALSE(li.Empty());

        auto it_ans = li_ans.Begin();
        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
        }
    }
    { // Mallocator
        List<int, Mallocator> li;
        List<int, Mallocator> li_ans{99, 100};

        auto expect_size = li_ans.Size();

        li.PushBack(99);
        li.PushBack(100);

        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_FALSE(li.Empty());

        auto it_ans = li_ans.Begin();
        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
        }
    }
}

#ifndef NDEBUG
// PopBack 에 대해 Assertion이 제대로 걸리는지 확인
// 비어 있는 리스트에 대해 수행하였을 때 비정상 종료하는지 확인
TEST(PopBack, __void__Assertion)
{
    { // Nallocator
        List<int, Nallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.PopBack(), "");
    }
    { // Mallocator
        List<int, Mallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.PopBack(), "");
    }
}
#endif
TEST(PopBack, __void)
{
    { // Nallocator
        List<int, Nallocator> li{99, 100};
        List<int, Nallocator> li_ans;

        auto expect_size = li_ans.Size();

        li.PopBack();

        EXPECT_EQ(li.Size() - 1, expect_size);
        EXPECT_EQ(*--li.CEnd(), 99);

        li.PopBack();

        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_TRUE(li.Empty());
    }
    { // Mallocator
        List<int, Mallocator> li{99, 100};
        List<int, Mallocator> li_ans;

        auto expect_size = li_ans.Size();

        li.PopBack();

        EXPECT_EQ(li.Size() - 1, expect_size);
        EXPECT_EQ(*--li.CEnd(), 99);

        li.PopBack();

        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_TRUE(li.Empty());
    }
}

TEST(PushFront, __void)
{
    { // Nallocator
        List<int, Nallocator> li;
        List<int, Nallocator> li_ans{100, 99};

        auto expect_size = li_ans.Size();

        li.PushFront(99);
        EXPECT_EQ(li.Size() + 1, expect_size);
        EXPECT_EQ(*li.CBegin(), 99);

        li.PushFront(100);
        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_EQ(*li.CBegin(), 100);
        EXPECT_EQ(*--li.CEnd(), 99);

        auto it_ans = li_ans.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
        }
    }
    { // Mallocator
        List<int, Mallocator> li;
        List<int, Mallocator> li_ans{100, 99};

        auto expect_size = li_ans.Size();

        li.PushFront(99);
        EXPECT_EQ(li.Size() + 1, expect_size);
        EXPECT_EQ(*li.CBegin(), 99);

        li.PushFront(100);
        EXPECT_EQ(li.Size(), expect_size);
        EXPECT_EQ(*li.CBegin(), 100);
        EXPECT_EQ(*--li.CEnd(), 99);

        auto it_ans = li_ans.Begin();

        for (auto it = li.Begin(); it != li.End(); ++it)
        {
            EXPECT_EQ(*it, *it_ans);
            ++it_ans;
        }
    }
}

#ifndef NDEBUG
// PopFront 에 대해 Assertion이 제대로 걸리는지 확인
// 비어 있는 리스트에 대해 수행하였을 때 비정상 종료하는지 확인
TEST(PopFront, __void__Assertion)
{
    { // Nallocator
        List<int, Nallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.PopFront(), "");
    }
    { // Mallocator
        List<int, Mallocator> li;
        RDT_EXPECT_EXIT_FAILURE(li.PopFront(), "");
    }
}
#endif
TEST(PopFront, __void)
{
    { // Nallocator
        List<int, Nallocator> li{99, 100};
        List<int, Nallocator> li_ans;

        auto expect_size = li_ans.Size();

        li.PopFront();
        EXPECT_EQ(li.Size() - 1, expect_size);
        EXPECT_EQ(*li.CBegin(), 100);
        EXPECT_EQ(*--li.CEnd(), 100);
        li.PopFront();
        EXPECT_EQ(li.Size(), expect_size);

        EXPECT_TRUE(li.Empty());
        auto* sn = li.GetSentinelPointer();

        EXPECT_EQ(sn->next, sn);
        EXPECT_EQ(sn->prev, sn);
    }

    { // Mallocator
        List<int, Mallocator> li{99, 100};
        List<int, Mallocator> li_ans;

        auto expect_size = li_ans.Size();

        li.PopFront();
        EXPECT_EQ(li.Size() - 1, expect_size);
        EXPECT_EQ(*li.CBegin(), 100);
        EXPECT_EQ(*--li.CEnd(), 100);
        li.PopFront();
        EXPECT_EQ(li.Size(), expect_size);

        EXPECT_TRUE(li.Empty());
        auto* sn = li.GetSentinelPointer();

        EXPECT_EQ(sn->next, sn);
        EXPECT_EQ(sn->prev, sn);
    }
}

TEST(Swap, __void)
{
    {     // Nallocator
        { // 둘 다 Not empty
            std::initializer_list il_a = {0, 1, 2};
            std::initializer_list il_b = {99, 100};

            List<int, Nallocator> li_a(il_a);
            List<int, Nallocator> li_b(il_b);

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            auto it_il_b = il_b.begin();
            for (auto it = li_a.Begin(); it != li_a.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_b);
                ++it_il_b;
            }

            auto it_il_a = il_a.begin();
            for (auto it = li_b.Begin(); it != li_b.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_a);
                ++it_il_a;
            }
        }
        { // A 가 empty
            std::initializer_list il_b = {99, 100};

            List<int, Nallocator> li_a;
            List<int, Nallocator> li_b(il_b);

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            auto it_il_b = il_b.begin();
            for (auto it = li_a.Begin(); it != li_a.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_b);
                ++it_il_b;
            }

            EXPECT_TRUE(li_b.Empty());
        }
        { // B가 Empty
            std::initializer_list il_a = {0, 1, 2};

            List<int, Nallocator> li_a(il_a);
            List<int, Nallocator> li_b;

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            EXPECT_TRUE(li_a.Empty());

            auto it_il_a = il_a.begin();
            for (auto it = li_b.Begin(); it != li_b.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_a);
                ++it_il_a;
            }
        }
    }

    {     // Mallocator
        { // 둘 다 Not empty
            std::initializer_list il_a = {0, 1, 2};
            std::initializer_list il_b = {99, 100};

            List<int, Mallocator> li_a(il_a);
            List<int, Mallocator> li_b(il_b);

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            auto it_il_b = il_b.begin();
            for (auto it = li_a.Begin(); it != li_a.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_b);
                ++it_il_b;
            }

            auto it_il_a = il_a.begin();
            for (auto it = li_b.Begin(); it != li_b.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_a);
                ++it_il_a;
            }
        }
        { // A 가 empty
            std::initializer_list il_b = {99, 100};

            List<int, Mallocator> li_a;
            List<int, Mallocator> li_b(il_b);

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            auto it_il_b = il_b.begin();
            for (auto it = li_a.Begin(); it != li_a.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_b);
                ++it_il_b;
            }

            EXPECT_TRUE(li_b.Empty());
        }
        { // B가 Empty
            std::initializer_list il_a = {0, 1, 2};

            List<int, Mallocator> li_a(il_a);
            List<int, Mallocator> li_b;

            auto past_a_size = li_a.Size();
            auto past_b_size = li_b.Size();

            li_a.Swap(li_b);

            EXPECT_EQ(li_a.Size(), past_b_size);
            EXPECT_EQ(li_b.Size(), past_a_size);

            EXPECT_TRUE(li_a.Empty());

            auto it_il_a = il_a.begin();
            for (auto it = li_b.Begin(); it != li_b.End(); ++it)
            {
                EXPECT_EQ(*it, *it_il_a);
                ++it_il_a;
            }
        }
    }
}

struct EmplaceDummy
{
    EmplaceDummy() = default;

    EmplaceDummy(int a, float b, char c)
        : a(a)
        , b(b)
        , c(c)
    {}

    EmplaceDummy(int a, float b)
        : a(a)
        , b(b)
    {}

    auto operator==(const EmplaceDummy& other) const -> bool
    {
        return a == other.a && b == other.b && c == other.c;
    }

    int   a{};
    float b{};
    char  c{};
};

#ifndef NDEBUG
TEST(EmplaceBefore, __ConstIterator_t__CtorArgs_t__Assertion)
{
    {     // Nallocator
        { // Invalid Case
            List<EmplaceDummy, Nallocator> li;

            auto it_invalid =
                List<EmplaceDummy, Nallocator>::Iterator_t(&li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f, 'a'),
                                    "");
            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f), "");
        }
        { // Not Compatible Case
            List<EmplaceDummy, Nallocator> li;
            List<EmplaceDummy, Nallocator> li_a{EmplaceDummy()};

            auto it_incompatible = li_a.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                li.EmplaceBefore(it_incompatible, 1, 1.0f, 'a'), "");

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_incompatible, 1, 1.0f),
                                    "");
        }
    }
    {     // Mallocator
        { // Invalid Case
            List<EmplaceDummy, Mallocator> li;

            auto it_invalid =
                List<EmplaceDummy, Mallocator>::Iterator_t(&li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f, 'a'),
                                    "");
            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f), "");
        }
        { // Not Compatible Case
            List<EmplaceDummy, Mallocator> li;
            List<EmplaceDummy, Mallocator> li_a{EmplaceDummy()};

            auto it_incompatible = li_a.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                li.EmplaceBefore(it_incompatible, 1, 1.0f, 'a'), "");

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_incompatible, 1, 1.0f),
                                    "");
        }
    }
}
#endif

TEST(EmplaceBefore, __ConstIterator_t__CtorArgs_t)
{
    auto d_0 = EmplaceDummy(999, 999.f, 'Z');
    auto d_1 = EmplaceDummy(1'000, 1000.f, 'Y');
    auto d_2 = EmplaceDummy(1'001, 1001.f);

    { // Nallocator

        List<EmplaceDummy, Nallocator> li;
        auto it_ret = li.EmplaceBefore(li.Begin(), d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        it_ret = li.EmplaceBefore(++it_ret, d_1.a, d_1.b, d_1.c);
        it_ret = li.EmplaceBefore(++it_ret, d_2.a, d_2.b);
        EXPECT_TRUE(++it_ret == li.End());

        EXPECT_EQ(li.Size(), 3);
    }
    { // Mallocator

        List<EmplaceDummy, Mallocator> li;
        auto it_ret = li.EmplaceBefore(li.Begin(), d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        it_ret = li.EmplaceBefore(++it_ret, d_1.a, d_1.b, d_1.c);
        it_ret = li.EmplaceBefore(++it_ret, d_2.a, d_2.b);
        EXPECT_TRUE(++it_ret == li.End());

        EXPECT_EQ(li.Size(), 3);
    }
}

TEST(EmplaceFront, __CtorArgs_t)
{
    EmplaceDummy d_0(999, 999.f, 'Z');
    EmplaceDummy d_1(1'000, 1000.f, 'Y');
    EmplaceDummy d_2(1'001, 1001.f);

    { // Nallocator
        List<EmplaceDummy, Nallocator> li;

        auto it_ret = li.EmplaceFront(d_0.a, d_0.b, d_0.c);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*li.Begin(), d_0);

        it_ret = li.EmplaceFront(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*li.Begin(), d_1);

        it_ret = li.EmplaceFront(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*li.Begin(), d_2);

        auto it = li.Begin();
        EXPECT_EQ(*it, d_2);
        ++it;
        EXPECT_EQ(*it, d_1);
        ++it;
        EXPECT_EQ(*it, d_0);
    }
    { // Mallocator
        List<EmplaceDummy, Mallocator> li;

        auto it_ret = li.EmplaceFront(d_0.a, d_0.b, d_0.c);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*li.Begin(), d_0);

        it_ret = li.EmplaceFront(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*li.Begin(), d_1);

        it_ret = li.EmplaceFront(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*li.Begin(), d_2);

        auto it = li.Begin();
        EXPECT_EQ(*it, d_2);
        ++it;
        EXPECT_EQ(*it, d_1);
        ++it;
        EXPECT_EQ(*it, d_0);
    }
}

TEST(EmplaceBack, __CtorArgs_t)
{
    auto d_0 = EmplaceDummy(999, 999.f, 'Z');
    auto d_1 = EmplaceDummy(1'000, 1000.f, 'Y');
    auto d_2 = EmplaceDummy(1'001, 1001.f);

    { // Nallocator
        List<EmplaceDummy, Nallocator> li;

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
        List<EmplaceDummy, Mallocator> li;

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