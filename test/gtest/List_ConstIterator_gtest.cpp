#include <gtest/gtest.h>

#include <list>
#include <type_traits>

#include "List.hpp"
#include "List_ConstIterator.hpp"

class NonEmptyIntListAccess: public ::testing::Test
{
protected:
    void SetUp() override
    {}

    rds::List<int>       P_int_ne{10, 11, 12, 13};
    const rds::List<int> C_int_ne{10, 11, 12, 13};
};

// 간단한 역참조 연산자 테스트
// End/CEnd 는 마지막 원소를 가리키고 있어선 안된다.
TEST_F(NonEmptyIntListAccess, PC_BeginEndCBeginCEnd_deref)
{
    EXPECT_EQ(*P_int_ne.Begin(), 10);
    EXPECT_NE(*P_int_ne.End(), 13);

    EXPECT_EQ(*C_int_ne.Begin(), 10);
    EXPECT_NE(*C_int_ne.End(), 13);

    EXPECT_EQ(*P_int_ne.CBegin(), 10);
    EXPECT_NE(*P_int_ne.CEnd(), 13);

    EXPECT_EQ(*C_int_ne.CBegin(), 10);
    EXPECT_NE(*C_int_ne.CEnd(), 13);

    EXPECT_EQ(P_int_ne.Begin().operator*(), 10);
    EXPECT_NE(P_int_ne.End().operator*(), 13);

    EXPECT_EQ(C_int_ne.Begin().operator*(), 10);
    EXPECT_NE(C_int_ne.End().operator*(), 13);

    EXPECT_EQ(P_int_ne.CBegin().operator*(), 10);
    EXPECT_NE(P_int_ne.CEnd().operator*(), 13);

    EXPECT_EQ(C_int_ne.CBegin().operator*(), 10);
    EXPECT_NE(C_int_ne.CEnd().operator*(), 13);
}

// 일반 리스트와 상수 리스트에 대해서 Begin을 호출했을 때 어떤 타입의 반복자가
// 생성되는지 테스트
// 일반 리스트에서 Begin/End을 호출하면 Iterator가 생성되어야 함
// 상수 리스트에서 Begin/End을 호출하면 ConstIterator가 생성되어야함
// 일반 리스트에서 CBegin/CEnd을 호출하면 ConstIterator가 생성되어야 함
// 상수 리스트에서 CBegin/CEnd을 호출하면 ConstIterator가 생성되어야함
TEST_F(NonEmptyIntListAccess, PC_BeginEndCBeginCEnd_type)
{
    using PlainList_Begin_t  = decltype(P_int_ne.Begin());
    using ConstList_Begin_t  = decltype(C_int_ne.Begin());
    using PlainList_End_t    = decltype(P_int_ne.End());
    using ConstList_End_t    = decltype(C_int_ne.End());
    using PlainList_CBegin_t = decltype(P_int_ne.CBegin());
    using ConstList_CBegin_t = decltype(C_int_ne.CBegin());
    using PlainList_CEnd_t   = decltype(P_int_ne.CEnd());
    using ConstList_CEnd_t   = decltype(C_int_ne.CEnd());
    using Iterator_t         = rds::List<int>::Iterator;
    using ConstIterator_t    = rds::List<int>::ConstIterator;

    constexpr bool is_pl_b_it  = std::is_same_v<PlainList_Begin_t, Iterator_t>;
    constexpr bool is_pl_b_cit = std::is_same_v<PlainList_Begin_t, ConstIterator_t>;
    constexpr bool is_cl_b_it  = std::is_same_v<ConstList_Begin_t, Iterator_t>;
    constexpr bool is_cl_b_cit = std::is_same_v<ConstList_Begin_t, ConstIterator_t>;

    constexpr bool is_pl_e_it  = std::is_same_v<PlainList_End_t, Iterator_t>;
    constexpr bool is_pl_e_cit = std::is_same_v<PlainList_End_t, ConstIterator_t>;
    constexpr bool is_cl_e_it  = std::is_same_v<ConstList_End_t, Iterator_t>;
    constexpr bool is_cl_e_cit = std::is_same_v<ConstList_End_t, ConstIterator_t>;

    constexpr bool is_pl_cb_it  = std::is_same_v<PlainList_CBegin_t, Iterator_t>;
    constexpr bool is_pl_cb_cit = std::is_same_v<PlainList_CBegin_t, ConstIterator_t>;
    constexpr bool is_cl_cb_it  = std::is_same_v<ConstList_CBegin_t, Iterator_t>;
    constexpr bool is_cl_cb_cit = std::is_same_v<ConstList_CBegin_t, ConstIterator_t>;

    constexpr bool is_pl_ce_it  = std::is_same_v<PlainList_CEnd_t, Iterator_t>;
    constexpr bool is_pl_ce_cit = std::is_same_v<PlainList_CEnd_t, ConstIterator_t>;
    constexpr bool is_cl_ce_it  = std::is_same_v<ConstList_CEnd_t, Iterator_t>;
    constexpr bool is_cl_ce_cit = std::is_same_v<ConstList_CEnd_t, ConstIterator_t>;

    // [T] 일반 리스트의 Begin이 Iterator 인가?
    EXPECT_TRUE(is_pl_b_it);
    // [F] 일반 리스트의 Begin이 ConstIterator 인가?
    EXPECT_FALSE(is_pl_b_cit);
    // [F] 상수 리스트의 Begin이 Iterator 인가?
    EXPECT_FALSE(is_cl_b_it);
    // [T] 상수 리스트의 Begin이 ConstIterator 인가?
    EXPECT_TRUE(is_cl_b_cit);

    // [T] 일반 리스트의 End이 Iterator 인가?
    EXPECT_TRUE(is_pl_e_it);
    // [F] 일반 리스트의 End이 ConstIterator 인가?
    EXPECT_FALSE(is_pl_e_cit);
    // [F] 상수 리스트의 End이 Iterator 인가?
    EXPECT_FALSE(is_cl_e_it);
    // [T] 상수 리스트의 End이 ConstIterator 인가?
    EXPECT_TRUE(is_cl_e_cit);

    // [F] 일반 리스트의 CBegin이 Iterator인가?
    EXPECT_FALSE(is_pl_cb_it);
    // [T] 일반 리스트의 CBegin이 ConstIterator인가?
    EXPECT_TRUE(is_pl_cb_cit);
    // [F] 상수 리스트의 CBegin이 Iterator인가?
    EXPECT_FALSE(is_cl_cb_it);
    // [T] 상수 리스트의 CBegin이 ConstIterator인가?
    EXPECT_TRUE(is_cl_cb_cit);

    // [F] 일반 리스트의 CEnd이 Iterator인가?
    EXPECT_FALSE(is_pl_ce_it);
    // [T] 일반 리스트의 CEnd이 ConstIterator인가?
    EXPECT_TRUE(is_pl_ce_cit);
    // [F] 상수 리스트의 CEnd이 Iterator인가?
    EXPECT_FALSE(is_cl_ce_it);
    // [T] 상수 리스트의 CEnd이 ConstIterator인가?
    EXPECT_TRUE(is_cl_ce_cit);
}

TEST_F(NonEmptyIntListAccess, PC_BeginEndCBeginCEnd_op_preinc)
{
    EXPECT_EQ(*P_int_ne.Begin(), 10);
    EXPECT_EQ(*++P_int_ne.Begin(), 11);
    EXPECT_EQ(*++ ++P_int_ne.Begin(), 12);
    EXPECT_EQ(*++ ++ ++P_int_ne.Begin(), 13);
    EXPECT_NE(*++ ++ ++ ++P_int_ne.Begin(), 10);

    // 명시적으로 호출
    EXPECT_EQ(P_int_ne.Begin().operator*(), 10);
    EXPECT_EQ(P_int_ne.Begin().operator++().operator*(), 11);
    EXPECT_EQ(P_int_ne.Begin().operator++().operator++().operator*(), 12);
    EXPECT_EQ(P_int_ne.Begin().operator++().operator++().operator++().operator*(), 13);
}