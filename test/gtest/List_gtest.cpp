#include <gtest/gtest.h>

#include <cmath>

#include "List.hpp"
#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"

using namespace rds;
using namespace std;

TEST(List_test, Push_Back_basic)
{
    List<int> a;
    a.PushBack(1);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
}

TEST(List_test, Push_Front_basic)
{
    List<float> a;
    a.PushFront(1.f);
    a.PushFront(2.f);
    a.PushFront(3.f);
    a.PushFront(4.f);
    a.PushFront(5.f);
}
