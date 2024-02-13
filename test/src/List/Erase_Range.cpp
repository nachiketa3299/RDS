/// @file List_Erase_Range_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"

#include <iterator>
#include <list>

using namespace rds;
using namespace std;
using namespace testing;

class List_Erase_Range_int_exit_fixture: public Test
{
protected:
    void SetUp() override
    {
        // 역참조 불가능한 이유가 센티넬 노드를 가리키고 있어서
        no_de_it_a  = List<int>::Iterator(std::addressof(li_a),
                                          std::addressof(li_a.GetSentinel()));
        no_de_cit_a = List<int>::ConstIterator(std::addressof(li_a),
                                               std::addressof(li_a.GetSentinel()));
        // 역참조 불가능한 이유가 유효하지 않아서
        no_de_it_b  = List<int>::Iterator();
        no_de_cit_b = List<int>::ConstIterator();

        // 유효하지 않은 반복자
        no_val_it  = List<int>::Iterator();
        no_val_cit = List<int>::ConstIterator();

        // 호환되지 않는 반복자
        it_pa_begin  = li_a.Begin();
        it_pb_begin  = li_b.Begin();
        cit_pa_begin = li_a.CBegin();
        cit_pb_begin = li_b.CBegin();

        it_pa_end  = li_a.End();
        it_pb_end  = li_b.End();
        cit_pa_end = li_a.CEnd();
        cit_pb_end = li_b.CEnd();
    }

    List<int> li_a{0, 1, 2};
    List<int> li_b{0, 1, 2};

    List<int>::Iterator no_de_it_a;
    List<int>::Iterator no_de_it_b;

    List<int>::ConstIterator no_de_cit_a;
    List<int>::ConstIterator no_de_cit_b;

    List<int>::Iterator      no_val_it;
    List<int>::ConstIterator no_val_cit;

    List<int>::Iterator      it_pa_begin;
    List<int>::Iterator      it_pb_begin;
    List<int>::ConstIterator cit_pa_begin;
    List<int>::ConstIterator cit_pb_begin;

    List<int>::Iterator      it_pa_end;
    List<int>::Iterator      it_pb_end;
    List<int>::ConstIterator cit_pa_end;
    List<int>::ConstIterator cit_pb_end;
};

// TEST(List_STL_erase, Basic)
// {
//     list<int> li{0, 1, 2};
//     li.erase(li.begin(), li.end());   // no problem, absolutely.
//     li.erase(li.cbegin(), li.cend()); // no problem, also.
//     li.erase(li.begin(), li.cend());  // wtf?? no problem
//     li.erase(--li.end(), li.begin()); // has fucking big problem but "silent"
//     li.erase(li.end());               // has noisy problem
// }

#define RDS_EXPECT_EXIT_FAILURE(Expression)                                            \
    EXPECT_EXIT(Expression, ExitedWithCode(EXIT_FAILURE), "")

/// @brief 역참조 불가능한 `it_first` 반복자에 대해서 비정상 종료하는지 확인
TEST_F(List_Erase_Range_int_exit_fixture, exit_first_ndref)
{
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(no_de_it_a, li_a.End()));
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(no_de_it_b, li_a.End()));

    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(no_de_cit_a, li_a.CEnd()));
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(no_de_cit_b, li_a.CEnd()));
}

/// @brief 유효하지 않은 `it_last` 반복자에 대해서 비정상 종료하는지 확인
TEST_F(List_Erase_Range_int_exit_fixture, exit_last_nvalid)
{
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(li_a.Begin(), no_val_it));
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(li_a.CBegin(), no_val_cit));
}

/// @brief `it_first` 가 리스트와 호환되지 않는 경우 비정상 종료하는지 확인
TEST_F(List_Erase_Range_int_exit_fixture, exit_first_ncomp)
{
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(it_pb_begin, li_a.End()));
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(cit_pb_begin, li_a.CEnd()));

    RDS_EXPECT_EXIT_FAILURE(li_b.Erase(it_pa_begin, li_b.End()));
    RDS_EXPECT_EXIT_FAILURE(li_b.Erase(cit_pa_begin, li_b.CEnd()));
}

/// @brief `it_last`가 리스트와 호환되지 않는 경우 비정상 종료하는지 확인
TEST_F(List_Erase_Range_int_exit_fixture, exit_last_ncomp)
{
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(li_a.Begin(), it_pb_end));
    RDS_EXPECT_EXIT_FAILURE(li_a.Erase(li_a.CBegin(), cit_pb_end));

    RDS_EXPECT_EXIT_FAILURE(li_b.Erase(li_b.Begin(), it_pa_end));
    RDS_EXPECT_EXIT_FAILURE(li_b.Erase(li_b.CBegin(), cit_pa_end));
}

/// @brief `it_first`와 `it_last` 가 같아서, 빠르게 반복자를 반환하는 경우 제대로
/// 반환하는지 확인
TEST(List_Erase_Range, first_last_eq_fast_return)
{
    List<int> li{0};
    auto      it_pivot  = li.Begin();
    auto      cit_pivot = li.CBegin();

    EXPECT_TRUE(it_pivot.operator==(li.Erase(li.Begin(), li.Begin())));
    EXPECT_TRUE(cit_pivot.operator==(li.Erase(li.Begin(), li.Begin())));

    EXPECT_TRUE(it_pivot.operator==(li.Erase(li.CBegin(), li.Begin())));
    EXPECT_TRUE(cit_pivot.operator==(li.Erase(li.CBegin(), li.Begin())));

    EXPECT_TRUE(it_pivot.operator==(li.Erase(li.Begin(), li.CBegin())));
    EXPECT_TRUE(cit_pivot.operator==(li.Erase(li.Begin(), li.CBegin())));

    EXPECT_TRUE(it_pivot.operator==(li.Erase(li.CBegin(), li.CBegin())));
    EXPECT_TRUE(cit_pivot.operator==(li.Erase(li.CBegin(), li.CBegin())));
}

/// @brief 기본적인 사용례 테스트
TEST(List_Erase_Range, basic_test)
{
    List<int> li_a     = {0, 1, 2, 3, 4};
    auto      real_end = li_a.End();
    auto      ret_it   = li_a.Erase(++li_a.Begin(), li_a.End());

    EXPECT_TRUE(real_end == ret_it);
    EXPECT_EQ(li_a.Size(), 1);

    // li = List<int>({0, 1, 2, 3, 4}); 이러면 어떻게 되지?
    List<int> li_b = {0, 1, 2, 3, 4};
    EXPECT_TRUE(li_b.End() == li_b.Erase(li_b.Begin(), li_b.End()));
    EXPECT_EQ(li_b.Size(), 0);
}

/// @brief 정의되지 않은 행동
TEST(List_Erase_Range, undefined_behaviour)
{
    List<int> li = {0, 1, 2, 3, 4};
    // li.Erase(--li.End(), li.Begin()); // 리스트 노드를 삭제하려고 하기 때문에
    // 오류 난다
}

#undef RDS_EXPECT_EXIT_FAILURE