#ifndef RDS_TESTCOREDEFS_H
#define RDS_TESTCOREDEFS_H

#include <gtest/gtest.h>

// clang-format off
#define RDT_BEGIN namespace rds::test {
#define RDT_END };

// clang-format on

#define RDT_EXPECT_EXIT_FAILURE(Statement, Pattern)                                    \
    EXPECT_EXIT(Statement, ::testing::ExitedWithCode(EXIT_FAILURE), Pattern)

#endif // RDS_TESTCOREDEFS_H