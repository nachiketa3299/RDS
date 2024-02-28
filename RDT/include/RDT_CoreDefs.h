/// @file RDT_CoreDefs.h

#ifndef RDT_COREDEFS_H
#define RDT_COREDEFS_H

#include <gtest/gtest.h>
#include <initializer_list>
#include <tuple>
#include <utility>

// clang-format off
/// @brief 메인 
#define RDT_BEGIN namespace rds::test {
#define RDT_END };

// clang-format on

struct cxx_fundamental_GTestTypes
{
public:
    using integers        = ::testing::Types<short int, unsigned short int, int,
                                      unsigned int, long int, unsigned long int,
                                      long long int, unsigned long long int>;
    using booleans        = ::testing::Types<bool>;
    using characters      = ::testing::Types<signed char, unsigned char, char,
                                        wchar_t, char16_t, char32_t, char8_t>;
    using floating_points = ::testing::Types<float, double, long double>;

public:
};

#define RDT_EXPECT_EXIT_FAILURE(Statement, Pattern)                            \
    EXPECT_EXIT(Statement, ::testing::ExitedWithCode(EXIT_FAILURE), Pattern)

#endif // RDT_COREDEFS_H