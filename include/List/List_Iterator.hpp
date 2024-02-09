/// @file List_ConstIterator.hpp

#ifndef RDS_LIST_ITERATOR_HPP
#define RDS_LIST_ITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "List_ConstIterator.hpp"

RDS_BEGIN

/// @brief @ref List 컨테이너에 대한 반복자 템플릿 클래스
/// @tparam List_t 이 반복자가 가리킬 리스트의 자료형
/// @details 이 반복자는 @ref List_ConstIterator 클래스를 상속하고 상수성을 제거하는
/// 방식으로 구현되어 있다. 자세한 설명은 @ref List_ConstIterator 클래스를 참고한다.
template <class List_t>
class List_Iterator: public List_ConstIterator<List_t>
{
    friend List_t;

public:
    /// @brief 이 반복자의 기초 클래스
    using Super    = List_ConstIterator<List_t>;
    /// @brief 이 반복자가 가리키는 리스트 원소의 자료형
    using Val_t    = typename List_ConstIterator<List_t>::Val_t;
    /// @brief 이 반복자가 가리키는 리스트 크기의 자료형
    using Size_t   = typename List_ConstIterator<List_t>::Size_t;
    /// @brief 이 반복자가 가리키는 리스트 노드의 자료형 (@ref Node_D)
    using Node_D_t = typename List_ConstIterator<List_t>::Node_D_t;

public:
    /// @brief 기본 생성자
    List_Iterator()                                   = default;
    /// @brief 기본 복사 생성자
    List_Iterator(const List_Iterator<List_t>& other) = default;
    /// @brief 기본 소멸자
    ~List_Iterator()                                  = default;
    /// @brief 리스트내 노드 위치와 리스트 자체에 대한 포인터를 받는 생성자.
    /// @param[in] list_ptr 이 반복자가 가리키는 리스트 자체에 대한 포인터
    /// @param[in] node_pos_ptr 이 반복자가 가리키는 리스트의 노드에 대한 포인터
    List_Iterator(const List_t* list_ptr, Node_D_t* node_pos_ptr) noexcept;

public:
    /// @brief 이 반복자가 가리키는 리스트 노드 내 값에 대한 lvalue 참조를 반환한다.
    /// @details @ref List_ConstIterator::operator*() 를 호출하고 @p const_cast 로
    /// 상수성을 제거한다.
    Val_t& operator*() const noexcept;
    /// @brief 이 반복자가 가리키는 리스트 노드 내 값에 대한 포인터를 반환한다.
    /// @details @ref List_ConstIterator::operator->() 를 호출하고 @p const_cast 로
    /// 상수성을 제거한다.
    Val_t* operator->() const noexcept;

public:
    /// @brief 이 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @details 전위 증가 연산자에 대한 오버로드. 부모의 전위 증가 연산자를 호출한다.
    List_Iterator& operator++() noexcept;
    /// @brief 이 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @details 후위 증가 연산자에 대한 오버로드. 부모의 후위 증가 연산자를 호출한다.
    List_Iterator  operator++(int) noexcept;
    /// @brief 이 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @details 전위 감소 연산자에 대한 오버로드. 부모의 전위 감소 연산자를 호출한다.
    List_Iterator& operator--() noexcept;
    /// @brief 이 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @details 후위 감소 연산자에 대한 오버로드. 부모의 후위 감소 연산자를 호출한다.
    List_Iterator  operator--(int) noexcept;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class List_t>
List_Iterator<List_t>::List_Iterator(const List_t* list_ptr,
                                     Node_D_t*     node_pos_ptr) noexcept
    : Super(list_ptr, node_pos_ptr)
{}

template <typename List_t>
auto List_Iterator<List_t>::operator*() const noexcept -> Val_t&
{
    return const_cast<Val_t&>(Super::operator*());
}

template <typename List_t>
auto List_Iterator<List_t>::operator->() const noexcept -> Val_t*
{
    return const_cast<Val_t*>(Super::operator->());
}

template <typename List_t>
auto List_Iterator<List_t>::operator++() noexcept -> List_Iterator&
{
    Super::operator++();
    return *this;
}

template <typename List_t>
auto List_Iterator<List_t>::operator++(int) noexcept -> List_Iterator
{
    auto temp = *this;
    operator++();
    return temp;
}

template <typename List_t>
auto List_Iterator<List_t>::operator--() noexcept -> List_Iterator&
{
    Super::operator--();
    return *this;
}

template <typename List_t>
auto List_Iterator<List_t>::operator--(int) noexcept -> List_Iterator
{
    auto temp = *this;
    operator--();
    return temp;
}

RDS_END

#endif // RDS_LIST_ITERATOR_HPP
