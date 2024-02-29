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

#ifndef NDEBUG
/** @brief SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t,
 * ConstIterator_t) Assertion
 * 다음의 경우 비정상 종료하는지 확인
 * - this_it_pos가 유효하지 않음
 * - this_it_pos가 호출한 리스트와 호환되지 않음.
 * - other_it_first가 다른 리스트와 호환되지 않음.
 * - other_it_first가 역참조가 불가능
 * - other_it_last가 유효하지 않음
 * - other_it_last가 다른 리스트와 호환되지 않음
 */
TEST(SpliceAndInsertBefore,
     __ConstIterator_t__List_ref__ConstIterator_t__ConstIterator_t__Assertion)
{
    initializer_list<int> il = {99, 100, 101};
    {     // Nallocator
        { // this_it_pos 검사
            List<int, Nallocator> this_li;
            List<int, Nallocator> other_li(il);

            // this_it_pos 가 유효하지 않은 경우
            List<int, Nallocator>::Iterator_t invalid_this_it(&this_li,
                                                              nullptr);
            EXPECT_FALSE(invalid_this_it.IsValid());

            RDT_EXPECT_EXIT_FAILURE((this_li.SpliceAndInsertBefore(
                                        invalid_this_it, other_li,
                                        other_li.Begin(), other_li.End())),
                                    "");

            // this_it_pos 가 호환되지 않는 경우

            auto incompatible_this_it = other_li.Begin();
            RDT_EXPECT_EXIT_FAILURE((this_li.SpliceAndInsertBefore(
                                        incompatible_this_it, other_li,
                                        other_li.Begin(), other_li.End())),
                                    "");
        }
        { // other_it_first 검사
            List<int, Nallocator> li(il);
            List<int, Nallocator> other_li;

            // 호환되지 않는 경우
            auto incompatible_other_it = li.Begin();
            RDT_EXPECT_EXIT_FAILURE((li.SpliceAndInsertBefore(
                                        li.Begin(), other_li,
                                        incompatible_other_it, other_li.End())),
                                    "");
            // 역참조가 불가능한 경우
            auto indereferencible_other_it = other_li.End();
            RDT_EXPECT_EXIT_FAILURE(
                (li.SpliceAndInsertBefore(li.Begin(), other_li,
                                          indereferencible_other_it,
                                          other_li.End())),
                "");
        }
        { // other_it_last 검사
            List<int, Nallocator> li(il);
            List<int, Nallocator> other_li;

            // 유요하지 않은 경우
            auto invalid_other_it =
                List<int, Nallocator>::Iterator_t(&other_li, nullptr);
            RDT_EXPECT_EXIT_FAILURE(
                (li.SpliceAndInsertBefore(li.Begin(), other_li,
                                          other_li.Begin(), invalid_other_it)),
                "");

            // 호환되지 않는 경우
            auto incompatible_other_it = li.Begin();
            RDT_EXPECT_EXIT_FAILURE((li.SpliceAndInsertBefore(
                                        li.Begin(), other_li, other_li.Begin(),
                                        incompatible_other_it)),
                                    "");
        }
    }

    {     // Mallocator
        { // this_it_pos 검사
            List<int, Mallocator> this_li;
            List<int, Mallocator> other_li(il);

            // this_it_pos 가 유효하지 않은 경우
            List<int, Mallocator>::Iterator_t invalid_this_it(&this_li,
                                                              nullptr);
            EXPECT_FALSE(invalid_this_it.IsValid());

            RDT_EXPECT_EXIT_FAILURE((this_li.SpliceAndInsertBefore(
                                        invalid_this_it, other_li,
                                        other_li.Begin(), other_li.End())),
                                    "");

            // this_it_pos 가 호환되지 않는 경우

            auto incompatible_this_it = other_li.Begin();
            RDT_EXPECT_EXIT_FAILURE((this_li.SpliceAndInsertBefore(
                                        incompatible_this_it, other_li,
                                        other_li.Begin(), other_li.End())),
                                    "");
        }
        { // other_it_first 검사
            List<int, Mallocator> li(il);
            List<int, Mallocator> other_li;

            // 호환되지 않는 경우
            auto incompatible_other_it = li.Begin();
            RDT_EXPECT_EXIT_FAILURE((li.SpliceAndInsertBefore(
                                        li.Begin(), other_li,
                                        incompatible_other_it, other_li.End())),
                                    "");
            // 역참조가 불가능한 경우
            auto indereferencible_other_it = other_li.End();
            RDT_EXPECT_EXIT_FAILURE(
                (li.SpliceAndInsertBefore(li.Begin(), other_li,
                                          indereferencible_other_it,
                                          other_li.End())),
                "");
        }
        { // other_it_last 검사
            List<int, Mallocator> li(il);
            List<int, Mallocator> other_li;

            // 유효하지 않은 경우
            auto invalid_other_it =
                List<int, Mallocator>::Iterator_t(&other_li, nullptr);
            RDT_EXPECT_EXIT_FAILURE(
                (li.SpliceAndInsertBefore(li.Begin(), other_li,
                                          other_li.Begin(), invalid_other_it)),
                "");

            // 호환되지 않는 경우
            auto incompatible_other_it = li.Begin();
            RDT_EXPECT_EXIT_FAILURE((li.SpliceAndInsertBefore(
                                        li.Begin(), other_li, other_li.Begin(),
                                        incompatible_other_it)),
                                    "");
        }
    }
}
#endif

/** @brief SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t,
 * ConstIterator_t) */
TEST(SpliceAndInsertBefore,
     __ConstIterator_t__List_ref__ConstIterator_t__ConstIterator_t)
{
    initializer_list<int> a = {99, 100, 101};
    initializer_list<int> b = {0, 1, 2, 3, 4};
    {     // Nallocator
        { // Other 이 비어있는 경우
            List<int, Nallocator> this_li(a);
            List<int, Nallocator> other_li;

            // 애초에 정상적으로 이걸 호출할 방법이 없다.
            // 비어 있는 경우 Begin이 센티넬 노드를 가리키고 있기 때문에.
            // this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
            //                              other_li.Begin(),
            //                              other_li.End());
        }
        { // 비어 있는 범위를 전달하는 경우
            List<int, Nallocator> this_li(a);
            List<int, Nallocator> this_li_copy(this_li);

            auto past_size = this_li.Size();

            List<int, Nallocator> other_li(b);
            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          --other_li.End(), --other_li.End());

            // 아무 변화 없어야함
            EXPECT_EQ(this_li.Size(), past_size);

            auto this_it = this_li.Begin();
            for (auto it = this_li_copy.Begin(); it != this_li_copy.End();
                 ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
        { // This 가 비어있는 경우
            List<int, Nallocator> this_li;
            List<int, Nallocator> other_li(b);
            List<int, Nallocator> other_li_copy(other_li);

            auto past_other_size = other_li.Size();

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          other_li.Begin(), other_li.End());

            EXPECT_EQ(this_li.Size(), past_other_size);

            auto this_it = this_li.Begin();
            for (auto it = other_li_copy.Begin(); it != other_li_copy.End();
                 ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
        { // 둘 다 비어있는 경우
          // 정상적으로 호출을 못함
        }
        { // 아무도 안 비어있는 Sane 한 상태
            List<int, Nallocator> this_li(a);
            List<int, Nallocator> other_li(b);

            List<int, Nallocator> li_ans{99, 1, 2, 100, 101};

            this_li.SpliceAndInsertBefore(++this_li.Begin(), other_li,
                                          ++other_li.Begin(),
                                          -- --other_li.End());

            auto this_it = this_li.Begin();

            for (auto it = li_ans.Begin(); it != li_ans.End(); ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
    }

    {     // Mallocator
        { // Other 이 비어있는 경우
            List<int, Mallocator> this_li(a);
            List<int, Mallocator> other_li;

            // 애초에 정상적으로 이걸 호출할 방법이 없다.
            // 비어 있는 경우 Begin이 센티넬 노드를 가리키고 있기 때문에.
            // this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
            //                              other_li.Begin(),
            //                              other_li.End());
        }
        { // 비어 있는 범위를 전달하는 경우
            List<int, Mallocator> this_li(a);
            List<int, Mallocator> this_li_copy(this_li);

            auto past_size = this_li.Size();

            List<int, Mallocator> other_li(b);
            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          --other_li.End(), --other_li.End());

            // 아무 변화 없어야함
            EXPECT_EQ(this_li.Size(), past_size);

            auto this_it = this_li.Begin();
            for (auto it = this_li_copy.Begin(); it != this_li_copy.End();
                 ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
        { // This 가 비어있는 경우
            List<int, Mallocator> this_li;
            List<int, Mallocator> other_li(b);
            List<int, Mallocator> other_li_copy(other_li);

            auto past_other_size = other_li.Size();

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          other_li.Begin(), other_li.End());

            EXPECT_EQ(this_li.Size(), past_other_size);

            auto this_it = this_li.Begin();
            for (auto it = other_li_copy.Begin(); it != other_li_copy.End();
                 ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
        { // 둘 다 비어있는 경우
          // 정상적으로 호출을 못함
        }
        { // 아무도 안 비어있는 Sane 한 상태
            List<int, Mallocator> this_li(a);
            List<int, Mallocator> other_li(b);

            List<int, Mallocator> li_ans{99, 1, 2, 100, 101};

            this_li.SpliceAndInsertBefore(++this_li.Begin(), other_li,
                                          ++other_li.Begin(),
                                          -- --other_li.End());

            auto this_it = this_li.Begin();

            for (auto it = li_ans.Begin(); it != li_ans.End(); ++it, ++this_it)
            {
                EXPECT_EQ(*it, *this_it);
            }
        }
    }
}

#ifndef NDEBUG
/** @brief SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t)
 * Assertion
 * 다음의 경우 비정상 종료하는지 확지
 * - this_it_pos가 유효하지 않음
 * - this_it_pos가 호출한 리스트와 호환되지 않음.
 * - other_it_first가 다른 리스트와 호환되지 않음
 * - other_it_first가 유효하지 않음
 * */
TEST(SpliceAndInsertBefore,
     __ConstIterator_t__List_ref__ConstIterator_t__Assertion)
{
    initializer_list<int> il = {1, 2, 3};
    {     // Nallocator
        { // this_it_pos 가 유효하지 않은 경우
            List<int, Nallocator>             this_li;
            List<int, Nallocator>             other_li(il);
            List<int, Nallocator>::Iterator_t invaid_this_it_pos(&this_li,
                                                                 nullptr);
            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(invaid_this_it_pos, other_li,
                                               other_li.Begin())),
                "");
        }
        { // this_it_pos 가 호환되지 않는 경우
            List<int, Nallocator> this_li(il);
            List<int, Nallocator> other_li(il);

            auto incompatible_this_it = other_li.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(incompatible_this_it, other_li,
                                               other_li.Begin())),
                "");
        }
        { // other_it_first 가 다른 리스트와 호환되지 않음

            List<int, Nallocator> this_li(il);
            List<int, Nallocator> other_li(il);

            auto incompatible_other_it_pos = this_li.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                               incompatible_other_it_pos)),
                "");
        }
        { // other_it_first 가 유효하지 않음
            List<int, Nallocator> this_li(il);
            List<int, Nallocator> other_li(il);

            auto invalid_other_it_pos =
                List<int, Nallocator>::Iterator_t(&other_li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                               invalid_other_it_pos)),
                "");
        }
    }

    {     // Mallocator
        { // this_it_pos 가 유효하지 않은 경우
            List<int, Mallocator>             this_li;
            List<int, Mallocator>             other_li(il);
            List<int, Mallocator>::Iterator_t invaid_this_it_pos(&this_li,
                                                                 nullptr);
            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(invaid_this_it_pos, other_li,
                                               other_li.Begin())),
                "");
        }
        { // this_it_pos 가 호환되지 않는 경우
            List<int, Mallocator> this_li(il);
            List<int, Mallocator> other_li(il);

            auto incompatible_this_it = other_li.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(incompatible_this_it, other_li,
                                               other_li.Begin())),
                "");
        }
        { // other_it_first 가 다른 리스트와 호환되지 않음

            List<int, Mallocator> this_li(il);
            List<int, Mallocator> other_li(il);

            auto incompatible_other_it_pos = this_li.Begin();

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                               incompatible_other_it_pos)),
                "");
        }
        { // other_it_first 가 유효하지 않음
            List<int, Mallocator> this_li(il);
            List<int, Mallocator> other_li(il);

            auto invalid_other_it_pos =
                List<int, Mallocator>::Iterator_t(&other_li, nullptr);

            RDT_EXPECT_EXIT_FAILURE(
                (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                               invalid_other_it_pos)),
                "");
        }
    }
}
#endif

/** @brief SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t)
 */
TEST(SpliceAndInsertBefore, __ConstIterator_t__List_ref__ConstIterator_t)
{
    initializer_list<int> il_a = {99, 100, 101};
    initializer_list<int> il_b = {1, 2, 3};
    {     // Nallocator
        { // This 가 비어있고, Other는 비어있지 않음
            List<int, Nallocator> this_li;
            List<int, Nallocator> other_li(il_a);

            List<int, Nallocator> this_li_result{100, 101};

            EXPECT_TRUE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          ++other_li.Begin());

            EXPECT_EQ(this_li.Size(), this_li_result.Size());

            auto this_it_result = this_li_result.Begin();

            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }
        }
        { // This 가 비어있지 않고, Other는 비어있지 않음
            List<int, Nallocator> this_li(il_a);
            List<int, Nallocator> other_li(il_b);

            List<int, Nallocator> this_li_result{99, 2, 3, 100, 101};
            List<int, Nallocator> other_li_result{1};

            EXPECT_FALSE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(++this_li.Begin(), other_li,
                                          ++other_li.Begin());

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result  = this_li_result.Begin();
            auto other_it_result = other_li_result.Begin();

            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }
        { // This 가 비어있고, Other도 비어있음 -> 이 경우는 항상 비정상 종료
        }
        { // This 가 비어있지 않고, Other도 비어있음 -> 이 경우는 항상 비정상
          // 종료
        }
    }

    {     // Mallocator
        { // This 가 비어있고, Other는 비어있지 않음
            List<int, Mallocator> this_li;
            List<int, Mallocator> other_li(il_a);

            List<int, Mallocator> this_li_result{100, 101};

            EXPECT_TRUE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li,
                                          ++other_li.Begin());

            EXPECT_EQ(this_li.Size(), this_li_result.Size());

            auto this_it_result = this_li_result.Begin();

            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }
        }
        { // This 가 비어있지 않고, Other는 비어있지 않음
            List<int, Mallocator> this_li(il_a);
            List<int, Mallocator> other_li(il_b);

            List<int, Mallocator> this_li_result{99, 2, 3, 100, 101};
            List<int, Mallocator> other_li_result{1};

            EXPECT_FALSE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(++this_li.Begin(), other_li,
                                          ++other_li.Begin());

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result  = this_li_result.Begin();
            auto other_it_result = other_li_result.Begin();

            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }
        { // This 가 비어있고, Other도 비어있음 -> 이 경우는 항상 비정상 종료
        }
        { // This 가 비어있지 않고, Other도 비어있음 -> 이 경우는 항상 비정상
          // 종료
        }
    }
}

#ifndef NDEBUG
/** @brief SpliceAndInsertBefore(ConstIterator_t, List&) Assertion
 * 다음의 경우 비정상 종료하는지 확인
 * - other 가 비어있는 경우
 */
TEST(SpliceAndInsertBefore, __ConstIterator_t__List_ref__Assertion)
{
    { // Nallocator
        List<int, Nallocator> this_li;
        List<int, Nallocator> other_li;

        RDT_EXPECT_EXIT_FAILURE(
            (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li)), "");
    }

    { // Mallocator
        List<int, Mallocator> this_li;
        List<int, Mallocator> other_li;

        RDT_EXPECT_EXIT_FAILURE(
            (this_li.SpliceAndInsertBefore(this_li.Begin(), other_li)), "");
    }
}
#endif

/** @brief SpliceAndInsertBefore(ConstIterator_t, List&)*/
TEST(SpliceAndInsertBefore, __ConstIterator_t__List_ref)
{
    initializer_list<int> il_a = {99, 100, 101};
    initializer_list<int> il_b = {1, 2};
    {     // Nallocator
        { // This 가 비어있고, Other 는 비어있지 않음
            List<int, Nallocator> this_li;
            List<int, Nallocator> other_li(il_a);

            List<int, Nallocator> this_li_result(il_a);
            List<int, Nallocator> other_li_result;

            EXPECT_TRUE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li);

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result = this_li_result.Begin();
            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            auto other_it_result = other_li_result.Begin();
            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }

        { // This 가 비어있지 않고, Other 는 비어있지 않음
            List<int, Nallocator> this_li(il_a);
            List<int, Nallocator> other_li(il_b);

            List<int, Nallocator> this_li_result{99, 100, 1, 2, 101};
            List<int, Nallocator> other_li_result;

            EXPECT_FALSE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(--this_li.End(), other_li);

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result = this_li_result.Begin();
            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            auto other_it_result = other_li_result.Begin();
            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }

        { // This 가 비어있고, Other 는 비어있음 -> 항상 비정상 종료
        }
        { // This 가 비어있지 않고, Other 는 비어있음 -> 항상 비정상 종료
        }
    }

    {     // Mallocator
        { // This 가 비어있고, Other 는 비어있지 않음
            List<int, Mallocator> this_li;
            List<int, Mallocator> other_li(il_a);

            List<int, Mallocator> this_li_result(il_a);
            List<int, Mallocator> other_li_result;

            EXPECT_TRUE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(this_li.Begin(), other_li);

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result = this_li_result.Begin();
            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            auto other_it_result = other_li_result.Begin();
            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }

        { // This 가 비어있지 않고, Other 는 비어있지 않음
            List<int, Mallocator> this_li(il_a);
            List<int, Mallocator> other_li(il_b);

            List<int, Mallocator> this_li_result{99, 100, 1, 2, 101};
            List<int, Mallocator> other_li_result;

            EXPECT_FALSE(this_li.Empty());
            EXPECT_FALSE(other_li.Empty());

            this_li.SpliceAndInsertBefore(--this_li.End(), other_li);

            EXPECT_EQ(this_li.Size(), this_li_result.Size());
            EXPECT_EQ(other_li.Size(), other_li_result.Size());

            auto this_it_result = this_li_result.Begin();
            for (auto it = this_li.Begin(); it != this_li.End();
                 ++it, ++this_it_result)
            {
                EXPECT_EQ(*it, *this_it_result);
            }

            auto other_it_result = other_li_result.Begin();
            for (auto it = other_li.Begin(); it != other_li.End();
                 ++it, ++other_it_result)
            {
                EXPECT_EQ(*it, *other_it_result);
            }
        }

        { // This 가 비어있고, Other 는 비어있음 -> 항상 비정상 종료
        }
        { // This 가 비어있지 않고, Other 는 비어있음 -> 항상 비정상 종료
        }
    }
}

/** @brief Reverse() */
TEST(Reverse, __void)
{
    initializer_list<int> il = {1, 2, 3};

    {     // Nallocator
        { // 비어있음
            List<int, Nallocator> li;
            li.Reverse();
            // 이거 뭐 테스트할게 없네...
        }
        { // 원소가 하나
            List<int, Nallocator> li{int{}};
            li.Reverse();

            EXPECT_EQ(*li.Begin(), int{});
        }
        { // 원소가 둘 이상
            List<int, Nallocator> li(il);
            List<int, Nallocator> li_ans{3, 2, 1};

            li.Reverse();

            auto ans_it = li_ans.Begin();
            for (auto it = li.Begin(); it != li.End(); ++it, ++ans_it)
            {
                EXPECT_EQ(*it, *ans_it);
            }
        }
    }
}

RDT_END