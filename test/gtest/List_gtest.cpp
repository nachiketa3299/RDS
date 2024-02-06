#include <gtest/gtest.h>

#include <list>

#include "List.hpp"

using namespace rds;
using namespace std;

TEST(List_test, STL_examples)
{
    list<int> sfoo;
    // sfoo.pop_back();
}

TEST(List_test, PushPop_Back_basic)
{
    List<int> foo;
    foo.PushBack(1);
    foo.PushBack(2);
    foo.PushBack(3);
    foo.PushBack(4);
    foo.PushBack(5);
    foo.PopBack();
    foo.PopBack();
}

TEST(List_test, Pop_Empty)
{
    List<int> foo;
    foo.PopBack();
}

TEST(List_test, Push_Front_basic)
{
    List<float> bar;
    bar.PushFront(1.f);
    bar.PushFront(2.f);
    bar.PushFront(3.f);
    bar.PushFront(4.f);
    bar.PushFront(5.f);
}
