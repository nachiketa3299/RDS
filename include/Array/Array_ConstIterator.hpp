/// @file Array_ConstIterator.hpp

#ifndef RDS_ARRAY_CONSTITERATOR_HPP
#define RDS_ARRAY_CONSTITERATOR_HPP

#include <cstddef>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "Array.hpp"

RDS_BEGIN

template <typename Array_t>
class Array_ConstIterator
{
public:
    using Val_t  = typename Array_t::Val_t;
    using Size_t = typename Array_t::Size_t;
    using Diff_t = std::ptrdiff_t;

public:
    Array_ConstIterator() = default;
    explicit Array_ConstIterator(const Val_t* head, Size_t index = 0);

private:
    /// @todo WTF This means?
    auto VerifyOffset(const Diff_t offset) const -> void;
    auto IsValid() const -> bool;
    auto IsCompatible(const Array_ConstIterator& other) const -> bool;

public:
    auto operator*() const -> const Val_t&;
    /// @todo no assertion?
    auto operator->() const -> const Val_t*;

public:
    /// @todo what if reaches the end of array?
    auto operator++() -> Array_ConstIterator&;
    auto operator++(int) -> Array_ConstIterator;
    auto operator--() -> Array_ConstIterator&;
    auto operator--(int) -> Array_ConstIterator;

public:
    auto operator+=(const Diff_t offset) -> Array_ConstIterator&;
    auto operator+(const Diff_t offset) const -> Array_ConstIterator;
    auto operator-=(const Diff_t offset) -> Array_ConstIterator&;
    auto operator-(const Diff_t offset) -> Array_ConstIterator;
    auto operator-(const Array_ConstIterator& other) const -> Diff_t;

public:
    auto operator==(const Array_ConstIterator& other) const -> bool;
    auto operator!=(const Array_ConstIterator& other) const -> bool;
    auto operator<(const Array_ConstIterator& other) const -> bool;
    auto operator>(const Array_ConstIterator& other) const -> bool;
    auto operator<=(const Array_ConstIterator& other) const -> bool;
    auto operator>=(const Array_ConstIterator& other) const -> bool;

private:
    const Val_t* m_head{nullptr};
    Size_t       m_offset{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <typename Array_t>
Array_ConstIterator<Array_t>::Array_ConstIterator(const Val_t* head, Size_t index)
    : m_head(head)
    , m_offset(index)
{}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::VerifyOffset(const Diff_t offset) const -> void
{
    if (offset != 0)
        RDS_Assert(m_head != nullptr);
    if (offset < 0)
        RDS_Assert(m_offset >= Size_t{0} - static_cast<Size_t>(offset));
    if (offset > 0)
        RDS_Assert(Array_t::Size_v - m_offset >= static_cast<Size_t>(offset));
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::IsValid() const -> bool
{
    return m_head != nullptr;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::IsCompatible(const Array_ConstIterator& other) const
    -> bool
{
    return m_head == other.m_head;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator*() const -> const Val_t&
{
    return *(operator->());
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator->() const -> const Val_t*
{
    return m_head + m_offset;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator++() -> Array_ConstIterator&
{
    ++m_offset;
    return *this;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator++(int) -> Array_ConstIterator
{
    const auto temp = *this;
    operator++();
    return temp;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator--() -> Array_ConstIterator&
{
    --m_offset;
    return *this;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator--(int) -> Array_ConstIterator
{
    const auto temp = *this;
    operator--();
    return temp;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator+=(const Diff_t offset)
    -> Array_ConstIterator&
{
    VerifyOffset(offset);
    m_offset += static_cast<Size_t>(offset);
    return *this;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator+(const Diff_t offset) const
    -> Array_ConstIterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator-=(const Diff_t offset)
    -> Array_ConstIterator&
{
    VerifyOffset(offset);
    m_offset -= static_cast<Size_t>(offset);
    return *this;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator-(const Diff_t offset) -> Array_ConstIterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator-(const Array_ConstIterator& other) const
    -> Diff_t
{
    RDS_Assert(IsCompatible(other));
    return static_cast<Diff_t>(m_offset - other.m_offset);
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator==(const Array_ConstIterator& other) const
    -> bool
{
    RDS_Assert(IsCompatible(other) && "Iterators are not compatible.");
    return m_offset == other.m_offset;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator!=(const Array_ConstIterator& other) const
    -> bool
{
    return !(operator==(other));
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator<(const Array_ConstIterator& other) const
    -> bool
{
    RDS_Assert(IsCompatible(other) && "Iterators are not compatible.");
    return m_offset < other.m_offset;
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator>(const Array_ConstIterator& other) const
    -> bool
{
    return other.operator<(*this);
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator<=(const Array_ConstIterator& other) const
    -> bool
{
    return !operator>(other);
}

template <typename Array_t>
auto Array_ConstIterator<Array_t>::operator>=(const Array_ConstIterator& other) const
    -> bool
{
    return !operator<(other);
}

RDS_END

#endif // RDS_ARRAY_CONSTITERATOR_HPP
