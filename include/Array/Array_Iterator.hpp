#ifndef RDS_ARRAY_ITERATOR_HPP
#define RDS_ARRAY_ITERATOR_HPP

#include <cstddef>

#include "RDS_CoreDefs.h"

#include "Array_ConstIterator.hpp"

RDS_BEGIN

template <typename Array_t>
class Array_Iterator: public Array_ConstIterator<Array_t>
{
public:
    using Super = Array_ConstIterator<Array_t>;

public:
    using Val_t  = typename Super::Val_t;
    using Size_t = typename Super::Size_t;
    using Diff_t = typename Super::Diff_t;

public:
    Array_Iterator() = default;
    explicit Array_Iterator(const Val_t* head, Size_t index = 0);

public:
    auto operator*() const -> Val_t&;
    auto operator->() const -> Val_t*;

public:
    auto operator++() -> Array_Iterator&;
    auto operator++(int) -> Array_Iterator;
    auto operator--() -> Array_Iterator&;
    auto operator--(int) -> Array_Iterator;

public:
    auto operator+=(const Diff_t offset) -> Array_Iterator&;
    auto operator+(const Diff_t offset) const -> Array_Iterator;
    auto operator-=(const Diff_t offset) -> Array_Iterator&;
    auto operator-(const Diff_t offset) -> Array_Iterator;
};

RDS_END

// IMPELEMENTATIONS //

RDS_BEGIN

template <typename Array_t>
inline Array_Iterator<Array_t>::Array_Iterator(const Val_t* head, Size_t index)
    : Super(head, index)
{}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator*() const -> Val_t&
{
    return const_cast<Val_t&>(Super::operator*());
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator->() const -> Val_t*
{
    return const_cast<Val_t*>(Super::operator->());
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator++() -> Array_Iterator&
{
    Super::operator++();
    return *this;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator++(int) -> Array_Iterator
{
    const auto temp = *this;
    Super::operator++();
    return temp;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator--() -> Array_Iterator&
{
    Super::operator--();
    return *this;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator--(int) -> Array_Iterator
{
    const auto temp = *this;
    Super::operator--();
    return temp;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator+=(const Diff_t offset) -> Array_Iterator&
{
    Super::operator+=(offset);
    return *this;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator+(const Diff_t offset) const
    -> Array_Iterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator-=(const Diff_t offset) -> Array_Iterator&
{
    Super::operator-=(offset);
    return *this;
}

template <typename Array_t>
inline auto Array_Iterator<Array_t>::operator-(const Diff_t offset) -> Array_Iterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

RDS_END

#endif // RDS_ARRAY_ITERATOR_HPP
