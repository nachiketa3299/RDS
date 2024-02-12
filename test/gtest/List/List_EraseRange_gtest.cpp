/// @file List_EraseRange_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"

#include <iterator>
#include <list>

using namespace rds;
using namespace std;
using namespace testing;

// TEST(List_STL, EraseTest)
// {
//     list<int> l = {0, 1, 2, 3, 4, 5};

//     auto it_f = next(l.begin(), 4);
//     auto it_l = next(l.begin(), 1);

//     // Undefined Behaviour
//     l.erase(it_f, it_l);
// }

TEST(EraseRange, exit_first_not_dereferencible)
{}

TEST(EraseRange, exit_last_not_valid)
{}

TEST(EraseRange, exit_first_not_compatible)
{}

TEST(EraseRange, exit_last_not_compatible)
{}

TEST(EraseRange, fast_return_fisrt_last_same)
{}
