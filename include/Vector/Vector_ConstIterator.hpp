/// @file Vector_ConstIterator.hpp

#ifndef RDS_VECTOR_CONSTITERATOR_HPP
#define RDS_VECTOR_CONSTITERATOR_HPP

#include <memory>

#include "RDS_CoreDefs.h"

#include "Assertion.h"

RDS_BEGIN

/// @brief \ref Vector 컨테이너에 대한 상수 반복자 템플릿 클래스
/// @tparam Vector_t 이 상수 반복자가 가리킬 벡터 자료형
/// @details 연속 반복자(Contiguous Iterator) 이다.
template <class Vector_t>
class Vector_ConstIterator
{
public:
    using Value_t      = typename Vector_t::Value_t;
    using Size_t       = typename Vector_t::Size_t;
    using Difference_t = typename Vector_t::Difference_t;

public:
    Vector_ConstIterator()                                      = default;
    Vector_ConstIterator(const Vector_ConstIterator<Vector_t>&) = default;
    ~Vector_ConstIterator()                                     = default;

public:
    Vector_ConstIterator(const Vector_t* cont_ptr, Size_t index);

public:
    auto operator->() const -> const Value_t*;
    auto operator*() const -> const Value_t&;

public:
    auto operator++() -> Vector_ConstIterator&;
    auto operator++(int) -> Vector_ConstIterator;
    auto operator--() -> Vector_ConstIterator&;
    auto operator--(int) -> Vector_ConstIterator;

public:
    auto operator+=(const Difference_t& offset) -> Vector_ConstIterator&;
    auto operator+(const Difference_t& offset) const -> Vector_ConstIterator;
    auto operator-=(const Difference_t& offset) -> Vector_ConstIterator&;
    auto operator-(const Difference_t& offset) const -> Vector_ConstIterator;
    auto operator-(const Vector_ConstIterator& other) const -> Difference_t;

public:
    auto operator==(const Vector_ConstIterator& other) const -> bool;
    auto operator!=(const Vector_ConstIterator& other) const -> bool;

public:
    auto operator>(const Vector_ConstIterator& other) const -> bool;
    auto operator>=(const Vector_ConstIterator& other) const -> bool;
    auto operator<=(const Vector_ConstIterator& other) const -> bool;
    auto operator<(const Vector_ConstIterator& other) const -> bool;

public:
    auto IsValid() const -> bool;
    auto IsValidPos() const -> bool;
    auto IsDereferencible() const -> bool;
    auto IsCompatible(const Vector_t& vector) const -> bool;

public:
    auto GetDataPoiner() const -> const Value_t*;

private:
    const Vector_t* m_cont_ptr{nullptr};
    Size_t          m_data_offset{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class Vector_t>
inline Vector_ConstIterator<Vector_t>::Vector_ConstIterator(
    const Vector_t* cont_ptr, Size_t index)
    : m_cont_ptr(cont_ptr)
    , m_data_offset(index)
{}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator->() const -> const Value_t*
{
    return m_cont_ptr->GetSentinelPointer() + m_data_offset;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator*() const -> const Value_t&
{
    RDS_Assert(IsDereferencible() &&
               "Cannot dereference iterator out of range.");
    return *(operator->());
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator++()
    -> Vector_ConstIterator&
{
    ++m_data_offset;
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator++(int)
    -> Vector_ConstIterator
{
    const auto temp = *this;
    operator++();
    return temp;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator--()
    -> Vector_ConstIterator&
{
    --m_data_offset;
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator--(int)
    -> Vector_ConstIterator
{
    const auto temp = *this;
    operator--();
    return temp;
}

template <class Vector_t>
inline auto
Vector_ConstIterator<Vector_t>::operator+=(const Difference_t& offset)
    -> Vector_ConstIterator&
{
    m_data_offset += static_cast<Size_t>(offset);
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <class Vector_t>
inline auto
Vector_ConstIterator<Vector_t>::operator+(const Difference_t& offset) const
    -> Vector_ConstIterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <class Vector_t>
inline auto
Vector_ConstIterator<Vector_t>::operator-=(const Difference_t& offset)
    -> Vector_ConstIterator&
{
    m_data_offset -= static_cast<Size_t>(offset);
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <class Vector_t>
inline auto
Vector_ConstIterator<Vector_t>::operator-(const Difference_t& offset) const
    -> Vector_ConstIterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator-(
    const Vector_ConstIterator& other) const -> Difference_t
{
    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return static_cast<Difference_t>(m_data_offset - other.m_data_offset);
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator==(
    const Vector_ConstIterator& other) const -> bool
{

    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return m_data_offset == other.m_data_offset;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator!=(
    const Vector_ConstIterator& other) const -> bool
{
    return !(operator==(other));
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator<(
    const Vector_ConstIterator& other) const -> bool
{
    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return m_data_offset < other.m_data_offset;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::IsValid() const -> bool
{
    return m_cont_ptr != nullptr;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::IsValidPos() const -> bool
{
    return m_data_offset <= m_cont_ptr->Size();
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::IsDereferencible() const -> bool
{
    return IsValid() && IsValidPos() && m_data_offset != m_cont_ptr->Size();
}

template <class Vector_t>
inline auto
Vector_ConstIterator<Vector_t>::IsCompatible(const Vector_t& vector) const
    -> bool
{
    return m_cont_ptr == &vector;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::GetDataPoiner() const
    -> const Value_t*
{
    return m_cont_ptr->GetSentinelPointer() + m_data_offset;
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator>(
    const Vector_ConstIterator& other) const -> bool
{
    return other.operator<(*this);
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator<=(
    const Vector_ConstIterator& other) const -> bool
{
    return !operator>(other);
}

template <class Vector_t>
inline auto Vector_ConstIterator<Vector_t>::operator>=(
    const Vector_ConstIterator& other) const -> bool
{
    return !operator<(other);
}

RDS_END

#endif // RDS_VECTOR_CONSTITERATOR_HPP
