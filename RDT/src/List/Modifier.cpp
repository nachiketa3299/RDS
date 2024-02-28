/// @file Modifier.cpp

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

namespace modifier_test
{
struct EmplaceType
{
    EmplaceType() = default;

    EmplaceType(int a, float b, char c)
        : a(a)
        , b(b)
        , c(c)
    {}

    EmplaceType(int a, float b)
        : a(a)
        , b(b)
    {}

    auto operator==(const EmplaceType& other) const -> bool
    {
        return a == other.a && b == other.b && c == other.c;
    }

    int   a{};
    float b{};
    char  c{};
};

} // namespace modifier_test

using namespace rds;
using namespace std;
using namespace modifier_test;

#ifndef NDEBUG
/** @brief InsertBefore(ConstIterator_t, Size_t, const Value_t&) Assertion
 * 다음의 경우 비정상 종료하는지 확의
 * (1) 유효하지 않은 반복자에 대해 호출
 * (2) 호환되지 않는 반복자에 대해 호출
 */
TEST(InsertBefore, __Constiterator_t__Size_t__const_Value_t_ref__Assertion)
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
#endif

/** @brief InsertBefore(ConstIterator_t, Size_t, const Value_t&) */
TEST(InsertBefore, __ConstIterator_t__Size_t__const_Value_t_ref)
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

/** @brief InsertBefore(ConstIterator_t, const std::initializer_list&) */
TEST(InsertBefore, __ConstIterator_t__const_initializer_list_ref)
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
/** @brief Erase(ConstIterator_t, ConstIterator_t) Assertion
 * 다음의 경우 비정상 종료하는지 확인
 * (1) it_first 가 역참조 불가능한 경우 (End)
 * (2) it_last 가 유효하지 않은 경우
 * (3) it_fist 와 it_last가 Erase가 호출된 리스트와 호환되지 않는 경우
 */
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

/** @brief Erase(ConstIterator_t, ConstIterator_t) */
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
/** @brief Erase(ConstIterator_t) Assertion
 *  다음의 경우 비정상 종료하는지 확의
 *  더 이상 증가시킬 수 없는 반복자에 대해 호출
 */
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
/** @brief Erase(ConstIterator_t) */
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

/** @brief PushBack() */
TEST(PushBack, __void)
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
/** @brief PopBack() Assertion
 *  다음에 대해 비정상 종료하는지 확인
 *  비어 있는 리스트에 대해 호출하는 경우
 */
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
/** @brief PopBack() */
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

/** @brief Pushback() */
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
/** @brief PopFront() Assertion
 *  다음의 경우에 대해 비정상 종료하는지 확인
 *  비어 있는 리스트에 대해 수행
 */
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
/** @brief PopFront() */
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

/** @brief Swap() */
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

#ifndef NDEBUG
/** @brief EmplaceBefore(ConstIterator_t, CtorArgs_t&&...) Assertion
 * 다음에 대해 비정상 종료하는지 확인
 * (1) 반복자가 유효하지 않은 경우
 * (2) 반복자가 호환되지 않는 경우
 */
TEST(EmplaceBefore, __ConstIterator_t__CtorArgs_t__Assertion)
{
    {     // Nallocator
        { // Invalid Case
            List<EmplaceType, Nallocator> li;

            auto it_invalid =
                List<EmplaceType, Nallocator>::Iterator_t(&li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f, 'a'),
                                    "");
            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f), "");
        }
        { // Not Compatible Case
            List<EmplaceType, Nallocator> li;
            List<EmplaceType, Nallocator> li_a{EmplaceType()};

            auto it_incompatible = li_a.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                li.EmplaceBefore(it_incompatible, 1, 1.0f, 'a'), "");

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_incompatible, 1, 1.0f),
                                    "");
        }
    }
    {     // Mallocator
        { // Invalid Case
            List<EmplaceType, Mallocator> li;

            auto it_invalid =
                List<EmplaceType, Mallocator>::Iterator_t(&li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f, 'a'),
                                    "");
            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_invalid, 1, 1.0f), "");
        }
        { // Not Compatible Case
            List<EmplaceType, Mallocator> li;
            List<EmplaceType, Mallocator> li_a{EmplaceType()};

            auto it_incompatible = li_a.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                li.EmplaceBefore(it_incompatible, 1, 1.0f, 'a'), "");

            RDT_EXPECT_EXIT_FAILURE(li.EmplaceBefore(it_incompatible, 1, 1.0f),
                                    "");
        }
    }
}
#endif

/** @brief EmplaceBefore(ConstIterator_t, CtorArgs_t&&...) */
TEST(EmplaceBefore, __ConstIterator_t__CtorArgs_t)
{
    auto d_0 = EmplaceType(999, 999.f, 'Z');
    auto d_1 = EmplaceType(1'000, 1000.f, 'Y');
    auto d_2 = EmplaceType(1'001, 1001.f);

    { // Nallocator

        List<EmplaceType, Nallocator> li;
        auto it_ret = li.EmplaceBefore(li.Begin(), d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        it_ret = li.EmplaceBefore(++it_ret, d_1.a, d_1.b, d_1.c);
        it_ret = li.EmplaceBefore(++it_ret, d_2.a, d_2.b);
        EXPECT_TRUE(++it_ret == li.End());

        EXPECT_EQ(li.Size(), 3);
    }
    { // Mallocator

        List<EmplaceType, Mallocator> li;
        auto it_ret = li.EmplaceBefore(li.Begin(), d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        it_ret = li.EmplaceBefore(++it_ret, d_1.a, d_1.b, d_1.c);
        it_ret = li.EmplaceBefore(++it_ret, d_2.a, d_2.b);
        EXPECT_TRUE(++it_ret == li.End());

        EXPECT_EQ(li.Size(), 3);
    }
}

/** @brief EmplaceFront(CtorArgs_t...) */
TEST(EmplaceFront, __CtorArgs_t)
{
    EmplaceType d_0(999, 999.f, 'Z');
    EmplaceType d_1(1'000, 1000.f, 'Y');
    EmplaceType d_2(1'001, 1001.f);

    { // Nallocator
        List<EmplaceType, Nallocator> li;

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
        List<EmplaceType, Mallocator> li;

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

/** @brief EmplaceBack(CtorArgs_t...) */
TEST(EmplaceBack, __CtorArgs_t)
{
    EmplaceType d_0(999, 999.f, 'Z');
    EmplaceType d_1(1'000, 1000.f, 'Y');
    EmplaceType d_2(1'001, 1001.f);

    { // Nallocator
        List<EmplaceType, Nallocator> li;

        auto it_ret = li.EmplaceBack(d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*it_ret, d_0);

        it_ret = li.EmplaceBack(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == ++li.Begin());
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*it_ret, d_1);

        it_ret = li.EmplaceBack(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == ++(++li.Begin()));
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*it_ret, d_2);
    }
    { // Mallocator
        List<EmplaceType, Mallocator> li;

        auto it_ret = li.EmplaceBack(d_0.a, d_0.b, d_0.c);
        EXPECT_TRUE(it_ret == li.Begin());
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 1);
        EXPECT_EQ(*it_ret, d_0);

        it_ret = li.EmplaceBack(d_1.a, d_1.b, d_1.c);

        EXPECT_TRUE(it_ret == ++li.Begin());
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 2);
        EXPECT_EQ(*it_ret, d_1);

        it_ret = li.EmplaceBack(d_2.a, d_2.b);

        EXPECT_TRUE(it_ret == ++(++li.Begin()));
        EXPECT_TRUE(it_ret == --li.End());
        EXPECT_EQ(li.Size(), 3);
        EXPECT_EQ(*it_ret, d_2);
    }
}

RDT_END
