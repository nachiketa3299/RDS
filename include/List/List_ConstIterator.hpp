/// @file List_ConstIterator.hpp

#ifndef RDS_LIST_CONSTITERATOR_HPP
#define RDS_LIST_CONSTITERATOR_HPP

#include <memory>

#include "RDS_CoreDefs.h"

#include "Assertion.h"

RDS_BEGIN

/// @brief @ref List 컨테이너에 대한 상수 반복자 템플릿 클래스
/// @tparam List_t 이 상수 반복자가 가리킬 리스트의 자료형
/// @details 양방향 반복자(Bidirectional Iterator) 이며, 기본적으로 이 상수 반복자가
/// 가리키는 리스트와 리스트 내부 노드를 포인터( @ref List_ConstIterator::m_node_ptr ,
/// @ref List_ConstIterator::m_proxy)로 저장하고 있다.
template <class List_t>
class List_ConstIterator
{
    friend List_t;

public:
    /// @brief 이 상수 반복자가 가리키는 리스트 원소의 자료형
    using Val_t    = typename List_t::Val_t;
    /// @brief 이 상수 반복자가 가리키는 리스트 크기의 자료형
    using Size_t   = typename List_t::Size_t;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드의 자료형 (@ref Node_D)
    using Node_D_t = typename List_t::Node_D_t;

public:
    /// @brief 기본 생성자. 모든 멤버를 @p nullptr 로 설정한다.
    List_ConstIterator()                                        = default;
    /// @brief 기본 복사 생성자
    List_ConstIterator(const List_ConstIterator<List_t>& other) = default;
    /// @brief 기본 소멸자
    ~List_ConstIterator()                                       = default;
    /// @brief 리스트내 노드 위치와 리스트 자체에 대한 포인터를 받는 생성자.
    /// @param[in] list_ptr 이 상수 반복자가 가리키는 리스트 자체에 대한 포인터
    /// @param[in] node_pos_ptr 이 상수 반복자가 가리키는 리스트의 노드에 대한 포인터
    List_ConstIterator(const List_t* list_ptr, const Node_D_t* node_pos_ptr) noexcept;

public:
    /// @brief 이 상수 반복자가 가리키는 리스트 노드내 값 @p val 에 대한
    /// const-lvalue 참조를 반환한다.
    /// @details 역참조 연산자에 대한 오버로드.
    const Val_t& operator*() const noexcept;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드내 값 @p val 에 대한 상수
    /// 포인터를 반환한다.
    /// @details 화살표(클래스 멤버 접근 연산자)에 대한 오버로드. 화살표 연산자 특성상,
    /// 전역 화살표 연산자가 해당 반환값에 대해 다시 한 번 적용된다.
    const Val_t* operator->() const noexcept;

    /// @todo 이하 모든 증감 연산에 대해서 센티넬 노드에 대한 처리가 필요함
public:
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @details 전위 증가 연산자에 대한 오버로드
    List_ConstIterator& operator++() noexcept;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @details 후위 증가 연산자에 대한 오버로드
    List_ConstIterator  operator++(int) noexcept;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @details 전위 감소 연산자에 대한 오버로드
    List_ConstIterator& operator--() noexcept;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @details 후위 감소 연산자에 대한 오버로드
    List_ConstIterator  operator--(int) noexcept;

private:
    /// @brief 이 상수 반복자가 가리키는 리스트 내 노드에 대한 상수 포인터
    const Node_D_t* node_ptr{nullptr};
    /// @brief 반복자가 가리키는 리스트에 대한 상수 포인터
    const List_t*   m_proxy{nullptr};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class List_t>
inline List_ConstIterator<List_t>::List_ConstIterator(
    const List_t* list_ptr, const Node_D_t* node_pos_ptr) noexcept
    : node_ptr(node_pos_ptr)
    , m_proxy(list_ptr)
{}

template <class List_t>
inline auto List_ConstIterator<List_t>::operator*() const noexcept -> const Val_t&
{
    return node_ptr->val;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator->() const noexcept -> const Val_t*
{
    return std::pointer_traits<const typename List_t::Val_t*>::pointer_to(operator*());
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator++() noexcept
    -> List_ConstIterator<List_t>&
{
    RDS_Assert(node_ptr->next != m_proxy->m_sentinel_node);

    node_ptr = node_ptr->next;
    return *this;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator++(int) noexcept
    -> List_ConstIterator<List_t>
{
    RDS_Assert(node_ptr->next != m_proxy->m_sentinel_node);

    auto temp = *this;
    node_ptr  = node_ptr->next;
    return temp;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator--() noexcept
    -> List_ConstIterator<List_t>&
{
    RDS_Assert(node_ptr->prev != m_proxy->m_sentinel_node);

    node_ptr = node_ptr->prev;
    return *this;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator--(int) noexcept
    -> List_ConstIterator<List_t>
{
    RDS_Assert(node_ptr->prev != m_proxy->m_sentinel_node);

    auto temp = *this;
    node_ptr  = node_ptr->prev;
    return temp;
}

RDS_END

#endif // RDS_LIST_CONSTITERATOR_HPP
