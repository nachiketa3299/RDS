/// @file Array.hpp

#ifndef RDS_ARRAY_HPP
#define RDS_ARRAY_HPP

#include <cstddef>
#include <initializer_list>

#include "RDS_Concepts.h"
#include "RDS_CoreDefs.h"

#include "Array_ConstIterator.hpp"
#include "Array_Iterator.hpp"

RDS_BEGIN

/// @brief 정적 크기를 가지는 배열 템플릿 클래스
/// @tparam T_t 배열 원소의 자료형.
/// @tparam Size_v 배열의 크기
/// @details 단순한 원시 배열에 대한 래퍼로 구현되어 있다. 초기값을 전달하지 않는 경우
/// default-initialization 하기 때문에, `T_t`에 대한 기본 생성자가 정의되어 있으야 한다.
/// (\ref ArrayRequirement)
template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
class Array
{
public: // Type Aliases
    /// @brief 배열 원소의 자료형
    using Val_t  = T_t;
    /// @brief 배열의 크기의 자료형
    using Size_t = std::size_t;

public:
    /// @brief 배열의 반복자의 자료형
    using Iterator      = Array_Iterator<Array>;
    /// @brief 배열의 상수 반복자의 자료형
    using ConstIterator = Array_ConstIterator<Array>;

public: // Ctors
    /// @brief 기본 생성자. @ref Val_t 에 대한 기본 생성자가 정의되어 있어야 하는
    /// 이유이다.
    Array()                   = default;
    /// @brief 기본 소멸자.
    ~Array()                  = default;
    /// @brief 기본 복사 생성자
    Array(const Array& other) = default;

    /// @brief 초기화 리스트를 받는 생성자
    Array(std::initializer_list<Val_t> init_list);

public: // Element Access
    /// @brief 인자로 전달된 인덱스의 배열 원소에 대한 lvalue 참조를 반환한다.
    /// @details 배열 아래 첨자 연산자에 대한 오버로딩이다. 인덱스의 범위 검사를 하지
    /// 않는다.
    /// @param[in] index 참조를 반환할 배열 원소에 대한 인덱스
    /// @warning 인덱스의 범위를 검사하지 않으므로, 주의한다.
    auto operator[](Size_t index) -> Val_t&;
    /// @brief 인자로 전달된 인덱스의 배열 원소에 대한 const-lvalue 참조를 반환한다.
    /// @details 배열 아래 첨자 연산자에 대한 오버로딩이다. 인덱스의 범위 검사를 하지
    /// 않는다.
    /// @param[in] index 참조를 반환할 배열 원소에 대한 인덱스
    /// @warning 인덱스의 범위를 검사하지 않으므로, 주의한다.
    auto operator[](Size_t index) const -> const Val_t&;
    /// @brief 인자로 전달된 인덱스의 배열 원소에 대한 lvalue 참조를 반환한다.
    /// @details 배열의 범위를 검사하여 유효한 인덱스인 경우에만 참조를 반환한다.
    /// 유효하지 않은 경우 비정상 종료한다.
    /// @test \ref Array_ElementAccess_gtest.cpp 에서 테스트.
    /// @test `index` 가 [0, `Size_v`) 범위에 속하지 않는 경우, 비정상 종료하는지 확인.
    auto At(Size_t index) -> Val_t&;
    /// @brief 인자로 전달된 인덱스의 배열 원소에 대한 const-lvalue 참조를 반환한다.
    /// @details 배열의 범위를 검사하여 유효한 인덱스인 경우에만 참조를 반환한다.
    /// 유효하지 않은 경우 비정상 종료한다.
    /// @test \ref Array_ElementAccess_gtest.cpp 에서 테스트.
    /// @test `index` 가 [0, `Size_v`) 범위에 속하지 않는 경우, 비정상 종료하는지 확인.
    auto At(Size_t index) const -> const Val_t&;

public:
    /// @brief 배열의 맨 첫번째 원소에 대한 lvalue 참조를 반환한다.
    /// @return 배열의 맨 첫번째 원소에 대한 lvalue 참조
    /// @details 내부적으로 이 배열을 상수 배열로 형변환한 후, \ref Front() const 함수를
    /// 호출하여 반환값을 `const_cast` 하는 방식으로 작동한다.
    auto Front() -> Val_t&;
    /// @brief 배열의 맨 첫번째 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 배열의 맨 첫번째 원소에 대한 const-lvalue 참조
    auto Front() const -> const Val_t&;
    /// @brief 배열의 맨 마지막 원소에 대한 lvalue 참조를 반환한다.
    /// @return 배열의 맨 첫번째 원소에 대한 lvalue 참조
    /// @details 내부적으로 이 배열을 상수 배열로 형변환한 후, \ref Back() const 함수를
    /// 호출하여 반환값을 `const_cast` 하는 방식으로 작동한다.
    auto Back() -> Val_t&;
    /// @brief 배열의 맨 마지막 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 배열의 맨 마지막 원소에 대한 const-lvalue 참조
    auto Back() const -> const Val_t&;

public: // Iterators
    /// @brief 배열의 맨 첫번째 원소를 가리키는 반복자를 반환한다.
    /// @return 배열의 맨 첫번째 원소를 가리키는 반복자
    auto Begin() -> Iterator;
    /// @brief 배열의 맨 첫번째 원소를 가리키는 상수 반복자를 반환한다.
    /// @return 배열의 맨 첫번째 원소를 가리키는 상수 반복자
    auto Begin() const -> ConstIterator;
    /// @brief 배열의 맨 마지막 원소를 가리키는 반복자를 반환한다.
    /// @return 배열의 맨 마지막 원소를 가리키는 반복자
    auto End() -> Iterator;
    /// @brief 배열의 맨 마지막 원소를 가리키는 상수 반복자를 반환한다.
    /// @return 배열의 맨 마지막 원소를 가리키는 상수 반복자
    auto End() const -> ConstIterator;
    /// @brief 배열의 맨 첫번째 원소를 가리키는 상수 반복자를 반환한다.
    /// @return 배열의 맨 첫번재 원소를 가리키는 상수 반복자
    auto CBegin() const -> ConstIterator;
    /// @brief 배열의 맨 마지막 원소를 가리키는 상수 반복자를 반환한다.
    /// @return 배열의 맨 마지막 원소를 가리키는 상수 반복자
    auto CEnd() const -> ConstIterator;

public: // Capacity
    /// @brief 배열의 크기(원소의 갯수)를 반환한다.
    /// @return 배열의 크기(원소의 갯수)
    auto Size() const -> Size_t;
    /// @brief 배열의 최대 크기(원소의 갯수)를 반환한다. 정적 배열이므로 배열의 크기와
    /// 같은 값을 반환한다.
    /// @return 배열의 최대 크기
    auto MaxSize() const -> Size_t;
    /// @brief 배열이 비어있는지의 여부를 판단한다.
    /// @return 배열이 비어있으면 (`Size` = 0) `ture`, 그렇지 않으면 비어있지
    /// 않으면(`Size` > 0) `false` 를 반환한다.
    /// @details
    /// - `Size_v` 가 0 초과인 경우, 항상 참이 반환된다.
    /// - `Size_v` 가 0인 경우, 항상 거짓이 반환된다.
    auto Empty() const -> bool;

public:
    auto Fill(const Val_t& value) -> void;
    auto Swap(Array& other) -> void;

private:
    /// @brief Array 클래스가 감싸고 있는 크기 @p Size_v 의 원시 배열 이다.
    Val_t m_ptr[Size_v];
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
Array<T_t, Size_v>::Array(std::initializer_list<Val_t> init_list)
{
    for (int i = 0; i < Size_v; ++i)
        m_ptr[i] = *(init_list.begin() + i);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::operator[](Size_t index) -> Val_t&
{
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::operator[](Size_t index) const -> const Val_t&
{
    return m_ptr[index];
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::At(Size_t index) -> Val_t&
{
    RDS_Assert(index < Size_v);
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::At(Size_t index) const -> const T_t&
{
    RDS_Assert(index < Size_v);
    return operator[](index);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Front() -> T_t&
{
    return const_cast<T_t&>(static_cast<const Array<T_t, Size_v>&>(*this).Front());
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Front() const -> const T_t&
{
    return m_ptr[0];
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Back() -> T_t&
{
    return const_cast<T_t&>(static_cast<const Array<T_t, Size_v>&>(*this).Back());
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Back() const -> const T_t&
{
    return m_ptr[Size_v - 1];
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Begin() -> Iterator
{
    return Iterator(m_ptr, 0);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Begin() const -> ConstIterator
{
    return ConstIterator(m_ptr, 0);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::End() -> Iterator
{
    return Iterator(m_ptr, Size_v);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::End() const -> ConstIterator
{
    return ConstIterator(m_ptr, Size_v);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::CBegin() const -> ConstIterator
{
    return ConstIterator(m_ptr, 0);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::CEnd() const -> ConstIterator
{
    return ConstIterator(m_ptr, Size_v);
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Size() const -> Size_t
{
    return Size_v;
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::MaxSize() const -> Size_t
{
    return Size_v;
}

template <class T_t, std::size_t Size_v>
    requires ArrayRequirement<T_t>
auto Array<T_t, Size_v>::Empty() const -> bool
{
    return false;
}

RDS_END

#endif // RDS_ARRAY_HPP
