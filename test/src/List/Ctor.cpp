#include <gtest/gtest.h>

#include "List.hpp"
#include <list>

using namespace rds;
using namespace std;

TEST(Ctor, InitializerList_PrimitiveTypes)
{
    List<int> int_empty{};
    List<int> int_non_empty{1, 2, 3};

    List<float> float_empty{};
    List<float> float_non_empty{1.f, 2.f, 3.f};

    List<double> double_empty{};
    List<double> double_non_empty{1., 2., 3.};

    List<char> char_empty{};
    List<char> char_non_empty{'a', 'b', 'c'};
}

// clang-format off
template <typename T_t> 
struct TemplatedStruct { T_t val; };
struct PlainStruct{ int a, b; };

// clang-format on

TEST(Ctor, InitializerList_CustomTypes)
{
    List<PlainStruct> ct_empty{};
    List<PlainStruct> ct_non_empty{
        {1, 1},
        {2, 2},
        {3, 3}
    };
}

TEST(Ctor, InitializerList_TemplateTypes)
{
    List<TemplatedStruct<int>> tt_empty{};
    List<TemplatedStruct<int>> tt_non_empty{{1}, {2}, {3}};
}