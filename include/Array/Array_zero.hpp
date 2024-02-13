#ifndef RDS_ARRAY_ZERO_HPP
#define RDS_ARRAY_ZERO_HPP

#include "Array.hpp"

RDS_BEGIN

/// @brief \ref Array 템플릿의 `Size_v`가 0인 경우 특수화
/// @tparam T_t 배열 원소의 자료형.
template <typename T_t>
    requires ArrayRequirement<T_t>
class Array<T_t, 0>
{
public:
    using Val_t  = T_t;
    using Size_t = std::size_t;

public:
    auto IsEmpty() const -> bool;
    auto MaxSize() const -> Size_t;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <typename T_t>
    requires ArrayRequirement<T_t>
auto Array<T_t, 0>::IsEmpty() const -> bool
{
    return false;
}

RDS_END

#endif // RDS_ARRAY_ZERO_HPP
