#ifndef RDS_ARRAY_H
#define RDS_ARRAY_H

#include <array>
#include <concepts>
#include <cstddef>

#include "Array_ConstIterator.hpp"
#include "Array_Iterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 배열 원소의 형식에 대한 필요 사항: Default Constructible 해야 하며, 크기는 0
/// 이상이어야 함.
template <typename _T>
concept ArrayRequirement = std::default_initializable<_T>;

/// @brief 정적 크기를 가지는 배열 템플릿 클래스
/// @tparam _T 배열 원소의 자료형. 요구 조건은 @ref ArrayRequirement 를 참조.
/// @tparam _Size 배열의 크기
/// @details 단순한 원시 배열에 대한 래퍼로 구현하였다.
template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
class Array
{
public: // Type Aliases
    /// @brief 배열 원소의 자료형
    using Val_t  = _T;
    /// @brief 배열의 크기의 자료형
    using Size_t = std::size_t;

public:
    /// @brief 배열의 반복자의 자료형
    using Iterator      = Array_Iterator<Val_t, _Size>;
    /// @brief 배열의 상수 반복자의 자료형
    using ConstIterator = Array_ConstIterator<Val_t, _Size>;

public: // Ctors
    /// @brief 기본 생성자. @ref Val_t 에 대한 기본 생성자가 정의되어 있어야 하는
    /// 이유이다.
    Array() = default;

    /// @brief 복사 생성자
    /// @todo 너무 단순하게 구현한 것 같은데, 더 나은 방법이 없나?
    Array(const Array& other)
    {
        for (int i = 0; i < _Size; ++i)
            m_ptr[i] = other[i];
    }

    /// @brief 기본 소멸자.
    ~Array() = default;

public: // Element Access
    /// @brief 배열의 앞에서부터 @p index - 1 번째 원소에 대한 lvalue 참조를 반환한다.
    /// @details 배열 아래 첨자 연산자에 대한 오버로딩.
    Val_t&       operator[](Size_t index);
    /// @brief 배열의 앞에서부터 @p index - 1 번째 원소에 대한 const-lvalue 참조 를
    /// 반환한다.
    /// @details 배열 아래 첨자 연산자에 대한 오버로딩의 상수 버전. 모든 멤버 접근
    /// 메소드의 구현의 마지막 부분에서, 항상 이 메소드가 호출된다.
    const Val_t& operator[](Size_t index) const;
    /// @brief 배열의 앞에서부터 @p index - 1 번째 원소에 대한 lvalue 참조를 반환하되,
    /// 전달된
    /// @p index 가 유효한지 검사한다.
    Val_t&       At(Size_t index);
    /// @brief 배열의 앞에서부터 @p index - 1 번째 원소에 대한 const-lvalue 참조를
    /// 반환하되, 전달된
    /// @p index 가 유효한지 검사한다.
    const Val_t& At(Size_t index) const;

public:
    /// @brief 배열의 맨 첫번째 원소에 대한 lvalue 참조를 반환한다.
    Val_t&       Front();
    /// @brief 배열의 맨 첫번째 원소에 대한 const-lvalue 참조를 반환한다.
    const Val_t& Front() const;
    /// @brief 배열의 맨 마지막 원소에 대한 lvalue 참조를 반환한다.
    Val_t&       Back();
    /// @brief 배열의 맨 마지막 원소에 대한 const-lvalue 참조를 반환한다.
    const Val_t& Back() const;

public: // Iterators
    /// @brief 배열의 맨 첫번째 원소를 가리키는 반복자를 반환한다.
    Iterator      Begin();
    /// @brief 배열의 맨 첫번째 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator Begin() const;
    /// @brief 배열의 맨 마지막 원소를 가리키는 반복자를 반환한다.
    Iterator      End();
    /// @brief 배열의 맨 마지막 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator End() const;
    /// @brief 배열의 맨 첫번째 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator CBegin() const;
    /// @brief 배열의 맨 마지막 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator CEnd() const;

public: // Capacity
    /// @brief 배열의 크기(원소의 갯수)를 반환한다.
    Size_t Size() const;
    /// @brief 배열의 최대 크기(원소의 갯수)를 반환한다.
    /// @note @ref Size() const 와 같은 값을 반환한다.
    Size_t MaxSize() const;
    /// @brief 배열이 비어있는지의 여부를 부울형 값으로 반환한다.
    /// @details - @p _Size 가 0 초과인 경우, 항상 참이 반환된다. \n - @p _Size 가 0인
    /// 경우, 항상 거짓이 반환된다.
    bool   Empty() const;

private:
    /// @brief Array 클래스가 감싸고 있는 크기 @p _Size 의 원시 배열 이다.
    Val_t m_ptr[_Size];
};

/// @brief Specialization in @p _Size = 0 for template class @ref Array
template <typename T>
class Array<T, 0>
{
public:
    bool IsEmpty() const
    {
        return true;
    }
};

RDS_END

RDS_BEGIN

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::operator[](Size_t index) -> Val_t&
{
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::operator[](Size_t index) const -> const Val_t&
{
    return m_ptr[index];
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::At(Size_t index) -> Val_t&
{
    RDS_Assert(index < _Size);
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::At(Size_t index) const -> const _T&
{
    RDS_Assert(index < _Size);
    return operator[](index);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Front() -> _T&
{
    return const_cast<_T&>(static_cast<const Array<_T, _Size>&>(*this).Front());
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Front() const -> const _T&
{
    return m_ptr[0];
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Back() -> _T&
{
    return const_cast<_T&>(static_cast<Array<_T, _Size>&>(*this).Back());
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Back() const -> const _T&
{
    return m_ptr[_Size - 1];
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Begin() -> Iterator
{
    return Iterator(m_ptr, 0);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Begin() const -> ConstIterator
{
    return ConstIterator(m_ptr, 0);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::End() -> Iterator
{
    return Iterator(m_ptr, _Size);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::End() const -> ConstIterator
{
    return ConstIterator(m_ptr, _Size);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::CBegin() const -> ConstIterator
{
    return ConstIterator(m_ptr, 0);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::CEnd() const -> ConstIterator
{
    return ConstIterator(m_ptr, _Size);
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Size() const -> Size_t
{
    return _Size;
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::MaxSize() const -> Size_t
{
    return _Size;
}

template <class _T, std::size_t _Size>
    requires ArrayRequirement<_T>
inline auto Array<_T, _Size>::Empty() const -> bool
{
    return false;
}

RDS_END

#endif // RDS_ARRAY_H