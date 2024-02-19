#include <gtest/gtest.h>

#include "RDT_CoreDefs.h"

#include "Array.hpp"
#include "List.hpp"

TEST(Deref_Invalid, DefaultCtor_List)
{
    auto list_cit = rds::List<int>::ConstIterator();
    auto list_it  = rds::List<int>::Iterator();

    EXPECT_FALSE(list_cit.IsValid());
    EXPECT_FALSE(list_it.IsValid());

    EXPECT_FALSE(list_cit.IsDereferencible());
    EXPECT_FALSE(list_it.IsDereferencible());

    EXPECT_TRUE(list_it == list_cit);
    EXPECT_TRUE(list_cit == list_it);

    EXPECT_FALSE(list_cit != list_it);
    EXPECT_FALSE(list_it != list_cit);

    EXPECT_TRUE(list_cit.GetDataPointer() == nullptr);
    EXPECT_TRUE(list_it.GetDataPointer() == nullptr);

    RDT_EXPECT_EXIT_FAILURE(*list_cit, "");
    RDT_EXPECT_EXIT_FAILURE(*list_it, "");
}

TEST(Deref_Invalid, DefaultCopyCtor_List)
{
    auto list_cit = rds::List<int>::ConstIterator(rds::List<int>::ConstIterator());
    auto list_it  = rds::List<int>::Iterator(rds::List<int>::Iterator());

    EXPECT_FALSE(list_cit.IsValid());
    EXPECT_FALSE(list_it.IsValid());

    EXPECT_FALSE(list_cit.IsDereferencible());
    EXPECT_FALSE(list_it.IsDereferencible());

    EXPECT_TRUE(list_it == list_cit);
    EXPECT_TRUE(list_cit == list_it);

    EXPECT_FALSE(list_cit != list_it);
    EXPECT_FALSE(list_it != list_cit);

    EXPECT_TRUE(list_cit.GetDataPointer() == nullptr);
    EXPECT_TRUE(list_it.GetDataPointer() == nullptr);

    RDT_EXPECT_EXIT_FAILURE(*list_cit, "");
    RDT_EXPECT_EXIT_FAILURE(*list_it, "");
}

TEST(Deref_Invalid, DefaultCtor_Array_NotEmpty)
{
    auto arr_cit = rds::Array<int, 3>::ConstIterator();
    auto arr_it  = rds::Array<int, 3>::Iterator();

    RDT_EXPECT_EXIT_FAILURE(*arr_cit, "");
    RDT_EXPECT_EXIT_FAILURE(*arr_it, "");
}

TEST(Deref_Invalid, DefaultCtor_Array_Empty)
{
    auto arr_cit = rds::Array<int, 0>::ConstIterator();
    auto arr_it  = rds::Array<int, 0>::Iterator();

    RDT_EXPECT_EXIT_FAILURE(*arr_cit, "");
    RDT_EXPECT_EXIT_FAILURE(*arr_it, "");
}