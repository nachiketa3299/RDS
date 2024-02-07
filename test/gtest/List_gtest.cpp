#include <gtest/gtest.h>

#include <list>
#include <memory>
#include <type_traits>

#include "List.hpp"

using namespace rds;
using namespace std;

class IntList_test: public ::testing::Test
{
protected:
    void SetUp() override
    {}

    List<int> l_empty;
};

TEST_F(IntList_test, EmptyList_Size)
{
    EXPECT_EQ(l_empty.Size(), 0);
}

TEST_F(IntList_test, EmptyList_PopBack)
{
    EXPECT_EXIT(l_empty.PopBack(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(IntList_test, EmptyList_PopFront)
{
    EXPECT_EXIT(l_empty.PopFront(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST(List_test, ctor_n_val)
{
    List<int> li(10, 10);
    EXPECT_EQ(0, 0);
}

TEST(List_test, PushPop_Front_basic)
{
    EXPECT_EQ(0, 0);
}

TEST(List_test, PushPop_Back_basic)
{

    EXPECT_EQ(0, 0);
}

TEST(List_test, Front_const)
{
    EXPECT_EQ(0, 0);
}

class IntItList_test: public ::testing::Test
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

TEST_F(IntItList_test, CBegin_op_dref)
{
    List<int>::ConstIterator cit = li.CBegin();
    EXPECT_EQ(cit.operator*(), push_val0);
}

TEST_F(IntItList_test, CEnd_op_dref)
{
    List<int>::ConstIterator cit = li.CEnd();
    EXPECT_EQ(cit.operator*(), push_val2);
}

TEST_F(IntItList_test, Begin_op_dref)
{
    List<int>::Iterator it = li.Begin();
    EXPECT_EQ(it.operator*(), push_val0);
}

TEST_F(IntItList_test, End_op_dref)
{
    List<int>::Iterator it = li.End();
    EXPECT_EQ(it.operator*(), push_val2);
}

TEST_F(IntItList_test, CBegin_op_preinc)
{
    List<int>::ConstIterator it = li.CBegin();
    ++it;
    EXPECT_EQ(it.operator*(), push_val1);
}

TEST(List_test, Front_empty)
{}

TEST(List_test, Front_const_empty)
{}

TEST(List_test, Back)
{}

TEST(List_test, Back_const)
{}

TEST(List_test, Back_empty)
{}

TEST(List_test, Back_const_empty)
{}