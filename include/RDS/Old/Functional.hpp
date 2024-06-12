#ifndef RDS_FUNCTIONAL_HPP
#define RDS_FUNCTIONAL_HPP

#include <type_traits>

namespace rds
{

#pragma region Comparators

template <class __T_t = void>
struct Greater
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left > right;
    }
};

template <class __T_t = void>
struct GreaterEqual
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left >= right;
    }
};

template <class __T_t = void>
struct Less
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left < right;
    }
};

template <class __T_t = void>
struct LessEqual
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left <= right;
    }
};

template <class __T_t = void>
struct EqualTo
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left == right;
    }
};

template <class __T_t = void>
struct NotEqualTo
{
    auto operator()(const __T_t& left, const __T_t& right) const -> bool
    {
        return left != right;
    }
};

#pragma endregion Comparators

} // namespace rds

#endif // RDS_FUNCTIONAL_HPP