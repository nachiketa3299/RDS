#include <gtest/gtest.h>

#include <list>

#include "List.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

using namespace rds;

TEST(List, DefaultCtors)
{
    List<int>       list;
    const List<int> clist;

    RDT_EXPECT_EXIT_FAILURE(list.Front(), "");
    RDT_EXPECT_EXIT_FAILURE(clist.Front(), "");

    RDT_EXPECT_EXIT_FAILURE(list.Back(), "");
    RDT_EXPECT_EXIT_FAILURE(clist.Back(), "");

    EXPECT_TRUE(list.GetSentinelPointer() != nullptr);
    EXPECT_TRUE(clist.GetSentinelPointer() != nullptr);

    EXPECT_NO_THROW(list.Begin());
    EXPECT_NO_THROW(clist.Begin());

    EXPECT_NO_THROW(list.CBegin());
    EXPECT_NO_THROW(clist.CBegin());

    EXPECT_NO_THROW(list.End());
    EXPECT_NO_THROW(clist.End());

    EXPECT_NO_THROW(list.CEnd());
    EXPECT_NO_THROW(clist.CEnd());

    EXPECT_EQ(list.Size(), 0);
    EXPECT_TRUE(list.Empty());
    EXPECT_EQ(clist.Size(), 0);
    EXPECT_TRUE(clist.Empty());
}

TEST(List, STL)
{
    std::list<int>       li{0};
    const std::list<int> cli{0};
    // clang-format off

    li.begin() == li.begin();
    li.begin() == li.cbegin();
    li.begin() == const_cast<const std::list<int>&>(li).begin();
    li.begin() == const_cast<const std::list<int>&>(li).cbegin();

    li.cbegin() == li.begin();
    li.cbegin() == li.cbegin();
    li.cbegin() == const_cast<const std::list<int>&>(li).begin();
    li.cbegin() == const_cast<const std::list<int>&>(li).cbegin();

    const_cast<const std::list<int>&>(li).begin() == li.begin();
    const_cast<const std::list<int>&>(li).begin() == li.cbegin();
    const_cast<const std::list<int>&>(li).begin() == const_cast<const std::list<int>&>(li).begin();
    const_cast<const std::list<int>&>(li).begin() == const_cast<const std::list<int>&>(li).cbegin();

    const_cast<const std::list<int>&>(li).cbegin() == li.begin();
    const_cast<const std::list<int>&>(li).cbegin() == li.cbegin();
    const_cast<const std::list<int>&>(li).cbegin() == const_cast<const std::list<int>&>(li).begin();
    const_cast<const std::list<int>&>(li).cbegin() == const_cast<const std::list<int>&>(li).cbegin();
}

RDT_END