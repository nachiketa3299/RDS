/// @file List_Iterator.hpp

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
public: // Base Template Class
    /// @brief 이 반복자의 기초 클래스
    using Super = List_ConstIterator<List_t>;

public: // Type Alias
    /// @brief 이 반복자가 가리키는 리스트 원소의 자료형
    using Val_t    = typename List_ConstIterator<List_t>::Val_t;
    /// @brief 이 반복자가 가리키는 리스트 크기의 자료형
    using Size_t   = typename List_ConstIterator<List_t>::Size_t;
    /// @brief 이 반복자가 가리키는 리스트 노드의 자료형 (@ref Node_D)
    using Node_D_t = typename List_ConstIterator<List_t>::Node_D_t;

public: // Default CDtors
    /// @brief 기본 생성자
    List_Iterator()                                   = default;
    /// @brief 기본 복사 생성자
    List_Iterator(const List_Iterator<List_t>& other) = default;
    /// @brief 기본 소멸자
    ~List_Iterator()                                  = default;

public:
    /// @brief 리스트내 노드 위치와 리스트 자체에 대한 포인터를 받는 생성자.
    /// @param[in] list_ptr 이 반복자가 가리키는 리스트 자체에 대한 포인터
    /// @param[in] node_pos_ptr 이 반복자가 가리키는 리스트의 노드에 대한 포인터
    explicit List_Iterator(const List_t*   list_ptr,
                           const Node_D_t* node_pos_ptr) noexcept;

public: // IO Iterator
    /// @brief 이 반복자가 가리키는 리스트 노드 내 값에 대한 lvalue 참조를 반환한다.
    /// @details @ref List_ConstIterator::operator*() 를 호출하고 @p const_cast 로
    /// 상수성을 제거한다.
    auto operator*() const noexcept -> Val_t&;
    /// @brief 이 반복자가 가리키는 리스트 노드 내 값에 대한 포인터를 반환한다.
    /// @details @ref List_ConstIterator::operator->() 를 호출하고 @p const_cast 로
    /// 상수성을 제거한다.
    auto operator->() const noexcept -> Val_t*;

public: // Forward Iterator
    /// @brief 이 반복자가 가리키는 리스트 노드를 다음으로 이동시킨다노
    auto operator++() noexcept -> List_Iterator&;
    /// @brief 이 반복자가 가리키는 리스트 노드를 다음으로 이동시킨다노
    auto operator++(int) noexcept -> List_Iterator;

public: // Bidirectional Iterator
    /// @brief 이 반복자가 가리키는 리스트 노드를 이전으로 이동시킨다노
    auto operator--() noexcept -> List_Iterator&;
    /// @brief 이 반복자가 가리키는 리스트 노드를 이전으로 이동시킨다노
    auto operator--(int) noexcept -> List_Iterator;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class List_t>
List_Iterator<List_t>::List_Iterator(const List_t*   list_ptr,
                                     const Node_D_t* node_pos_ptr) noexcept
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
