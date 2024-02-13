/// @file List_Erase_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"

using namespace rds;
using namespace std;
using namespace testing;

// Erase 메서드가 정지하는 경우에 대한 테스트
// (1) (m_size = 0) 비어 있는 리스트에서 반복자(Begin, End)를 통해 Erase 메서드를
// 호출하는 경우
TEST(Erase, exit_empty_begin)
{
    List<int> list_empty{};

    auto begin_it = list_empty.Begin();

    EXPECT_EXIT(list_empty.Erase(begin_it), ExitedWithCode(EXIT_FAILURE), "");
}

// (2) (m_size != 0) 리스트가 비어있건, 비어있지 않건 End() 위치에서 Erase 메서드를
// 호출하는 경우
TEST(Erase, exit_empty_end)
{

    List<int> list_empty{};

    auto end_it_0 = list_empty.End();
    auto end_it_1 = list_empty.Begin(); // 이것 또한 End 위치임

    EXPECT_EXIT(list_empty.Erase(end_it_0), ExitedWithCode(EXIT_FAILURE), "Failed");
    EXPECT_EXIT(list_empty.Erase(end_it_1), ExitedWithCode(EXIT_FAILURE), "");
}

TEST(Erase, exit_nempty_end)
{
    List<int> list_not_empty{1};

    auto end_it_0 = list_not_empty.End();
    auto end_it_1 = ++list_not_empty.Begin();

    EXPECT_EXIT(list_not_empty.Erase(end_it_0), ExitedWithCode(EXIT_FAILURE), "");
    EXPECT_EXIT(list_not_empty.Erase(end_it_1), ExitedWithCode(EXIT_FAILURE), "");
}

TEST(Erase, exit_not_compatible)
{
    List<int> list_a{1, 2};
    List<int> list_b{1, 2};

    auto a_begin_it = list_a.Begin();
    EXPECT_EXIT(list_b.Erase(a_begin_it), ExitedWithCode(EXIT_FAILURE), "");
}

TEST(Erase, basic_start_begin)
{
    List<int> li{1, 2, 3};
    EXPECT_EQ(*li.Begin(), 1);
    EXPECT_EQ(li.Size(), 3);

    li.Erase(li.Begin());
    EXPECT_EQ(*li.Begin(), 2);
    EXPECT_EQ(li.Size(), 2);

    li.Erase(li.Begin());
    EXPECT_EQ(*li.Begin(), 3);
    EXPECT_EQ(li.Size(), 1);
}

TEST(Erase, basic_start_end)
{
    List<int> li{1, 2, 3};
    EXPECT_EQ(*--li.End(), 3);
    EXPECT_EQ(li.Size(), 3);

    li.Erase(--li.End());
    EXPECT_EQ(*--li.End(), 2);
    EXPECT_EQ(li.Size(), 2);

    li.Erase(--li.End());
    EXPECT_EQ(*--li.End(), 1);
    EXPECT_EQ(li.Size(), 1);
}
