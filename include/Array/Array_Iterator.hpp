/// @file Array_Iterator.hpp

#ifndef RDS_ARRAY_ITERATOR_HPP
#define RDS_ARRAY_ITERATOR_HPP

#include <cstddef>

#include "RDS_CoreDefs.h"

#include "Array_ConstIterator.hpp"

RDS_BEGIN

/// @brief \ref Array 컨테이너에 대한 반복자 템플릿 클래스
/// @tparam Array_t 이 상수 반복자가 가리킬 배열 자료형
template <typename Array_t>
class Array_Iterator: public Array_ConstIterator<Array_t>
{
public: // Base Template Class
    using Super = Array_ConstIterator<Array_t>;

public: // Type Alias
    /// @brief 이 반복자가 가리키는 배열 원소의 자료형
    using Val_t  = typename Array_t::Val_t;
    /// @brief 이 반복자가 가리키는 배열 크기의 자료형
    using Size_t = typename Array_t::Size_t;
    /// @brief 이 반복자가 가리키는 배열 원소의 차이값의 자료형
    using Diff_t = typename Array_t::Diff_t;

public: // Default CDtors
    /// @brief 기본 생성자
    Array_Iterator()                            = default;
    /// @brief 기본 복사 생성자
    Array_Iterator(const Array_Iterator& other) = default;
    /// @brief 기본 소멸자
    ~Array_Iterator()                           = default;

public: // Custom Ctors
    /// @brief 배열 자체에 대한 포인터와 배열 내 원소에 대한 인덱스를 받는 생성자
    /// @param cont_ptr 배열 자체에 대한 포인터
    /// @param index 배열 내 원소에 대한 인덱스
    explicit Array_Iterator(const Array_t* cont_ptr, Size_t index);

public: // IO Iterator
    /// @brief 이 반복자가 가리키는 배열 원소에 대한 lvalue 참조를 반환한다.
    auto operator*() const -> Val_t&;
    /// @brief 이 반복자가 가리키는 배열 원소에 대한 포인터를 반환한다.
    auto operator->() const -> Val_t*;

public: // Forward Iterator
    /// @brief 이 반복자가 가리키는 배열 원소를 다음 원소로 바꾼다.
    auto operator++() -> Array_Iterator&;
    /// @brief 이 반복자가 가리키는 배열 원소를 다음 원소로 바꾼다.
    auto operator++(int) -> Array_Iterator;

public: // Bidirectional Iterator
    /// @brief 이 반복자가 가리키는 배열 원소를 이전 원소로 바꾼다.
    auto operator--() -> Array_Iterator&;
    /// @brief 이 반복자가 가리키는 배열 원소를 이전 원소로 바꾼다.
    auto operator--(int) -> Array_Iterator;

public: // Random Access Iterator
    auto operator+=(const Diff_t offset) -> Array_Iterator&;
    auto operator+(const Diff_t offset) const -> Array_Iterator;
    auto operator-=(const Diff_t offset) -> Array_Iterator&;
    auto operator-(const Diff_t offset) -> Array_Iterator;

public: // Data Access
    /// @brief 이 반복자가 가리키는 배열 원소에 대한 포인터를 반환한다.
    auto GetDataPointer() const -> Val_t*;
};

RDS_END

// IMPELEMENTATIONS //

RDS_BEGIN

template <typename Array_t>
Array_Iterator<Array_t>::Array_Iterator(const Array_t* cont_ptr, Size_t index)
    : Super(cont_ptr, index)
{}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator*() const -> Val_t&
{
    return const_cast<Val_t&>(Super::operator*());
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator->() const -> Val_t*
{
    return const_cast<Val_t*>(Super::operator->());
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator++() -> Array_Iterator&
{
    Super::operator++();
    return *this;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator++(int) -> Array_Iterator
{
    const auto temp = *this;
    Super::operator++();
    return temp;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator--() -> Array_Iterator&
{
    Super::operator--();
    return *this;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator--(int) -> Array_Iterator
{
    const auto temp = *this;
    Super::operator--();
    return temp;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator+=(const Diff_t offset) -> Array_Iterator&
{
    Super::operator+=(offset);
    return *this;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator+(const Diff_t offset) const -> Array_Iterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator-=(const Diff_t offset) -> Array_Iterator&
{
    Super::operator-=(offset);
    return *this;
}

template <typename Array_t>
auto Array_Iterator<Array_t>::operator-(const Diff_t offset) -> Array_Iterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

template <typename Array_t>
auto Array_Iterator<Array_t>::GetDataPointer() const -> Val_t*
{
    return const_cast<Val_t*>(Super::GetDataPointer());
}

RDS_END

#endif // RDS_ARRAY_ITERATOR_HPP
