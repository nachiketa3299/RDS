#include "List.hpp"
#include "RDT_CoreDefs.h"
#include <gtest/gtest.h>

// clang-format off
/*!
    @todo 단순히 List 컨테이너에만 적용되는 테스트가 아니라서 확장할 수도 있을 것 같다.
    @todo 지금은 기본 자료형에 대해서만 테스트하지만, 사용자 정의 자료형도 추가할 것
    @todo 마크다운으로 테스트 항목들을 조금만 정리할 것
*/
// clang-format on

// clang-format off
/*
================================================================================
각 메서드 별로 테스트해야 할 것은 아래와 같다.
(의존성이 없는 메서드부터 위에서부터 아래로 테스트를 진행한다.)
--------------------------------------------------------------------------------
- [Helper]         IsValid()                   const -> bool
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자: `false`
    * {Empty/NEmpty} 리스트에 대한 {begin/end/cbegin/cend}: `true`
--------------------------------------------------------------------------------
- [Helper]         IsDereferencible()          const -> bool
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자: `false`
    * {Empty} 리스트에 대한 {begin/cbegin}: `false`
    * {NEmpty} 리스트에 대한 {begin/cbegin}: `true`
    * {Empty/NEmpty} 리스트에 대한 {end/cend}: `false`
--------------------------------------------------------------------------------
- [Dereference]    operator*()                 const -> T_t&
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자: Assertion Failed 확인
    * {Empty} 리스트에 대한 {begin/cbegin}: Assertion Failed 확인
    * {NEmpty} 리스트에 대한 {begin/cbegin}: 반환값 확인
    * {Empty/NEmpty} 리스트에 대한 {end/cend}: Assertion Failed 확인
--------------------------------------------------------------------------------
- [Arrow]          operator->()                const -> T_t*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자: Assertion Failed 확인
    * {Empty} 리스트에 대한 {begin/cbegin}: Assertion Failed 확인
    * {NEmpty} 리스트에 대한 {begin/cbegin}: 반환값 확인
    * {Empty/NEmpty} 리스트에 대한 {end/cend}: Assertion Failed 확인
--------------------------------------------------------------------------------
- [Helper]         IsCompatible(const List_t&) const -> bool
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자({Empty/NEmpty} 리스트): `false`
    * {Empty/NEmpty} 리스트에 대한 {begin/end/cbegin/cend}(동일한 리스트): `true`
    * {Empty/NEmpty} 리스트에 대한 {begin/end/cbegin/cend}(다른 리스트): `false`
--------------------------------------------------------------------------------
- [Equality]       operator==(const Iterator&) const -> bool
- [Inequality]     operator!=(const Iterator&) const -> bool
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 반복자들끼리의 상수성과 관계 없는 동등성 비교
    * (같은/다른) 리스트의 (같은/다른) 위치를 가리키는 (일반/상수) 반복자들의
      동등성 비교
--------------------------------------------------------------------------------
- [Data Access]    GetDataPointer()            const -> const Node_D_t*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 {일반/상수} 반복자: `nullptr`
    * {Empty} 리스트에 대한 {begin/end/cbegin/cend}: 아마 센티넬 노드가 나올 듯
    * {NEmpty} 리스트에 대한 {begin/cbegin}: 리스트의 첫 번째 노드의 주소
    * {NEmpty} 리스트에 대한 {end/cend}: 아마 센티넬 노드가 나올 듯
--------------------------------------------------------------------------------
- [Pre-Increment]  operator++()                      -> Iterator&
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 반복자: Assertion Failed 확인
    * {Empty} 리스트에 대해 {begin/cbegin/end/cend}: Assertion Failed 확인
    * {NEmpty} 리스트에 대해 {begin/cbegin}: 반환값 사이즈만큼 확인
    * {NEmpty} 리스트에 대해 {end/cend}: Assertion Failed 확인
--------------------------------------------------------------------------------
- [Pre-Decrement]  operator--()                      -> Iterator&
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 기본 초기화된 반복자: Assertion Failed 확인
    * {Empty} 리스트에 대해 {begin/cbegin/end/cend}: Assertion Failed 확인
    * {NEmpty} 리스트에 대해 {begin/cbegin}: Assertion Failed 확인
    * {NEmpty} 리스트에 대해 {end/cend}: 반환값 사이즈만큼 확인
--------------------------------------------------------------------------------
- [Post-Increment] operator++(int)                   -> Iterator
- [Post-Decrement] operator--(int)                   -> Iterator
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * 각각의 전위 연산자 버전과 동일하되, 복사본으로서 수행되는지 확인
--------------------------------------------------------------------------------
*/
// clang-format on

RDT_BEGIN

using namespace std;
using namespace rds;
using GT_INTEGERS = cxx_fundamental_GTestTypes::integers;
using GT_BOOLEANS = cxx_fundamental_GTestTypes::booleans;
using GT_CHARS    = cxx_fundamental_GTestTypes::characters;
using GT_FLOATS   = cxx_fundamental_GTestTypes::floating_points;

template <class T_t>
class Iterators: public testing::Test
{
protected:
    void SetUp() override
    {
        // clang-format off
        it_default   = typename List<T_t>::Iterator_t();
        c_it_default = typename List<T_t>::Const_Iterator_t();
        it_default_a   = typename List<T_t>::Iterator_t();
        c_it_default_a = typename List<T_t>::Const_Iterator_t();

        e_it_begin = Empty_list.Begin();
        e_it_begin_const = const_cast<const List<T_t>&>(Empty_list).Begin();
        e_it_cbegin = Empty_list.CBegin();
        e_it_cbegin_const = const_cast<const List<T_t>&>(Empty_list).CBegin();

        ne_it_begin = NEmpty_list.Begin();
        ne_it_begin_const = const_cast<const List<T_t>&>(NEmpty_list).Begin();
        ne_it_cbegin = NEmpty_list.CBegin();
        ne_it_cbegin_const = const_cast<const List<T_t>&>(NEmpty_list).CBegin();

        e_it_end = Empty_list.End();
        e_it_end_const = const_cast<const List<T_t>&>(Empty_list).End();
        e_it_cend = Empty_list.CEnd();
        e_it_cend_const = const_cast<const List<T_t>&>(Empty_list).CEnd();

        ne_it_end = NEmpty_list.End();
        ne_it_end_const = const_cast<const List<T_t>&>(NEmpty_list).End();
        ne_it_cend = NEmpty_list.CEnd();
        ne_it_cend_const = const_cast<const List<T_t>&>(NEmpty_list).CEnd();

        e_it_begin_a = Empty_list_a.Begin();
        e_it_begin_const_a = const_cast<const List<T_t>&>(Empty_list_a).Begin();
        e_it_cbegin_a = Empty_list_a.CBegin();
        e_it_cbegin_const_a = const_cast<const List<T_t>&>(Empty_list_a).CBegin();

        ne_it_begin_a = NEmpty_list_a.Begin();
        ne_it_begin_const_a = const_cast<const List<T_t>&>(NEmpty_list_a).Begin();
        ne_it_cbegin_a = NEmpty_list_a.CBegin();
        ne_it_cbegin_const_a = const_cast<const List<T_t>&>(NEmpty_list_a).CBegin();

        e_it_end_a = Empty_list_a.End();
        e_it_end_const_a = const_cast<const List<T_t>&>(Empty_list_a).End();
        e_it_cend_a = Empty_list_a.CEnd();
        e_it_cend_const_a = const_cast<const List<T_t>&>(Empty_list_a).CEnd();

        ne_it_end_a = NEmpty_list_a.End();
        ne_it_end_const_a = const_cast<const List<T_t>&>(NEmpty_list_a).End();
        ne_it_cend_a = NEmpty_list_a.CEnd();
        ne_it_cend_const_a = const_cast<const List<T_t>&>(NEmpty_list_a).CEnd();
        // clang-format on
    }

protected:
    inline static const T_t e0 = T_t{0};
    inline static const T_t e1 = T_t{1};

protected:
    List<T_t> Empty_list;
    List<T_t> NEmpty_list{e0, e1};

    List<T_t> Empty_list_a;
    List<T_t> NEmpty_list_a{e0, e1};

protected:
    typename List<T_t>::Iterator_t       it_default;
    typename List<T_t>::Const_Iterator_t c_it_default;
    typename List<T_t>::Iterator_t       it_default_a;
    typename List<T_t>::Const_Iterator_t c_it_default_a;

    // clang-format off
protected:
    typename List<T_t>::Iterator_t       e_it_begin;
    typename List<T_t>::Const_Iterator_t e_it_begin_const;
    typename List<T_t>::Const_Iterator_t e_it_cbegin;
    typename List<T_t>::Const_Iterator_t e_it_cbegin_const;

    typename List<T_t>::Iterator_t       ne_it_begin;
    typename List<T_t>::Const_Iterator_t ne_it_begin_const;
    typename List<T_t>::Const_Iterator_t ne_it_cbegin;
    typename List<T_t>::Const_Iterator_t ne_it_cbegin_const;

    typename List<T_t>::Iterator_t       e_it_end;
    typename List<T_t>::Const_Iterator_t e_it_end_const;
    typename List<T_t>::Const_Iterator_t e_it_cend;
    typename List<T_t>::Const_Iterator_t e_it_cend_const;

    typename List<T_t>::Iterator_t       ne_it_end;
    typename List<T_t>::Const_Iterator_t ne_it_end_const;
    typename List<T_t>::Const_Iterator_t ne_it_cend;
    typename List<T_t>::Const_Iterator_t ne_it_cend_const;

    /* Alternative */

    typename List<T_t>::Iterator_t       e_it_begin_a;
    typename List<T_t>::Const_Iterator_t e_it_begin_const_a;
    typename List<T_t>::Const_Iterator_t e_it_cbegin_a;
    typename List<T_t>::Const_Iterator_t e_it_cbegin_const_a;

    typename List<T_t>::Iterator_t       ne_it_begin_a;
    typename List<T_t>::Const_Iterator_t ne_it_begin_const_a;
    typename List<T_t>::Const_Iterator_t ne_it_cbegin_a;
    typename List<T_t>::Const_Iterator_t ne_it_cbegin_const_a;

    typename List<T_t>::Iterator_t       e_it_end_a;
    typename List<T_t>::Const_Iterator_t e_it_end_const_a;
    typename List<T_t>::Const_Iterator_t e_it_cend_a;
    typename List<T_t>::Const_Iterator_t e_it_cend_const_a;

    typename List<T_t>::Iterator_t       ne_it_end_a;
    typename List<T_t>::Const_Iterator_t ne_it_end_const_a;
    typename List<T_t>::Const_Iterator_t ne_it_cend_a;
    typename List<T_t>::Const_Iterator_t ne_it_cend_const_a;
    // clang-format on
};

TYPED_TEST_SUITE_P(Iterators);

TYPED_TEST_P(Iterators, IsValid_Default)
{
    EXPECT_FALSE(this->it_default.IsValid());
    EXPECT_FALSE(this->c_it_default.IsValid());
}

TYPED_TEST_P(Iterators, IsValid_ENE)
{
    // clang-format off
    EXPECT_TRUE(this->e_it_begin.IsValid());
    EXPECT_TRUE(this->e_it_begin_const.IsValid());
    EXPECT_TRUE(this->e_it_cbegin.IsValid());
    EXPECT_TRUE(this->e_it_cbegin_const.IsValid());

    EXPECT_TRUE(this->ne_it_begin.IsValid());
    EXPECT_TRUE(this->ne_it_begin_const.IsValid());
    EXPECT_TRUE(this->ne_it_cbegin.IsValid());
    EXPECT_TRUE(this->ne_it_cbegin_const.IsValid());

    EXPECT_TRUE(this->e_it_end.IsValid());
    EXPECT_TRUE(this->e_it_end_const.IsValid());
    EXPECT_TRUE(this->e_it_cend.IsValid());
    EXPECT_TRUE(this->e_it_cend_const.IsValid());

    EXPECT_TRUE(this->ne_it_end.IsValid());
    EXPECT_TRUE(this->ne_it_end_const.IsValid());
    EXPECT_TRUE(this->ne_it_cend.IsValid());
    EXPECT_TRUE(this->ne_it_cend_const.IsValid());
    // clang-format on
}

TYPED_TEST_P(Iterators, IsDereferencible_Default)
{
    EXPECT_FALSE(this->it_default.IsDereferencible());
    EXPECT_FALSE(this->c_it_default.IsDereferencible());
}

TYPED_TEST_P(Iterators, IsDereferencible_ENE)
{
    EXPECT_FALSE(this->e_it_begin.IsDereferencible());
    EXPECT_FALSE(this->e_it_begin_const.IsDereferencible());
    EXPECT_FALSE(this->e_it_cbegin.IsDereferencible());
    EXPECT_FALSE(this->e_it_cbegin_const.IsDereferencible());

    EXPECT_TRUE(this->ne_it_begin.IsDereferencible());
    EXPECT_TRUE(this->ne_it_begin_const.IsDereferencible());
    EXPECT_TRUE(this->ne_it_cbegin.IsDereferencible());
    EXPECT_TRUE(this->ne_it_cbegin_const.IsDereferencible());

    EXPECT_FALSE(this->e_it_end.IsDereferencible());
    EXPECT_FALSE(this->e_it_end_const.IsDereferencible());
    EXPECT_FALSE(this->e_it_cend.IsDereferencible());
    EXPECT_FALSE(this->e_it_cend_const.IsDereferencible());

    EXPECT_FALSE(this->ne_it_end.IsDereferencible());
    EXPECT_FALSE(this->ne_it_end_const.IsDereferencible());
    EXPECT_FALSE(this->ne_it_cend.IsDereferencible());
    EXPECT_FALSE(this->ne_it_cend_const.IsDereferencible());
}

TYPED_TEST_P(Iterators, op_Star_Default)
{
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator*(), "");
}

TYPED_TEST_P(Iterators, op_Start_ENE)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin_const.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin_const.operator*(), "");

    EXPECT_EQ(this->ne_it_begin.operator*(), Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_begin_const.operator*(), Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_cbegin.operator*(), Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_cbegin_const.operator*(), Iterators<TypeParam>::e0);

    RDT_EXPECT_EXIT_FAILURE(this->e_it_end.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end_const.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend_const.operator*(), "");

    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator*(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator*(), "");
    // clang-format on
}

TYPED_TEST_P(Iterators, op_Arrow_Default)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator->(), "");
    // clang-format on
}

TYPED_TEST_P(Iterators, op_Arrow_ENE)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin_const.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin_const.operator->(), "");

    EXPECT_EQ(*this->ne_it_begin.operator->(), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_begin_const.operator->(), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin.operator->(), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin_const.operator->(), Iterators<TypeParam>::e0);

    RDT_EXPECT_EXIT_FAILURE(this->e_it_end.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end_const.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend_const.operator->(), "");

    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator->(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator->(), "");
    // clang-format on
}

TYPED_TEST_P(Iterators, Default_IsCompatible_ENE)
{
    // clang-format off
    EXPECT_FALSE(this->it_default.IsCompatible(this->Empty_list));
    EXPECT_FALSE(this->it_default.IsCompatible(this->NEmpty_list));
    EXPECT_FALSE(this->c_it_default.IsCompatible(this->Empty_list));
    EXPECT_FALSE(this->c_it_default.IsCompatible(this->NEmpty_list));
    // clang-format on
}

TYPED_TEST_P(Iterators, ENE_IsCompatible_ENE)
{
    // clang-format off
    EXPECT_TRUE(this->e_it_begin.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_begin_const.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_cbegin.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_cbegin_const.IsCompatible(this->Empty_list));

    EXPECT_TRUE(this->ne_it_begin.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_begin_const.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_cbegin.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_cbegin_const.IsCompatible(this->NEmpty_list));

    EXPECT_TRUE(this->e_it_end.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_end_const.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_cend.IsCompatible(this->Empty_list));
    EXPECT_TRUE(this->e_it_cend_const.IsCompatible(this->Empty_list));

    EXPECT_TRUE(this->ne_it_end.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_end_const.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_cend.IsCompatible(this->NEmpty_list));
    EXPECT_TRUE(this->ne_it_cend_const.IsCompatible(this->NEmpty_list));
    // clang-format on
}

TYPED_TEST_P(Iterators, ENE_IsCompatible_ENE_a)
{
    // clang-format off
    EXPECT_FALSE(this->e_it_begin.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_begin_const.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_cbegin.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_cbegin_const.IsCompatible(this->Empty_list_a));

    EXPECT_FALSE(this->ne_it_begin.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_begin_const.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_cbegin.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_cbegin_const.IsCompatible(this->NEmpty_list_a));

    EXPECT_FALSE(this->e_it_end.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_end_const.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_cend.IsCompatible(this->Empty_list_a));
    EXPECT_FALSE(this->e_it_cend_const.IsCompatible(this->Empty_list_a));

    EXPECT_FALSE(this->ne_it_end.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_end_const.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_cend.IsCompatible(this->NEmpty_list_a));
    EXPECT_FALSE(this->ne_it_cend_const.IsCompatible(this->NEmpty_list_a));
    // clang-format on
}

TYPED_TEST_P(Iterators, Default_op_Equality_Default)
{
    // clang-format off
    EXPECT_TRUE(this->it_default.operator==(this->it_default));
    EXPECT_TRUE(this->it_default.operator==(this->c_it_default));
    EXPECT_TRUE(this->it_default.operator==(this->it_default_a));
    EXPECT_TRUE(this->it_default.operator==(this->c_it_default_a));

    EXPECT_TRUE(this->c_it_default.operator==(this->it_default));
    EXPECT_TRUE(this->c_it_default.operator==(this->c_it_default));
    EXPECT_TRUE(this->c_it_default.operator==(this->it_default_a));
    EXPECT_TRUE(this->c_it_default.operator==(this->c_it_default_a));
    // clang-format on
}

TYPED_TEST_P(Iterators, Default_op_Equality_ENE)
{
    // clang-format on
    EXPECT_FALSE(this->it_default.operator==(this->e_it_begin));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_begin_const));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_cbegin));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_cbegin_const));

    EXPECT_FALSE(this->it_default.operator==(this->ne_it_begin));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_begin_const));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_cbegin));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_cbegin_const));

    EXPECT_FALSE(this->it_default.operator==(this->e_it_end));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_end_const));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_cend));
    EXPECT_FALSE(this->it_default.operator==(this->e_it_cend_const));

    EXPECT_FALSE(this->it_default.operator==(this->ne_it_end));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_end_const));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_cend));
    EXPECT_FALSE(this->it_default.operator==(this->ne_it_cend_const));

    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_begin));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_begin_const));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_cbegin));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_cbegin_const));

    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_begin));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_begin_const));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_cbegin));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_cbegin_const));

    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_end));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_end_const));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_cend));
    EXPECT_FALSE(this->c_it_default.operator==(this->e_it_cend_const));

    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_end));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_end_const));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_cend));
    EXPECT_FALSE(this->c_it_default.operator==(this->ne_it_cend_const));
}

TYPED_TEST_P(Iterators, ENE_op_Equality_Default)
{
    // clang-format off
    EXPECT_FALSE(this->e_it_begin.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_begin_const.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_cbegin.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->it_default));

    EXPECT_FALSE(this->e_it_begin.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_begin_const.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_cbegin.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->c_it_default));

    EXPECT_FALSE(this->ne_it_begin.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->it_default));

    EXPECT_FALSE(this->ne_it_begin.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->c_it_default));

    EXPECT_FALSE(this->e_it_end.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_end_const.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_cend.operator==(this->it_default));
    EXPECT_FALSE(this->e_it_cend_const.operator==(this->it_default));

    EXPECT_FALSE(this->e_it_end.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_end_const.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_cend.operator==(this->c_it_default));
    EXPECT_FALSE(this->e_it_cend_const.operator==(this->c_it_default));

    EXPECT_FALSE(this->ne_it_end.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_end_const.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_cend.operator==(this->it_default));
    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->it_default));

    EXPECT_FALSE(this->ne_it_end.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_end_const.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_cend.operator==(this->c_it_default));
    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->c_it_default));
}
TYPED_TEST_P(Iterators, ENE_op_Equality_ENE)
{
    // clang-format off
    EXPECT_TRUE(this->e_it_begin.operator==(this->e_it_begin));
    EXPECT_TRUE(this->e_it_begin.operator==(this->e_it_begin_const));
    EXPECT_TRUE(this->e_it_begin.operator==(this->e_it_cbegin));
    EXPECT_TRUE(this->e_it_begin.operator==(this->e_it_cbegin_const));

    EXPECT_TRUE(this->e_it_begin_const.operator==(this->e_it_begin));
    EXPECT_TRUE(this->e_it_begin_const.operator==(this->e_it_begin_const));
    EXPECT_TRUE(this->e_it_begin_const.operator==(this->e_it_cbegin));
    EXPECT_TRUE(this->e_it_begin_const.operator==(this->e_it_cbegin_const));

    EXPECT_TRUE(this->e_it_cbegin.operator==(this->e_it_begin));
    EXPECT_TRUE(this->e_it_cbegin.operator==(this->e_it_begin_const));
    EXPECT_TRUE(this->e_it_cbegin.operator==(this->e_it_cbegin));
    EXPECT_TRUE(this->e_it_cbegin.operator==(this->e_it_cbegin_const));

    EXPECT_TRUE(this->e_it_cbegin_const.operator==(this->e_it_begin));
    EXPECT_TRUE(this->e_it_cbegin_const.operator==(this->e_it_begin_const));
    EXPECT_TRUE(this->e_it_cbegin_const.operator==(this->e_it_cbegin));
    EXPECT_TRUE(this->e_it_cbegin_const.operator==(this->e_it_cbegin_const));

    EXPECT_TRUE(this->ne_it_begin.operator==(this->ne_it_begin));
    EXPECT_TRUE(this->ne_it_begin.operator==(this->ne_it_begin_const));
    EXPECT_TRUE(this->ne_it_begin.operator==(this->ne_it_cbegin));
    EXPECT_TRUE(this->ne_it_begin.operator==(this->ne_it_cbegin_const));

    EXPECT_TRUE(this->ne_it_begin_const.operator==(this->ne_it_begin));
    EXPECT_TRUE(this->ne_it_begin_const.operator==(this->ne_it_begin_const));
    EXPECT_TRUE(this->ne_it_begin_const.operator==(this->ne_it_cbegin));
    EXPECT_TRUE(this->ne_it_begin_const.operator==(this->ne_it_cbegin_const));

    EXPECT_TRUE(this->ne_it_cbegin.operator==(this->ne_it_begin));
    EXPECT_TRUE(this->ne_it_cbegin.operator==(this->ne_it_begin_const));
    EXPECT_TRUE(this->ne_it_cbegin.operator==(this->ne_it_cbegin));
    EXPECT_TRUE(this->ne_it_cbegin.operator==(this->ne_it_cbegin_const));

    EXPECT_TRUE(this->ne_it_cbegin_const.operator==(this->ne_it_begin));
    EXPECT_TRUE(this->ne_it_cbegin_const.operator==(this->ne_it_begin_const));
    EXPECT_TRUE(this->ne_it_cbegin_const.operator==(this->ne_it_cbegin));
    EXPECT_TRUE(this->ne_it_cbegin_const.operator==(this->ne_it_cbegin_const));

    EXPECT_TRUE(this->e_it_end.operator==(this->e_it_end));
    EXPECT_TRUE(this->e_it_end.operator==(this->e_it_end_const));
    EXPECT_TRUE(this->e_it_end.operator==(this->e_it_cend));
    EXPECT_TRUE(this->e_it_end.operator==(this->e_it_cend_const));

    EXPECT_TRUE(this->e_it_end_const.operator==(this->e_it_end));
    EXPECT_TRUE(this->e_it_end_const.operator==(this->e_it_end_const));
    EXPECT_TRUE(this->e_it_end_const.operator==(this->e_it_cend));
    EXPECT_TRUE(this->e_it_end_const.operator==(this->e_it_cend_const));

    EXPECT_TRUE(this->e_it_cend.operator==(this->e_it_end));
    EXPECT_TRUE(this->e_it_cend.operator==(this->e_it_end_const));
    EXPECT_TRUE(this->e_it_cend.operator==(this->e_it_cend));
    EXPECT_TRUE(this->e_it_cend.operator==(this->e_it_cend_const));

    EXPECT_TRUE(this->e_it_cend_const.operator==(this->e_it_end));
    EXPECT_TRUE(this->e_it_cend_const.operator==(this->e_it_end_const));
    EXPECT_TRUE(this->e_it_cend_const.operator==(this->e_it_cend));
    EXPECT_TRUE(this->e_it_cend_const.operator==(this->e_it_cend_const));

    EXPECT_TRUE(this->ne_it_end.operator==(this->ne_it_end));
    EXPECT_TRUE(this->ne_it_end.operator==(this->ne_it_end_const));
    EXPECT_TRUE(this->ne_it_end.operator==(this->ne_it_cend));
    EXPECT_TRUE(this->ne_it_end.operator==(this->ne_it_cend_const));

    EXPECT_TRUE(this->ne_it_end_const.operator==(this->ne_it_end));
    EXPECT_TRUE(this->ne_it_end_const.operator==(this->ne_it_end_const));
    EXPECT_TRUE(this->ne_it_end_const.operator==(this->ne_it_cend));
    EXPECT_TRUE(this->ne_it_end_const.operator==(this->ne_it_cend_const));

    EXPECT_TRUE(this->ne_it_cend.operator==(this->ne_it_end));
    EXPECT_TRUE(this->ne_it_cend.operator==(this->ne_it_end_const));
    EXPECT_TRUE(this->ne_it_cend.operator==(this->ne_it_cend));
    EXPECT_TRUE(this->ne_it_cend.operator==(this->ne_it_cend_const));

    EXPECT_TRUE(this->ne_it_cend_const.operator==(this->ne_it_end));
    EXPECT_TRUE(this->ne_it_cend_const.operator==(this->ne_it_end_const));
    EXPECT_TRUE(this->ne_it_cend_const.operator==(this->ne_it_cend));
    EXPECT_TRUE(this->ne_it_cend_const.operator==(this->ne_it_cend_const));
}
TYPED_TEST_P(Iterators, ENE_op_Equality_ENE_a)
{
    // clang-format off
    EXPECT_FALSE(this->e_it_begin.operator==(this->e_it_begin_a));
    EXPECT_FALSE(this->e_it_begin.operator==(this->e_it_begin_const_a));
    EXPECT_FALSE(this->e_it_begin.operator==(this->e_it_cbegin_a));
    EXPECT_FALSE(this->e_it_begin.operator==(this->e_it_cbegin_const_a));

    EXPECT_FALSE(this->e_it_begin_const.operator==(this->e_it_begin_a));
    EXPECT_FALSE(this->e_it_begin_const.operator==(this->e_it_begin_const_a));
    EXPECT_FALSE(this->e_it_begin_const.operator==(this->e_it_cbegin_a));
    EXPECT_FALSE(this->e_it_begin_const.operator==(this->e_it_cbegin_const_a));

    EXPECT_FALSE(this->e_it_cbegin.operator==(this->e_it_begin_a));
    EXPECT_FALSE(this->e_it_cbegin.operator==(this->e_it_begin_const_a));
    EXPECT_FALSE(this->e_it_cbegin.operator==(this->e_it_cbegin_a));
    EXPECT_FALSE(this->e_it_cbegin.operator==(this->e_it_cbegin_const_a));

    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->e_it_begin_a));
    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->e_it_begin_const_a));
    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->e_it_cbegin_a));
    EXPECT_FALSE(this->e_it_cbegin_const.operator==(this->e_it_cbegin_const_a));

    EXPECT_FALSE(this->ne_it_begin.operator==(this->ne_it_begin_a));
    EXPECT_FALSE(this->ne_it_begin.operator==(this->ne_it_begin_const_a));
    EXPECT_FALSE(this->ne_it_begin.operator==(this->ne_it_cbegin_a));
    EXPECT_FALSE(this->ne_it_begin.operator==(this->ne_it_cbegin_const_a));

    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->ne_it_begin_a));
    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->ne_it_begin_const_a));
    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->ne_it_cbegin_a));
    EXPECT_FALSE(this->ne_it_begin_const.operator==(this->ne_it_cbegin_const_a));

    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->ne_it_begin_a));
    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->ne_it_begin_const_a));
    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->ne_it_cbegin_a));
    EXPECT_FALSE(this->ne_it_cbegin.operator==(this->ne_it_cbegin_const_a));

    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->ne_it_begin_a));
    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->ne_it_begin_const_a));
    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->ne_it_cbegin_a));
    EXPECT_FALSE(this->ne_it_cbegin_const.operator==(this->ne_it_cbegin_const_a));

    EXPECT_FALSE(this->e_it_end.operator==(this->e_it_end_a));
    EXPECT_FALSE(this->e_it_end.operator==(this->e_it_end_const_a));
    EXPECT_FALSE(this->e_it_end.operator==(this->e_it_cend_a));
    EXPECT_FALSE(this->e_it_end.operator==(this->e_it_cend_const_a));

    EXPECT_FALSE(this->e_it_end_const.operator==(this->e_it_end_a));
    EXPECT_FALSE(this->e_it_end_const.operator==(this->e_it_end_const_a));
    EXPECT_FALSE(this->e_it_end_const.operator==(this->e_it_cend_a));
    EXPECT_FALSE(this->e_it_end_const.operator==(this->e_it_cend_const_a));

    EXPECT_FALSE(this->e_it_cend.operator==(this->e_it_end_a));
    EXPECT_FALSE(this->e_it_cend.operator==(this->e_it_end_const_a));
    EXPECT_FALSE(this->e_it_cend.operator==(this->e_it_cend_a));
    EXPECT_FALSE(this->e_it_cend.operator==(this->e_it_cend_const_a));

    EXPECT_FALSE(this->e_it_cend_const.operator==(this->e_it_end_a));
    EXPECT_FALSE(this->e_it_cend_const.operator==(this->e_it_end_const_a));
    EXPECT_FALSE(this->e_it_cend_const.operator==(this->e_it_cend_a));
    EXPECT_FALSE(this->e_it_cend_const.operator==(this->e_it_cend_const_a));

    EXPECT_FALSE(this->ne_it_end.operator==(this->ne_it_end_a));
    EXPECT_FALSE(this->ne_it_end.operator==(this->ne_it_end_const_a));
    EXPECT_FALSE(this->ne_it_end.operator==(this->ne_it_cend_a));
    EXPECT_FALSE(this->ne_it_end.operator==(this->ne_it_cend_const_a));

    EXPECT_FALSE(this->ne_it_end_const.operator==(this->ne_it_end_a));
    EXPECT_FALSE(this->ne_it_end_const.operator==(this->ne_it_end_const_a));
    EXPECT_FALSE(this->ne_it_end_const.operator==(this->ne_it_cend_a));
    EXPECT_FALSE(this->ne_it_end_const.operator==(this->ne_it_cend_const_a));

    EXPECT_FALSE(this->ne_it_cend.operator==(this->ne_it_end_a));
    EXPECT_FALSE(this->ne_it_cend.operator==(this->ne_it_end_const_a));
    EXPECT_FALSE(this->ne_it_cend.operator==(this->ne_it_cend_a));
    EXPECT_FALSE(this->ne_it_cend.operator==(this->ne_it_cend_const_a));

    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->ne_it_end_a));
    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->ne_it_end_const_a));
    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->ne_it_cend_a));
    EXPECT_FALSE(this->ne_it_cend_const.operator==(this->ne_it_cend_const_a));
}

TYPED_TEST_P(Iterators, GetDataPointer_Default)
{
    EXPECT_EQ(this->it_default.GetDataPointer(), nullptr);
    EXPECT_EQ(this->c_it_default.GetDataPointer(), nullptr);
}
TYPED_TEST_P(Iterators, GetDataPointer_ENE)
{
    // clang-format off
    EXPECT_EQ(this->e_it_begin.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_begin_const.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_cbegin.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_cbegin_const.GetDataPointer(), this->Empty_list.GetSentinelPointer());

    EXPECT_EQ(this->ne_it_begin.GetDataPointer()->val, Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_begin_const.GetDataPointer()->val, Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_cbegin.GetDataPointer()->val, Iterators<TypeParam>::e0);
    EXPECT_EQ(this->ne_it_cbegin_const.GetDataPointer()->val, Iterators<TypeParam>::e0);

    EXPECT_EQ(this->e_it_end.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_end_const.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_cend.GetDataPointer(), this->Empty_list.GetSentinelPointer());
    EXPECT_EQ(this->e_it_cend_const.GetDataPointer(), this->Empty_list.GetSentinelPointer());

    EXPECT_EQ(this->ne_it_end.GetDataPointer(), this->NEmpty_list.GetSentinelPointer());
    EXPECT_EQ(this->ne_it_end_const.GetDataPointer(), this->NEmpty_list.GetSentinelPointer());
    EXPECT_EQ(this->ne_it_cend.GetDataPointer(), this->NEmpty_list.GetSentinelPointer());
    EXPECT_EQ(this->ne_it_cend_const.GetDataPointer(), this->NEmpty_list.GetSentinelPointer());
    // clang-format on
}

TYPED_TEST_P(Iterators, op_PreIncrement_Default)
{
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator++(), "");
}

TYPED_TEST_P(Iterators, op_PreDecrement_Default)
{
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator--(), "");
}

TYPED_TEST_P(Iterators, op_PostIncrement_Default)
{
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator++(int{}), "");
}

TYPED_TEST_P(Iterators, op_PostDecrement_Default)
{
    RDT_EXPECT_EXIT_FAILURE(this->it_default.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->c_it_default.operator--(int{}), "");
}

TYPED_TEST_P(Iterators, op_PreIncrement_ENE_FromBegin)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin_const.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin_const.operator++(), "");

    /* modifying */
    EXPECT_EQ(*this->ne_it_begin, Iterators<TypeParam>::e0);
    this->ne_it_begin.operator++();
    EXPECT_EQ(*this->ne_it_begin, Iterators<TypeParam>::e1);
    this->ne_it_begin.operator++();
    EXPECT_TRUE(this->ne_it_begin == this->ne_it_end);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator++(), "");

    EXPECT_EQ(*this->ne_it_begin_const, Iterators<TypeParam>::e0);
    this->ne_it_begin_const.operator++();
    EXPECT_EQ(*this->ne_it_begin_const, Iterators<TypeParam>::e1);
    this->ne_it_begin_const.operator++();
    EXPECT_TRUE(this->ne_it_begin_const == this->ne_it_end_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin_const.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator++(), "");

    EXPECT_EQ(*this->ne_it_cbegin, Iterators<TypeParam>::e0);
    this->ne_it_cbegin.operator++();
    EXPECT_EQ(*this->ne_it_cbegin, Iterators<TypeParam>::e1);
    this->ne_it_cbegin.operator++();
    EXPECT_TRUE(this->ne_it_cbegin == this->ne_it_cend);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator++(), "");

    EXPECT_EQ(*this->ne_it_cbegin_const, Iterators<TypeParam>::e0);
    this->ne_it_cbegin_const.operator++();
    EXPECT_EQ(*this->ne_it_cbegin_const, Iterators<TypeParam>::e1);
    this->ne_it_cbegin_const.operator++();
    EXPECT_TRUE(this->ne_it_cbegin_const == this->ne_it_cend_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin_const.operator++(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator++(), "");
}
TYPED_TEST_P(Iterators, op_PreDecrement_ENE_FromEnd)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end_const.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend_const.operator--(), "");

    /* modifying */

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_end, "");
    this->ne_it_end.operator--();
    EXPECT_EQ(*this->ne_it_end, Iterators<TypeParam>::e1);
    this->ne_it_end.operator--();
    EXPECT_EQ(*this->ne_it_end, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_end == this->ne_it_begin);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin.operator--(), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_end_const, "");
    this->ne_it_end_const.operator--();
    EXPECT_EQ(*this->ne_it_end_const, Iterators<TypeParam>::e1);
    this->ne_it_end_const.operator--();
    EXPECT_EQ(*this->ne_it_end_const, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_end_const == this->ne_it_begin_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin_const.operator--(), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_cend, "");
    this->ne_it_cend.operator--();
    EXPECT_EQ(*this->ne_it_cend, Iterators<TypeParam>::e1);
    this->ne_it_cend.operator--();
    EXPECT_EQ(*this->ne_it_cend, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_cend == this->ne_it_cbegin);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin.operator--(), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_cend_const, "");
    this->ne_it_cend_const.operator--();
    EXPECT_EQ(*this->ne_it_cend_const, Iterators<TypeParam>::e1);
    this->ne_it_cend_const.operator--();
    EXPECT_EQ(*this->ne_it_cend_const, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_cend_const == this->ne_it_cbegin_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator--(), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin_const.operator--(), "");
    // clang-format on
}

TYPED_TEST_P(Iterators, op_PostIncrement_ENE_FromBegin)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_begin_const.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cbegin_const.operator++(int{}), "");

    /* modifying */
    EXPECT_EQ(*this->ne_it_begin, Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_begin.operator++(int{}), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_begin, Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_begin.operator++(int{}), Iterators<TypeParam>::e1);
    EXPECT_TRUE(this->ne_it_begin == this->ne_it_end);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator++(int{}), "");

    EXPECT_EQ(*this->ne_it_begin_const, Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_begin_const.operator++(int{}), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_begin_const, Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_begin_const.operator++(int{}), Iterators<TypeParam>::e1);
    EXPECT_TRUE(this->ne_it_begin_const == this->ne_it_end_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin_const.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator++(int{}), "");

    EXPECT_EQ(*this->ne_it_cbegin, Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin.operator++(int{}), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin, Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_cbegin.operator++(int{}), Iterators<TypeParam>::e1);
    EXPECT_TRUE(this->ne_it_cbegin == this->ne_it_cend);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator++(int{}), "");

    EXPECT_EQ(*this->ne_it_cbegin_const, Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin_const.operator++(int{}), Iterators<TypeParam>::e0);
    EXPECT_EQ(*this->ne_it_cbegin_const, Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_cbegin_const.operator++(int{}), Iterators<TypeParam>::e1);
    EXPECT_TRUE(this->ne_it_cbegin_const == this->ne_it_cend_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin_const.operator++(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator++(int{}), "");
    // clang-format on
}

TYPED_TEST_P(Iterators, Op_PostDecrement_ENE_FromEnd)
{
    // clang-format off
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_end_const.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->e_it_cend_const.operator--(int{}), "");

    /* modifying */

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_end, "");
    this->ne_it_end.operator--(int{});
    EXPECT_EQ(*this->ne_it_end.operator--(int{}), Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_end, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_end == this->ne_it_begin);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin.operator--(int{}), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_end_const, "");
    this->ne_it_end_const.operator--(int{});
    EXPECT_EQ(*this->ne_it_end_const.operator--(int{}), Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_end_const, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_end_const == this->ne_it_begin_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_end_const.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_begin_const.operator--(int{}), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_cend, "");
    this->ne_it_cend.operator--(int{});
    EXPECT_EQ(*this->ne_it_cend.operator--(int{}), Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_cend, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_cend == this->ne_it_cbegin);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin.operator--(int{}), "");

    RDT_EXPECT_EXIT_FAILURE(*this->ne_it_cend_const, "");
    this->ne_it_cend_const.operator--(int{});
    EXPECT_EQ(*this->ne_it_cend_const.operator--(int{}), Iterators<TypeParam>::e1);
    EXPECT_EQ(*this->ne_it_cend_const, Iterators<TypeParam>::e0);
    EXPECT_TRUE(this->ne_it_cend_const == this->ne_it_cbegin_const);
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cend_const.operator--(int{}), "");
    RDT_EXPECT_EXIT_FAILURE(this->ne_it_cbegin_const.operator--(int{}), "");
    // clang-format on
}

// clang-format off
REGISTER_TYPED_TEST_SUITE_P(Iterators,
IsValid_Default, IsValid_ENE,
IsDereferencible_Default, IsDereferencible_ENE,
op_Star_Default, op_Start_ENE,
op_Arrow_Default, op_Arrow_ENE,
Default_IsCompatible_ENE, ENE_IsCompatible_ENE, ENE_IsCompatible_ENE_a,
Default_op_Equality_Default,
Default_op_Equality_ENE,
ENE_op_Equality_Default,
ENE_op_Equality_ENE,
ENE_op_Equality_ENE_a,
GetDataPointer_Default, GetDataPointer_ENE,
op_PreIncrement_Default, op_PreDecrement_Default,
op_PostIncrement_Default, op_PostDecrement_Default,
op_PreIncrement_ENE_FromBegin, op_PreDecrement_ENE_FromEnd,
op_PostIncrement_ENE_FromBegin, Op_PostDecrement_ENE_FromEnd);


INSTANTIATE_TYPED_TEST_SUITE_P(Integers, Iterators, GT_INTEGERS);
INSTANTIATE_TYPED_TEST_SUITE_P(Booleans, Iterators, GT_BOOLEANS);
INSTANTIATE_TYPED_TEST_SUITE_P(Characters, Iterators, GT_CHARS);
INSTANTIATE_TYPED_TEST_SUITE_P(Floats, Iterators, GT_FLOATS);

RDT_END