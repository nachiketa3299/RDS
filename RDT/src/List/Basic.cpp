/// @file List_Basic.cpp

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

template <class T_t>
class tfList_Test: public testing::Test
{
protected:
    rds::List<T_t> m_list{};
};

TYPED_TEST_SUITE_P(tfList_Test);

TYPED_TEST_P(tfList_Test, List_Fundamental_Types)
{
    this->m_list.PushBack(0);
    this->m_list.PushBack(1);
    this->m_list.PushBack(2);

    EXPECT_EQ(this->m_list.Size(), 3);
    EXPECT_EQ(this->m_list.Front(), 0);
    EXPECT_EQ(this->m_list.Back(), 2);

    auto it = this->m_list.Begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it = this->m_list.End();
    --it;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
    --it;
    EXPECT_EQ(*it, 0);

    this->m_list.PopBack();
    EXPECT_EQ(this->m_list.Size(), 2);
    EXPECT_EQ(this->m_list.Front(), 0);
    EXPECT_EQ(this->m_list.Back(), 1);

    this->m_list.PopBack();
    EXPECT_EQ(this->m_list.Size(), 1);
    EXPECT_EQ(this->m_list.Front(), 0);
    EXPECT_EQ(this->m_list.Back(), 0);

    this->m_list.PopBack();
    EXPECT_EQ(this->m_list.Size(), 0);
}

REGISTER_TYPED_TEST_SUITE_P(tfList_Test, List_Fundamental_Types);

INSTANTIATE_TYPED_TEST_SUITE_P(i_integers, tfList_Test,
                               cxx_fundamental_GTestTypes::integers);
// INSTANTIATE_TYPED_TEST_SUITE_P(i_booleans, tfList_Test,
//                                cxx_fundamental_GTestTypes::booleans);
// INSTANTIATE_TYPED_TEST_SUITE_P(i_characters, tfList_Test,
//                               cxx_fundamental_GTestTypes::characters);
INSTANTIATE_TYPED_TEST_SUITE_P(i_floating_points, tfList_Test,
                               cxx_fundamental_GTestTypes::floating_points);

RDT_END