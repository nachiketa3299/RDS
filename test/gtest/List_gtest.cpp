#include <gtest/gtest.h>

#include <list>
#include <memory>
#include <type_traits>

#include "List.hpp"

using namespace rds;
using namespace std;

class EmptyList: public ::testing::Test
{
protected:
    void SetUp() override
    {}

    List<int> l_empty;
};

TEST_F(EmptyList, Size)
{
    EXPECT_EQ(l_empty.Size(), 0);
}

TEST_F(EmptyList, PopBack)
{
    EXPECT_EXIT(l_empty.PopBack(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(EmptyList, PopFront)
{
    EXPECT_EXIT(l_empty.PopFront(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

// Modifiers

TEST(List_modifiers, PushPop_Front_basic)
{
    EXPECT_EQ(0, 0);
}

TEST(List_modifiers, PushPop_Back_basic)
{

    EXPECT_EQ(0, 0);
}

TEST(List_modifiers, Front_const)
{
    EXPECT_EQ(0, 0);
}

// Element Access

class FList_element_access: public ::testing::Test
{
protected:
    void SetUp() override
    {
        li.PushBack(push_val0);
        li.PushBack(push_val1);
        li.PushBack(push_val2);
    }

    int push_val0 = 0;
    int push_val1 = 1;
    int push_val2 = 2;

    List<int> li;
};

TEST_F(FList_element_access, CBegin_op_dref)
{
    List<int>::ConstIterator cit = li.CBegin();
    EXPECT_EQ(cit.operator*(), push_val0);
}

TEST_F(FList_element_access, CEnd_op_dref)
{
    List<int>::ConstIterator cit = li.CEnd();
    EXPECT_EQ(cit.operator*(), push_val2);
}

TEST_F(FList_element_access, Begin_op_dref)
{
    List<int>::Iterator it = li.Begin();
    EXPECT_EQ(it.operator*(), push_val0);
}

TEST_F(FList_element_access, End_op_dref)
{
    List<int>::Iterator it = li.End();
    EXPECT_EQ(it.operator*(), push_val2);
}

TEST_F(FList_element_access, CBegin_op_preinc)
{
    List<int>::ConstIterator it = li.CBegin();
    ++it;
    EXPECT_EQ(it.operator*(), push_val1);
}

TEST_F(FList_element_access, Front_empty)
{}

TEST_F(FList_element_access, Front_const_empty)
{}

TEST_F(FList_element_access, Back)
{}

TEST_F(FList_element_access, Back_const)
{}

TEST_F(FList_element_access, Back_empty)
{}

TEST_F(FList_element_access, Back_const_empty)
{}

// Ctors

TEST(List_ctor, initializer_list)
{
    List<int> li_0 = {1, 2, 3, 4, 5};
    List<int> li_1{1, 2, 3, 4, 5};
}

TEST(List_ctor, ctor_n_val)
{
    List<int> li(10, 10);
}