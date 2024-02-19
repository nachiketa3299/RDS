#include <gtest/gtest.h>

#include "RDT_CoreDefs.h"

#include "Array.hpp"
#include "List.hpp"

class N_Dereferencible_Cont_int_it_fixture: public testing::Test
{

protected:
    rds::List<int>       list_basic{0, 1, 2};
    const rds::List<int> clist_basic{0, 1, 2};

    rds::Array<int, 3>       arr_basic{0, 1, 2};
    const rds::Array<int, 3> carr_basic{0, 1, 2};
};

class N_Dereferencible_EmptyCont_int_it_fixture: public testing::Test
{
protected:
    rds::List<int>       list_empty{};
    const rds::List<int> clist_empty{};

    rds::Array<int, 0> arr_empty{};
    rds::Array<int, 0> carr_empty{};
};

// 리스트와 배열의 Begin 과 End 에 대해서 역참조 해보는 테스트
// 컨테이너가 비어 있는지
// 컨테이너가 Const 인지

// NonConst Container - Not Empty - Begin

TEST_F(N_Dereferencible_Cont_int_it_fixture, nc_Begin)
{
    EXPECT_EQ(*list_basic.Begin(), 0);
    EXPECT_EQ(*arr_basic.Begin(), 0);
}

// Const Container - Not Empty - Begin

TEST_F(N_Dereferencible_Cont_int_it_fixture, c_Begin)
{
    EXPECT_EQ(*clist_basic.Begin(), 0);
    EXPECT_EQ(*carr_basic.Begin(), 0);
}

// NonConst Container - Not Empty - CBegin

TEST_F(N_Dereferencible_Cont_int_it_fixture, nc_CBegin)
{
    EXPECT_EQ(*list_basic.CBegin(), 0);
    EXPECT_EQ(*arr_basic.CBegin(), 0);
}

// Const Container - Not Empty - CBegin

TEST_F(N_Dereferencible_Cont_int_it_fixture, c_CBegin)
{
    EXPECT_EQ(*clist_basic.CBegin(), 0);
    EXPECT_EQ(*carr_basic.CBegin(), 0);
}

// NonConstContainer - Not Empty - End

TEST_F(N_Dereferencible_Cont_int_it_fixture, nc_End)
{
    RDT_EXPECT_EXIT_FAILURE(*list_basic.End(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_basic.End(), "");
}

// ConstContainer - Not Empty - End

TEST_F(N_Dereferencible_Cont_int_it_fixture, c_End)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_basic.End(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_basic.End(), "");
}

// NonConstContainer - Not Empty - CEnd

TEST_F(N_Dereferencible_Cont_int_it_fixture, nc_CEnd)
{
    RDT_EXPECT_EXIT_FAILURE(*list_basic.CEnd(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_basic.CEnd(), "");
}

// ConstContainer - Not Empty - CEnd

TEST_F(N_Dereferencible_Cont_int_it_fixture, c_CEnd)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_basic.CEnd(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_basic.CEnd(), "");
}

// NonConst Container - Empty - Begin

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, nc_Begin)
{
    RDT_EXPECT_EXIT_FAILURE(*list_empty.Begin(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_empty.Begin(), "");
}

// Const Container - Empty - Begin

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, c_Begin)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_empty.Begin(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_empty.Begin(), "");
}

// NonConst Container - Empty - CBegin

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, nc_CBegin)
{
    RDT_EXPECT_EXIT_FAILURE(*list_empty.CBegin(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_empty.CBegin(), "");
}

// Const Container - Empty - CBegin

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, c_CBegin)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_empty.CBegin(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_empty.CBegin(), "");
}

// NonConstContainer - Empty - End

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, nc_End)
{
    RDT_EXPECT_EXIT_FAILURE(*list_empty.End(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_empty.End(), "");
}

// ConstContainer - Empty - End

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, c_End)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_empty.End(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_empty.End(), "");
}

// NonConstContainer - Empty - CEnd

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, nc_CEnd)
{
    RDT_EXPECT_EXIT_FAILURE(*list_empty.CEnd(), "");
    RDT_EXPECT_EXIT_FAILURE(*arr_empty.CEnd(), "");
}

// ConstContainer - Empty - CEnd

TEST_F(N_Dereferencible_EmptyCont_int_it_fixture, c_CEnd)
{
    RDT_EXPECT_EXIT_FAILURE(*clist_empty.CEnd(), "");
    RDT_EXPECT_EXIT_FAILURE(*carr_empty.CEnd(), "");
}
