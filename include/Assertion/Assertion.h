#ifndef RDS_ASSERTION_H
#define RDS_ASSERTION_H

#include "RDS_CoreDefs.h"

RDS_BEGIN

// clang-format off

/// @brief Macro function for assertion in RDS library
/// @param[in] Expression bool-evaluated expresion to assert
/// @see @ref __rds_assert(bool, const char*, const char*, long int*)
#define RDS_Assert(Expression) __rds_assert(Expression, #Expression, __FILE__, __LINE__)

// clang-format on

/// @brief Inner assertion function.
/// @warning Not intended to call directly. Use @ref RDS_Assert instead.
/// @param[in] exp bool-evaluated expression to assert
/// @param[in] exp_str string of expression itself
/// @param[in] file_str name of file ( @p __FILE__ )
/// @param[in] line line number where this assertion called ( @p __LINE__ )
void __rds_assert(bool exp, const char* exp_str, const char* file_str, long int line);

RDS_END

#endif // RDS_ASSERTION_H
