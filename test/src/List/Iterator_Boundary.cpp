#include <gtest/gtest.h>

#include <iostream>

#include "List.hpp"
#include "List_Iterator.hpp"

class BiIteratorBoundary: public testing::Test
{
protected:
    void SetUp() override
    {}

    rds::List<int> int_list       = {1, 2, 3};
    rds::List<int> int_list_empty = {};
};

// 시작 반복자를 감소시키는 경우 Assertion Fail이 일어나는지 확인
TEST_F(BiIteratorBoundary, Before_BeginCBegin)
{
    auto bit  = int_list.Begin();
    auto cbit = int_list.CBegin();

    EXPECT_EXIT(--bit, ::testing::ExitedWithCode(EXIT_FAILURE), "");
    EXPECT_EXIT(--cbit, ::testing::ExitedWithCode(EXIT_FAILURE), "");
}

// 끝 반복자를 증가시키는 경우 Assertion Fail이 일어나는지 확인
TEST_F(BiIteratorBoundary, After_EndCEnd)
{
    auto eit  = int_list.End();
    auto ceit = int_list.CEnd();

    EXPECT_EXIT(++eit, ::testing::ExitedWithCode(EXIT_FAILURE), "");
    EXPECT_EXIT(++ceit, ::testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(BiIteratorBoundary, Normal_BeginCBegin)
{
    auto it = int_list.Begin();

    EXPECT_EQ(*it, 1);
    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*++it, 3);
    EXPECT_EXIT(++(/*End*/ ++it), ::testing::ExitedWithCode(EXIT_FAILURE), "");

    auto cit = int_list.CBegin();

    EXPECT_EQ(*cit, 1);
    EXPECT_EQ(*++cit, 2);
    EXPECT_EQ(*++cit, 3);
    EXPECT_EXIT(++(/*CEnd*/ ++cit), ::testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(BiIteratorBoundary, Normal_EndCEnd)
{
    auto it = int_list.End();
    EXPECT_EQ(*--it, 3);
    EXPECT_EQ(*--it, 2);
    EXPECT_EQ(*--it, 1);
    EXPECT_EXIT(--it, ::testing::ExitedWithCode(EXIT_FAILURE), "");

    auto cit = int_list.CEnd();
    EXPECT_EQ(*--cit, 3);
    EXPECT_EQ(*--cit, 2);
    EXPECT_EQ(*--cit, 1);
    EXPECT_EXIT(--cit, ::testing::ExitedWithCode(EXIT_FAILURE), "");
}