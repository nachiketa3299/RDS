/// @file List_ConstIterator.hpp

#ifndef RDS_LIST_CONSTITERATOR_HPP
#define RDS_LIST_CONSTITERATOR_HPP

#include <memory>

#include "RDS_CoreDefs.h"

#include "Assertion.h"

RDS_BEGIN

/// @brief \ref List 컨테이너에 대한 상수 반복자 템플릿 클래스
/// @tparam List_t 이 상수 반복자가 가리킬 리스트 자료형
/// @details 양방향 반복자(Bidirectional Iterator) 이며, 기본적으로 이 상수
/// 반복자가 가리키는 리스트와 리스트 내부 노드를 포인터(\ref m_node_ptr, \ref
/// m_cont_ptr)로 저장하고 있다.
template <class List_t>
class List_ConstIterator
{
public:
    /// @brief 이 상수 반복자가 가리키는 리스트 원소의 자료형
    using Value_t  = typename List_t::Value_t;
    /// @brief 이 상수 반복자가 가리키는 리스트 크기의 자료형
    using Size_t   = typename List_t::Size_t;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드의 자료형 (@ref Node_D)
    using Node_D_t = typename List_t::Node_D_t;

public: // Default CDtors
    /// @brief 기본 생성자.
    List_ConstIterator()                                  = default;
    /// @brief 기본 복사 생성자
    List_ConstIterator(const List_ConstIterator<List_t>&) = default;
    List_ConstIterator(List_ConstIterator<List_t>&&)      = default;

public:
    auto operator=(const List_ConstIterator<List_t>&)
        -> List_ConstIterator<List_t>& = default;
    auto operator=(List_ConstIterator<List_t>&&)
        -> List_ConstIterator<List_t>& = default;

public:
    /// @brief 기본 소멸자
    ~List_ConstIterator() = default;

public: // Custom Ctors
    /// @brief 리스트내 노드 위치와 리스트 자체에 대한 포인터를 받는 생성자.
    /// @param[in] cont_ptr 이 상수 반복자가 가리키는 리스트 자체에 대한 포인터
    /// @param[in] node_pos_ptr 이 상수 반복자가 가리키는 리스트의 노드에 대한
    /// 포인터
    explicit List_ConstIterator(const List_t*   cont_ptr,
                                const Node_D_t* node_pos_ptr);

public: // IO Iterator
    /// @brief 이 상수 반복자가 가리키는 리스트 노드내 값 @p val 에 대한
    /// const-lvalue 참조를 반환한다.
    /// @details 역참조 연산자에 대한 오버로드.
    /// @todo 반복자의 위치가 End() 인 경우, 역참조시 비정상 종료하도록 구현
    auto operator*() const -> const Value_t&;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드내 값 @p val 에 대한 상수
    /// 포인터를 반환한다.
    /// @details 화살표(클래스 멤버 접근 연산자)에 대한 오버로드. 화살표 연산자
    /// 특성상, 전역 화살표 연산자가 해당 반환값에 대해 다시 한 번 적용된다.
    auto operator->() const -> const Value_t*;

public: // Forward Iterator
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @return 이 반복자에 대한 lvalue 참조
    /// @details 전위 증가 연산자에 대한 오버로드. 현재 반복자가 가리키는
    /// 노드가 센티넬 노드가 아닌 경우에만 수행된다.@n 만일 다음 노드가 센티넬
    /// 노드라면,
    /// @ref List::End() 의 다음으로 가는 것과 같으며, Assertion Failed이다.
    /// @test 반복자가 현재 센티넬 노드를 가리키고 있을 때, 이 연산을 수행하면
    /// 비정상 종료하는지 확인.
    auto operator++() -> List_ConstIterator&;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 다음 노드로
    /// 바꾼다.
    /// @return 이 반복자에 대한 연산 전의 사본
    /// @details 후위 증가 연산자에 대한 오버로드. 현재 반복자가 가리키는
    /// 노드가 센티넬 노드가 아닌 경우에만 수행된다.@n 만일 다음 노드가 센티넬
    /// 노드라면,
    /// @ref List::End() 의 다음으로 가는 것과 같으며, Assertion Failed이다.
    /// @test 반복자가 현재 센티넬 노드를 가리키고 있을 때, 이 연산을 수행하면
    /// 비정상 종료하는지 확인.
    auto operator++(int) -> List_ConstIterator;

public: // Bidirectional Iterator
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @return 이 반복자에 대한 lvalue 참조
    /// @details 전위 감소 연산자에 대한 오버로드. 현재 반복자가 가리키는 노드의
    /// 이전 노드가 센티넬 노드가 아닌 경우에만 수행된다. @n 만일 이전 노드가
    /// 센티넬 노드라면, \ref List::Begin() 혹은 \ref List::CBegin() 의 이전으로
    /// 가는 것과 같으며, Assertion Failed이다.
    /// @test 반복자가 현재 센티넬 노드 바로 다음 노드를 가리키고 있을 때, 이
    /// 연산을 수행하면 비정상 종료하는지 확인.
    auto operator--() -> List_ConstIterator&;
    /// @brief 이 상수 반복자가 가리키는 리스트 노드를 리스트의 이전 노드로
    /// 바꾼다.
    /// @return 이 반복자에 대한 연산 전의 사본
    /// @details 후위 감소 연산자에 대한 오버로드. 현재 반복자가 가리키는 노드의
    /// 이전 노드가 센티넬 노드가 아닌 경우에만 수행된다. @n 만일 이전 노드가
    /// 센티넬 노드라면, @ref List::Begin()의 이전으로 가는 것과 같으며,
    /// Assertion Failed이다.
    /// @test 반복자가 현재 센티넬 노드 바로 다음 노드를 가리키고 있을 때, 이
    /// 연산을 수행하면 비정상 종료하는지 확인.
    auto operator--(int) -> List_ConstIterator;

public: // Comparators
    /// @brief 인자로 전달된 반복자와 이 반복자가 같은지 비교한다.
    /// @param[in] other 비교할 반복자
    /// @return 두 반복자가 같은 경우 `true`, 그렇지 않으면 `false`
    /// @details 다음의 두 조건을 만족하면 두 반복자가 같다고 정의한다.
    /// - 두 반복자가 같은 리스트를 가리키고 있다. (\ref
    /// List_ConstIterator::IsCompatible_unchecked(const List_t*) const 의
    /// 결과이다.)
    /// - 두 반복자가 같은 노드를 가리키고 있다.
    /// 같은 반복자이다.
    /// @warning 반복자의 유효성 여부는 고려하지 않기 때문에 주의가 필요하다.
    /// 예를 들어 두 반복자가 모두 `nullptr` 인 리스트를 가리키고 있고, 노드
    /// 또한 `nullptr` 이면 두 반복자는 모두 유효하지 않지만, 어쨌든 같은 것으로
    /// 취급한다.
    /// @test \ref List_Iterators_Equality_gtest.cpp 에서 테스트.
    auto operator==(const List_ConstIterator<List_t>& other) const -> bool;
    /// @brief 인자로 전달된 반복자와 이 반복자가 다른지 비교한다
    /// @param other 비교할 반복자
    /// @return 두 반복자가 다른 경우 `true`, 그렇지 않으면 `false`
    auto operator!=(const List_ConstIterator<List_t>& other) const -> bool;

public: // Helper Functions
    /// @brief 이 반복자가 유효한지 확인한다.
    /// @return 반복자의 유효성 여부. 유효한 경우 `true`, 그렇지 않으면 `false`
    auto IsValid() const -> bool;
    /// @brief 이 반복자가 가리키는 리스트의 원소를 역참조할 수 있는지 확인한다.
    /// @return 역참조 여부. 역참조가 가능한 경우 `true`, 그렇지 않으면 `false`
    /// @details 역참조가 가능하지 않은 상황은 다음과 같다.\n
    /// - 이 반복자가 유효한 리스트의 유효한 위치를 가리키고 있지 않은 경우
    /// (\ref IsValid() const 의 결과이다.)
    /// - 이 반복자가 센티넬 노드를 가리키고 있는 경우
    auto IsDereferencible() const -> bool;
    /// @brief 인자로 전달된 리스트에 대한 참조가 이 상수 반복자가 가리키는
    /// 리스트와 호환되는지 확인한다.
    /// @param list 이 반복자와 호환성을 확인할 리스트
    /// @return 호환성 여부. 호환이 되는 경우 `true`, 그렇지 않으면 `false`
    /// @details 매개 변수가 참조로 전달되기 때문에 항상 유효한 리스트를
    /// 전달해야 한다.
    auto IsCompatible(const List_t& list) const -> bool;

public: // Data Access
    /// @brief 이 상수 반복자가 가리키는 노드의 주소를 반환한다.
    /// @return 이 상수 반복자가 가리키는 노드의 주소
    auto GetDataPointer() const -> const Node_D_t*;

protected: // Members
    /// @brief 반복자가 가리키는 리스트에 대한 상수 포인터
    const List_t*   m_cont_ptr{nullptr};
    /// @brief 이 상수 반복자가 가리키는 리스트 내 노드에 대한 상수 포인터
    const Node_D_t* m_data_ptr{nullptr};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class List_t>
List_ConstIterator<List_t>::List_ConstIterator(const List_t*   list_ptr,
                                               const Node_D_t* node_pos_ptr)
    : m_cont_ptr(list_ptr)
    , m_data_ptr(node_pos_ptr)
{}

template <class List_t>
inline auto List_ConstIterator<List_t>::operator*() const -> const Value_t&
{
    RDS_Assert(IsDereferencible() && "Cannot dereference invalid iterator.");
    return m_data_ptr->val;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator->() const -> const Value_t*
{
    /// @todo 여기서 무슨 일이 일어나고 있는지 정확히 설명할 수 있어야 합니다.
    return std::pointer_traits<const typename List_t::Value_t*>::pointer_to(
        operator*());
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator++()
    -> List_ConstIterator<List_t>&
{
    // 현재 노드가 센티넬 노드가 아닌 경우에만 증가 연산을 수행한다.
    RDS_Assert(m_data_ptr != m_cont_ptr->GetSentinelPointer() &&
               "Cannot increment end iterator.");

    m_data_ptr = m_data_ptr->next;
    return *this;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator++(int)
    -> List_ConstIterator<List_t>
{
    const auto temp = *this;
    operator++();
    return temp;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator--()
    -> List_ConstIterator<List_t>&
{
    // 이전 노드가 센티넬 노드가 아닌 경우에만 감소 연산을 수행한다.
    RDS_Assert(m_data_ptr->prev != m_cont_ptr->GetSentinelPointer() &&
               "Cannot decrement begin iterator.");

    m_data_ptr = m_data_ptr->prev;
    return *this;
}

template <typename List_t>
inline auto List_ConstIterator<List_t>::operator--(int)
    -> List_ConstIterator<List_t>
{
    const auto temp = *this;
    operator--();
    return temp;
}

template <class List_t>
inline auto List_ConstIterator<List_t>::operator==(
    const List_ConstIterator<List_t>& other) const -> bool
{
    return IsCompatible(*other.m_cont_ptr) && (m_data_ptr == other.m_data_ptr);
}

template <class List_t>
inline auto List_ConstIterator<List_t>::operator!=(
    const List_ConstIterator<List_t>& other) const -> bool
{
    return !(operator==(other));
}

template <class List_t>
inline auto List_ConstIterator<List_t>::IsCompatible(const List_t& list) const
    -> bool
{
    // 컨테이너에 대한 포인터에 저장된 값이 전달된 리스트의 주소값과 같은지
    // 확인한다.
    return m_cont_ptr == std::addressof(list);
}

template <class List_t>
inline auto List_ConstIterator<List_t>::IsValid() const -> bool
{
    return m_cont_ptr != nullptr && m_data_ptr != nullptr;
}

template <class List_t>
inline auto List_ConstIterator<List_t>::IsDereferencible() const -> bool
{
    // 유요하지 않은 반복자는 역참조할 수 없다.
    if (!IsValid())
        return false;

    // 이 반복자가 리스트의 센티넬 노드를 가리키고 있지 않는 경우에만 역참조가
    // 가능하다.
    return m_data_ptr != m_cont_ptr->GetSentinelPointer();
}

template <class List_t>
inline auto List_ConstIterator<List_t>::GetDataPointer() const
    -> const Node_D_t*
{
    return m_data_ptr;
}

RDS_END

#endif // RDS_LIST_CONSTITERATOR_HPP
