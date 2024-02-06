#include <gtest/gtest.h>

#include <list>

#include "List.hpp"

using namespace rds;
using namespace std;

TEST(List_test, PopBack_Empty)
{
    List<int> foo;
    EXPECT_DEATH(foo.PopBack(), "");
}

TEST(List_test, PopFront_Empty)
{
    List<int> foo;
    EXPECT_DEATH(foo.PopFront(), "");
}

TEST(List_test, PushPop_Front_basic)
{
    List<float> bar;
    bar.PushFront(1.f);
    bar.PushFront(2.f);
    bar.PushFront(3.f);
    bar.PushFront(4.f);
    bar.PushFront(5.f);
    bar.PopFront();
    bar.PopFront();
}

TEST(List_test, PushPop_Back_basic)
{
    List<int> foo;
    foo.PushFront(1);
    foo.PushFront(2);
    foo.PushFront(3);
    foo.PushFront(4);
    foo.PushFront(5);
    foo.PopFront();
    foo.PopFront();
}
