/// @file List_Basic.cpp

#include <list>

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;

template <class T_t>
class List_Basic: public testing::Test
{
protected:
    void SetUp() override
    {
        iterator             = m_l.Begin();
        const_iterator       = m_l.CBegin();
        iterator_const       = const_cast<const decltype(m_l)&>(m_l).Begin();
        const_iterator_const = const_cast<const decltype(m_l)&>(m_l).CBegin();
    }

protected:
    List<T_t>       m_list{};
    List<T_t>       m_l{T_t{0}, T_t{1}, T_t{2}};
    const List<T_t> m_cl{T_t{0}, T_t{1}, T_t{2}};
    List<T_t>       m_la{T_t{0}};
    const List<T_t> m_cla{T_t{1}};
};

TYPED_TEST_SUITE_P(List_Basic);

/*
// TYPED_TEST_P(tfList_Test, List_Fundamental_Types)
// {
//     this->m_list.PushBack(TypeParam{0});
//     this->m_list.PushBack(TypeParam{1});
//     this->m_list.PushBack(TypeParam{2});
//     const List<TypeParam> clist = {TypeParam{0}, TypeParam{1}, TypeParam{2}};

//     EXPECT_TRUE(this->m_list.operator==(clist));
//     EXPECT_TRUE(this->m_list.operator==(this->m_list));

//     EXPECT_EQ(this->m_list.Size(), 3);
//     EXPECT_EQ(this->m_list.Front(), TypeParam{0});
//     EXPECT_EQ(this->m_list.Back(), TypeParam{2});

//     auto it  = this->m_list.Begin();
//     auto cit = this->m_list.CBegin();
//     auto itc = const_cast<const decltype(this->m_list)&>(this->m_list)
//                    .Begin(); // Iterator on const list
//     auto citc =
//         const_cast<const decltype(this->m_list)&>(this->m_list).CBegin();

//      * 주석 처리한 부분이 왜 FALSE 인지 찾아보아야 한다
//      * 그리고, STL 에서는 반복자의 상수성과 관계없이 비교가 가능한지 여부도
//      * - 확인 결과 STL 에서는 반복자의 상수성과 관계없이 안전하게 비교가
//      * 가능하다.

//     EXPECT_TRUE(it.operator==(cit));
//     EXPECT_TRUE(cit.operator==(itc)); // 이게 False면 안된다
//     EXPECT_TRUE(itc.operator==(citc));
//     EXPECT_TRUE(citc.operator==(it)); // 이게 False면 안된다

//     EXPECT_EQ(it.operator*(), TypeParam{0});
//     EXPECT_EQ(cit.operator*(), TypeParam{0});
//     EXPECT_EQ(itc.operator*(), TypeParam{0});
//     EXPECT_EQ(citc.operator*(), TypeParam{0});

//     it.operator++();
//     cit.operator++();
//     itc.operator++();
//     citc.operator++();

//     EXPECT_EQ(it.operator*(), TypeParam{1});
//     EXPECT_EQ(cit.operator*(), TypeParam{1});
//     EXPECT_EQ(itc.operator*(), TypeParam{1});
//     EXPECT_EQ(citc.operator*(), TypeParam{1});

//     it.operator++();
//     cit.operator++();
//     itc.operator++();
//     citc.operator++();

//     EXPECT_EQ(it.operator*(), TypeParam{2});
//     EXPECT_EQ(cit.operator*(), TypeParam{2});
//     EXPECT_EQ(itc.operator*(), TypeParam{2});
//     EXPECT_EQ(citc.operator*(), TypeParam{2});

//     // 모든 반복자가 End() 바로 전을 가리키고 있음

//     EXPECT_NO_THROW(it.operator++());
//     EXPECT_NO_THROW(cit.operator++());
//     EXPECT_NO_THROW(itc.operator++());
//     EXPECT_NO_THROW(citc.operator++());

//     EXPECT_TRUE(it.operator==(this->m_list.End()));
//     EXPECT_TRUE(cit.operator==(this->m_list.CEnd()));
//     EXPECT_TRUE(itc.operator==(clist.End()));
//     EXPECT_TRUE(citc.operator==(clist.CEnd()));

//     RDT_EXPECT_EXIT_FAILURE(it.operator++(), "");
//     RDT_EXPECT_EXIT_FAILURE(cit.operator++(), "");
//     RDT_EXPECT_EXIT_FAILURE(itc.operator++(), "");
//     RDT_EXPECT_EXIT_FAILURE(citc.operator++(), "");

//     it   = this->m_list.End();
//     cit  = this->m_list.CEnd();
//     itc  = clist.End();
//     citc = clist.CEnd();

//     RDT_EXPECT_EXIT_FAILURE(it.operator*(), "");
//     RDT_EXPECT_EXIT_FAILURE(cit.operator*(), "");
//     RDT_EXPECT_EXIT_FAILURE(itc.operator*(), "");
//     RDT_EXPECT_EXIT_FAILURE(citc.operator*(), "");

//     it.operator--();
//     cit.operator--();
//     itc.operator--();
//     citc.operator--();
//     EXPECT_EQ(it.operator*(), TypeParam{2});
//     EXPECT_EQ(cit.operator*(), TypeParam{2});
//     EXPECT_EQ(itc.operator*(), TypeParam{2});
//     EXPECT_EQ(citc.operator*(), TypeParam{2});

//     it.operator--();
//     cit.operator--();
//     itc.operator--();
//     citc.operator--();

//     EXPECT_EQ(it.operator*(), TypeParam{1});
//     EXPECT_EQ(cit.operator*(), TypeParam{1});
//     EXPECT_EQ(itc.operator*(), TypeParam{1});
//     EXPECT_EQ(citc.operator*(), TypeParam{1});

//     it.operator--();
//     cit.operator--();
//     itc.operator--();
//     citc.operator--();

//     EXPECT_EQ(it.operator*(), TypeParam{0});
//     EXPECT_EQ(cit.operator*(), TypeParam{0});
//     EXPECT_EQ(itc.operator*(), TypeParam{0});
//     EXPECT_EQ(citc.operator*(), TypeParam{0});

//     RDT_EXPECT_EXIT_FAILURE(it.operator--(), "");
//     RDT_EXPECT_EXIT_FAILURE(cit.operator--(), "");
//     RDT_EXPECT_EXIT_FAILURE(itc.operator--(), "");
//     RDT_EXPECT_EXIT_FAILURE(citc.operator--(), "");

//     this->m_list.PopBack();
//     EXPECT_EQ(this->m_list.Size(), 2);
//     EXPECT_EQ(this->m_list.Front(), TypeParam{0});
//     EXPECT_EQ(this->m_list.Back(), TypeParam{1});

//     EXPECT_FALSE(this->m_list.operator==(clist));

//     this->m_list.PopBack();
//     EXPECT_EQ(this->m_list.Size(), 1);
//     EXPECT_EQ(this->m_list.Front(), TypeParam{0});
//     EXPECT_EQ(this->m_list.Back(), TypeParam{0});

//     EXPECT_FALSE(this->m_list.operator==(clist));

//     this->m_list.PopBack();
//     EXPECT_EQ(this->m_list.Size(), 0);

//     EXPECT_FALSE(this->m_list.operator==(clist));
// }
*/

/*
    두 리스트가 같은지 확인
*/
TYPED_TEST_P(List_Basic, Equality)
{
    EXPECT_TRUE(this->m_l.operator==(this->m_cl));
    EXPECT_TRUE(this->m_cl.operator==(this->m_l));

    EXPECT_FALSE(this->m_l.operator==(this->m_la));
    EXPECT_FALSE(this->m_l.operator==(this->m_cla));
}

REGISTER_TYPED_TEST_SUITE_P(List_Basic, Equality, Iterator_Equality);

INSTANTIATE_TYPED_TEST_SUITE_P(i_integers, List_Basic,
                               cxx_fundamental_GTestTypes::integers);
// INSTANTIATE_TYPED_TEST_SUITE_P(i_booleans, tfList_Test,
//                                cxx_fundamental_GTestTypes::booleans);
// INSTANTIATE_TYPED_TEST_SUITE_P(i_characters, tfList_Test,
//                               cxx_fundamental_GTestTypes::characters);

INSTANTIATE_TYPED_TEST_SUITE_P(i_floating_points, List_Basic,
                               cxx_fundamental_GTestTypes::floating_points);

RDT_END