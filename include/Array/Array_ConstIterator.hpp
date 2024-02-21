/// @file Array_ConstIterator.hpp

#ifndef RDS_ARRAY_CONSTITERATOR_HPP
#define RDS_ARRAY_CONSTITERATOR_HPP

#include <memory>

#include "RDS_CoreDefs.h"

#include "Assertion.h"

RDS_BEGIN

/// @brief \ref Array 컨테이너에 대한 상수 반복자 템플릿 클래스
/// @tparam Array_t 이 상수 반복자가 가리킬 배열 자료형
/// @details 연속 반복자(Contiguous Iterator) 이다.
template <typename Array_t>
class Array_ConstIterator
{
public: // Type Alias
    /// @brief 이 상수 반복자가 가리키는 배열 원소의 자료형
    using Val_t  = typename Array_t::Val_t;
    /// @brief 이 상수 반복자가 가리키는 배열 크기의 자료형
    using Size_t = typename Array_t::Size_t;
    /// @brief 이 상수 반복자가 가리키는 배열 원소의 차이값의 자료형
    using Diff_t = typename Array_t::Diff_t;

public: // Default CDtors
    /// @brief 기본 생성자
    Array_ConstIterator()                                 = default;
    /// @brief 기본 복사 생성자
    Array_ConstIterator(const Array_ConstIterator& other) = default;
    /// @brief 기본 소멸자
    ~Array_ConstIterator()                                = default;

public: // Custom Ctors
    /// @brief 배열 자체에 대한 포인터와 배열 내 원소에 대한 인덱스를 받는
    /// 생성자
    /// @param cont_ptr 배열 자체에 대한 포인터
    /// @param index 배열 내 원소에 대한 인덱스
    Array_ConstIterator(const Array_t* cont_ptr, Size_t index);

public: // IO Iterator
    /// @brief 이 상수 반복자가 가리키는 배열 원소에 대한 const-lvalue 참조를
    /// 반환한다.
    /// @todo 역참조 불가능한 경우에 대한 처리가 필요하다
    auto operator*() const -> const Val_t&;
    /// @brief 이 상수 반복자가 가리키는 배열 원소에 대한 상수 포인터를
    /// 반환한다.
    auto operator->() const -> const Val_t*;

public: // Forward Iterator
    /// @brief 이 상수 반복자가 가리키는 배열 원소를 다음 원소로 바꾼다.
    /// @return 이 반복자에 대한 lvalue 참조
    /// @details 전위 증가 연산자에 대한 오버로드. 반복자가 배열의 끝을 넘어서는
    /// 경우
    /// (`m_data_offset` > `Array_t::Size_v`) 비정상 종료한다.
    /// @test 반복자가 배열의 끝을 넘어서면 비정상 종료하는지 확인
    auto operator++() -> Array_ConstIterator&;
    /// @brief 이 상수 반복자가 가리키는 배열 원소를 다음 원소로 바꾼다.
    /// @return 이 반복자에 대한 const-lvalue 참조
    /// @details 후위 증가 연산자에 대한 오버로드. 반복자가 배열의 끝을 넘어서는
    /// 경우
    /// (`m_data_offset` > `Array_t::Size_v`) 비정상 종료한다.
    /// @test 반복자가 배열의 끝을 넘어서면 비정상 종료하는지 확인
    auto operator++(int) -> Array_ConstIterator;

public: // Bidirectional Iterator
    /// @brief 이 상수 반복자가 가리키는 배열 원소를 이전 원소로 바꾼다.
    /// @return 이 반복자에 대한 lvalue 참조
    /// @details 전위 감소 연산자에 대한 오버로드. 반복자가 배열의 시작보다
    /// 이전을 가리키려는 경우 (`m_data_offset` < 0) 비정상 종료한다.
    /// @test 반복자가 시작 이전을 가리키려고 할 때 비정상 종료하는지 확인
    auto operator--() -> Array_ConstIterator&;
    /// @brief 이 상수 반복자가 가리키는 배열 원소를 이전 원소로 바꾼다.
    /// @return 이 반복자에 대한 const-lvalue 참조
    /// @details 후위 감소 연산자에 대한 오버로드. 반복자가 배열의 시작보다
    /// 이전을 가리키려는 경우 (`m_data_offset` < 0) 비정상 종료한다.
    /// @test 반복자가 시작 이전을 가리키려고 할 때 비정상 종료하는지 확인
    auto operator--(int) -> Array_ConstIterator;

public: // Random Access Iterator
    auto operator+=(const Diff_t offset) -> Array_ConstIterator&;
    auto operator+(const Diff_t offset) const -> Array_ConstIterator;
    auto operator-=(const Diff_t offset) -> Array_ConstIterator&;
    auto operator-(const Diff_t offset) -> Array_ConstIterator;
    auto operator-(const Array_ConstIterator& other) const -> Diff_t;

public: // Comparators ~ Bid
    auto operator==(const Array_ConstIterator& other) const -> bool;
    auto operator!=(const Array_ConstIterator& other) const -> bool;

public: // Comparators ~ Random
    auto operator<(const Array_ConstIterator& other) const -> bool;
    auto operator>(const Array_ConstIterator& other) const -> bool;
    auto operator<=(const Array_ConstIterator& other) const -> bool;
    auto operator>=(const Array_ConstIterator& other) const -> bool;

private: // Helper Functions
    /// @brief 이 반복자가 유효한지 검사한다.
    auto IsValid() const -> bool;
    auto IsValidPos() const -> bool;
    /// @brief 이 반복자가 역참조 가능한지 검사한다.
    auto IsDereferencible() const -> bool;
    /// @brief 인자로 전달된 반복자와 이 반복자가 호환 가능한지 검사한다.
    auto IsCompatible(const Array_t& array) const -> bool;

public: // Data Access
    /// @brief 이 상수 반복자가 가리키는 배열 원소의 포인터를 반환한다.
    /// @return 이 상수 반복자가 가리키는 배열 원소의 포인터
    auto GetDataPointer() const -> const Val_t*;

protected: // Members
    const Array_t* m_cont_ptr{nullptr};

    Size_t m_data_offset{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <typename Array_t>
inline Array_ConstIterator<Array_t>::Array_ConstIterator(
    const Array_t* cont_ptr, Size_t index)
    : m_cont_ptr(cont_ptr)
    , m_data_offset(index)
{}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::IsValid() const -> bool
{
    return m_cont_ptr != nullptr;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::IsValidPos() const -> bool
{
    return m_data_offset <= m_cont_ptr->Size();
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::IsDereferencible() const -> bool
{
    return IsValid() && IsValidPos() && m_data_offset != m_cont_ptr->Size();
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::IsCompatible(const Array_t& array) const -> bool
{
    return m_cont_ptr == &array;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator*() const -> const Val_t&
{
    RDS_Assert(IsDereferencible() &&
               "Cannot dereference iterator out of range.");
    return *(operator->());
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator->() const -> const Val_t*
{
    return m_cont_ptr->GetSentinelPointer() + m_data_offset;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator++() -> Array_ConstIterator&
{
    ++m_data_offset;
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator++(int) -> Array_ConstIterator
{
    const auto temp = *this;
    operator++();
    return temp;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator--() -> Array_ConstIterator&
{
    --m_data_offset;
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator--(int) -> Array_ConstIterator
{
    const auto temp = *this;
    operator--();
    return temp;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator+=(const Diff_t offset)
    -> Array_ConstIterator&
{
    m_data_offset += static_cast<Size_t>(offset);
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator+(const Diff_t offset) const
    -> Array_ConstIterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator-=(const Diff_t offset)
    -> Array_ConstIterator&
{
    m_data_offset -= static_cast<Size_t>(offset);
    RDS_Assert(IsValidPos() && "Iterator out of range.");
    return *this;
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::operator-(const Diff_t offset)
    -> Array_ConstIterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator-(const Array_ConstIterator& other) const
    -> Diff_t
{
    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return static_cast<Diff_t>(m_data_offset - other.m_data_offset);
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator==(const Array_ConstIterator& other) const
    -> bool
{
    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return m_data_offset == other.m_data_offset;
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator!=(const Array_ConstIterator& other) const
    -> bool
{
    return !(operator==(other));
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator<(const Array_ConstIterator& other) const
    -> bool
{
    RDS_Assert(IsCompatible(*other.m_cont_ptr) && "Incompatible iterators.");
    return m_data_offset < other.m_data_offset;
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator>(const Array_ConstIterator& other) const
    -> bool
{
    return other.operator<(*this);
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator<=(const Array_ConstIterator& other) const
    -> bool
{
    return !operator>(other);
}

template <typename Array_t>
inline auto
Array_ConstIterator<Array_t>::operator>=(const Array_ConstIterator& other) const
    -> bool
{
    return !operator<(other);
}

template <typename Array_t>
inline auto Array_ConstIterator<Array_t>::GetDataPointer() const -> const Val_t*
{
    return m_cont_ptr->GetSentinelPointer() + m_data_offset;
}

RDS_END

#endif // RDS_ARRAY_CONSTITERATOR_HPP
