/// @file List_Iterators_Equality_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"
#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"
#include <list>

using namespace rds;
using namespace std;
using namespace testing;

TEST(STL_List_equality, null)
{
    list<int>::iterator a;
    list<int>::iterator b;

    EXPECT_TRUE(a.operator==(b));
}

class Equality_fixture: public Test
{
    void SetUp() override
    {
        cit_cbegin_a = int_list.CBegin();
        cit_cbegin_b = int_list.CBegin();
        cit_cend_a   = int_list.CEnd();
        cit_cend_b   = int_list.CEnd();
        it_begin_a   = int_list.Begin();
        it_begin_b   = int_list.Begin();
        it_end_a     = int_list.End();
        it_end_b     = int_list.End();

        cit_null_a = List_ConstIterator<List<int>>();
        cit_null_b = List_ConstIterator<List<int>>();
        it_null_a  = List_Iterator<List<int>>();
        it_null_b  = List_Iterator<List<int>>();

        cit_node_a = List_ConstIterator<List<int>>(std::addressof(int_list),
                                                   std::addressof(int_node));
        cit_node_b = List_ConstIterator<List<int>>(std::addressof(int_list),
                                                   std::addressof(int_node));

        it_node_a = List_Iterator<List<int>>(std::addressof(int_list),
                                             std::addressof(int_node));
        it_node_b = List_Iterator<List<int>>(std::addressof(int_list),
                                             std::addressof(int_node));
    }

protected:
    List<int>   int_list{0, 1, 2};
    Node_D<int> int_node;

    List_ConstIterator<List<int>> cit_cbegin_a;
    List_ConstIterator<List<int>> cit_cbegin_b;
    List_ConstIterator<List<int>> cit_cend_a;
    List_ConstIterator<List<int>> cit_cend_b;
    List_Iterator<List<int>>      it_begin_a;
    List_Iterator<List<int>>      it_begin_b;
    List_Iterator<List<int>>      it_end_a;
    List_Iterator<List<int>>      it_end_b;

    List_ConstIterator<List<int>> cit_null_a;
    List_ConstIterator<List<int>> cit_null_b;
    List_Iterator<List<int>>      it_null_a;
    List_Iterator<List<int>>      it_null_b;

    List_ConstIterator<List<int>> cit_node_a;
    List_ConstIterator<List<int>> cit_node_b;
    List_Iterator<List<int>>      it_node_a;
    List_Iterator<List<int>>      it_node_b;
};

TEST_F(Equality_fixture, eq_const_iterator)
{
    EXPECT_TRUE(cit_cbegin_a.operator==(cit_cbegin_b));
    EXPECT_TRUE(cit_cbegin_b.operator==(cit_cbegin_a));
    EXPECT_TRUE(cit_cbegin_a == cit_cbegin_b);
    EXPECT_TRUE(cit_cbegin_b == cit_cbegin_a);
}

TEST_F(Equality_fixture, eq_iterator)
{
    EXPECT_TRUE(it_begin_a.operator==(it_begin_b));
    EXPECT_TRUE(it_begin_b.operator==(it_begin_a));
    EXPECT_TRUE(it_begin_a == it_begin_b);
    EXPECT_TRUE(it_begin_b == it_begin_a);
}

TEST_F(Equality_fixture, eq_const_iterator_iterator)
{
    EXPECT_TRUE(cit_cbegin_a.operator==(it_begin_a));
    EXPECT_TRUE(it_begin_a.operator==(cit_cbegin_a));
    EXPECT_TRUE(cit_cbegin_a == it_begin_a);
    EXPECT_TRUE(it_begin_a == cit_cbegin_a);
}

TEST_F(Equality_fixture, eq_ctor_listnode_const_iterator)
{
    EXPECT_TRUE(cit_node_a.operator==(cit_node_b));
    EXPECT_TRUE(cit_node_b.operator==(cit_node_a));
    EXPECT_TRUE(cit_node_a == cit_node_b);
    EXPECT_TRUE(cit_node_b == cit_node_a);
}

TEST_F(Equality_fixture, eq_ctor_listnode_iterator)
{
    EXPECT_TRUE(it_node_a.operator==(it_node_b));
    EXPECT_TRUE(it_node_b.operator==(it_node_a));
    EXPECT_TRUE(it_node_a == it_node_b);
    EXPECT_TRUE(it_node_b == it_node_a);
}

TEST_F(Equality_fixture, eq_ctor_listnode_const_iterator_iterator)
{
    EXPECT_TRUE(cit_node_a.operator==(it_node_a));
    EXPECT_TRUE(it_node_a.operator==(cit_node_a));
    EXPECT_TRUE(cit_node_a == it_node_a);
    EXPECT_TRUE(it_node_a == cit_node_a);
}

TEST_F(Equality_fixture, eq_null_const_iterator)
{
    EXPECT_TRUE(cit_null_a.operator==(cit_null_b));
    EXPECT_TRUE(cit_null_b.operator==(cit_null_a));
    EXPECT_TRUE(cit_null_a == cit_null_b);
    EXPECT_TRUE(cit_null_b == cit_null_a);
}

TEST_F(Equality_fixture, eq_null_iterator)
{
    EXPECT_TRUE(it_null_a.operator==(it_null_b));
    EXPECT_TRUE(it_null_b.operator==(it_null_a));
    EXPECT_TRUE(it_null_a == it_null_b);
    EXPECT_TRUE(it_null_b == it_null_a);
}

TEST_F(Equality_fixture, eq_null_const_iterator_iterator)
{
    EXPECT_TRUE(cit_null_a.operator==(it_null_a));
    EXPECT_TRUE(it_null_a.operator==(cit_null_a));
    EXPECT_TRUE(cit_null_a == it_null_a);
    EXPECT_TRUE(it_null_a == cit_null_a);
}