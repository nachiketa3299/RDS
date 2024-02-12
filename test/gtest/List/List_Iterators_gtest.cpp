/// @file List_Iterators_gtest.cpp

#include <gtest/gtest.h>

#include "List.hpp"
#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"

using namespace rds;
using namespace std;
using namespace testing;

TEST(Dereference, exit_non_dereferencible_end)
{
    List<int> list = {0, 1, 2};
    EXPECT_EXIT(list.End().operator*(), ExitedWithCode(EXIT_FAILURE), "");
}

TEST(Dereference, exit_non_dereferencible_cend)
{
    List<int> list = {0, 1, 2};
    EXPECT_EXIT(list.CEnd().operator*(), ExitedWithCode(EXIT_FAILURE), "");
}
