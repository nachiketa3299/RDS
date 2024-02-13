/// @file List_Compare_Equality_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"

using namespace rds;
using namespace testing;

class List_EqualityCompare_int_fixture: public Test
{
protected:
    List<int> il_s0_a{};
    List<int> il_s0_b{};
    List<int> il_s1_a{1};
    List<int> il_s1_b{1};
    List<int> il_s1_c{2};
    List<int> il_s5_a{1, 2, 3, 4, 5};
    List<int> il_s5_b{1, 2, 3, 4, 5};
    List<int> il_s5_c{1, 2, 9, 4, 5};
};

/// @brief 두 리스트의 `operator==` 연산자 오버로딩을 테스트하는 매크로
#define RDS_LIST_EQ_TEST(List_a, List_b, Expected)                                     \
    {                                                                                  \
        EXPECT_EQ(List_a.operator==(List_b), Expected);                                \
        EXPECT_EQ(List_b.operator==(List_a), Expected);                                \
        EXPECT_EQ(List_a == List_b, Expected);                                         \
        EXPECT_EQ(List_b == List_a, Expected);                                         \
    }

/// @brief 두 리스트의 크기가 다를 때, 항상 false 를 반환하는지 확인
TEST_F(List_EqualityCompare_int_fixture, size_neq_eq_afalse)
{
    RDS_LIST_EQ_TEST(il_s0_a, il_s1_a, false);
}

/// @brief 두 리스트의 크기가 같고 크기가 0일 때, 항상 true를 반환하는지 확인
TEST_F(List_EqualityCompare_int_fixture, size_eq0_eq_atrue)
{
    RDS_LIST_EQ_TEST(il_s0_a, il_s0_b, true);
}

/// @brief 두 리스트의 크기가 같고 크기가 0이 아닐 때, true 를 반환하는 경우
TEST_F(List_EqualityCompare_int_fixture, size_eqn0_eq_ctrue)
{
    RDS_LIST_EQ_TEST(il_s1_a, il_s1_b, true);
    RDS_LIST_EQ_TEST(il_s5_a, il_s5_b, true);
}

/// @brief 두 리스트의 크기가 같고 크기가 0이 아닐 때, flase 를 반환하는 경우
TEST_F(List_EqualityCompare_int_fixture, size_eqn0_eq_cfalse)
{
    RDS_LIST_EQ_TEST(il_s1_a, il_s1_c, false);
    RDS_LIST_EQ_TEST(il_s5_a, il_s5_c, false);
}

class LE_UD
{
    int  a{};
    char c{'a'};

public:
    LE_UD() = default;

    LE_UD(int a)
        : a(a)
    {}

public:
    bool operator==(const LE_UD& other) const
    {
        return a == other.a;
    }
};

class List_EqualityCompare_UD_fixture: public Test
{
protected:
    List<LE_UD> UDl_s0_a{};
    List<LE_UD> UDl_s0_b{};
    List<LE_UD> UDl_s1_a{{1}};
    List<LE_UD> UDl_s1_b{{1}};
    List<LE_UD> UDl_s1_c{{2}};
    List<LE_UD> UDl_s5_a{{1}, {2}, {3}, {4}, {5}};
    List<LE_UD> UDl_s5_b{{1}, {2}, {3}, {4}, {5}};
    List<LE_UD> UDl_s5_c{{1}, {2}, {9}, {4}, {5}};
};

/// @brief 사용자 정의 자료형에 대해, 두 리스트의 크기가 다를 때, 항상 false 를
/// 반환하는지 확인
TEST_F(List_EqualityCompare_UD_fixture, size_neq_eq_afalse)
{
    RDS_LIST_EQ_TEST(UDl_s0_a, UDl_s1_a, false);
}

/// @brief 사용자 정의 자료형에 대해, 두 리스트의 크기가 같고 크기가 0일 때, 항상 true를
/// 반환하는지 확인
TEST_F(List_EqualityCompare_UD_fixture, size_eq0_eq_atrue)
{
    RDS_LIST_EQ_TEST(UDl_s0_a, UDl_s0_b, true);
}

/// @brief 사용자 정의 자료형에 대해, 두 리스트의 크기가 같고 크기가 0이 아닐 때, true
/// 를 반환하는 경우
TEST_F(List_EqualityCompare_UD_fixture, size_eqn0_eq_ctrue)
{
    RDS_LIST_EQ_TEST(UDl_s1_a, UDl_s1_b, true);
    RDS_LIST_EQ_TEST(UDl_s5_a, UDl_s5_b, true);
}

/// @brief 사용자 정의 자료형에 대해, 두 리스트의 크기가 같고 크기가 0이 아닐 때, flase
/// 를 반환하는 경우
TEST_F(List_EqualityCompare_UD_fixture, size_eqn0_eq_cfalse)
{
    RDS_LIST_EQ_TEST(UDl_s1_a, UDl_s1_c, false);
    RDS_LIST_EQ_TEST(UDl_s5_a, UDl_s5_c, false);
}

#undef RDS_LIST_EQ_TEST
