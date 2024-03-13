#ifndef RDS_LIST_ITERATOR_HPP
#define RDS_LIST_ITERATOR_HPP

#include "List_ConstIterator.hpp"

namespace rds
{

/** @brief \ref List 컨테이너에 대한 반복자 템플릿 클래스
 *  @tparam __List_t 이 반복자가 가리킬 리스트의 자료형
 *  @see \ref List_ConstIterator
 */
template <class __List_t>
class List_Iterator: public List_ConstIterator<__List_t>
{
public:
    using Super_t  = List_ConstIterator<__List_t>;
    using Node_D_t = typename List_ConstIterator<__List_t>::Node_D_t;

    /// @{ @name Iterator Traits

public:
    using Value_t      = typename Super_t::Value_t;
    using Pointer_t    = typename Super_t::Pointer_t;
    using Reference_t  = typename Super_t::Reference_t;
    using Difference_t = typename Super_t::Difference_t;

    /// @} // Iterator Traits

public:
    /** @brief 기본 생성자 */
    List_Iterator()                               = default;
    /** @brief 기본 복사 생성자 */
    List_Iterator(const List_Iterator<__List_t>&) = default;
    /** @brief 기본 소멸자 */
    ~List_Iterator()                              = default;

    // TODO 이거 copydoc을 할 수 있는 방법이 없을까?
    /** @brief 리스트에 대한 포인터와 노드의 위치를 받는 생성자
     *  @param cont_ptr 이 반복자가 가리키는 리스트에 대한 포인터
     *  @param node_pos_ptr 이 반복자가 가리키는 노드에 대한 포인터
     *
     *  @warning 리스트에 속하지 않은 노드를 전달하는 경우 정의되지 않은
     *  행동이다.
     */
    explicit List_Iterator(const __List_t* list_ptr,
                           const Node_D_t* dnode_pos_ptr)
        : Super_t(list_ptr, dnode_pos_ptr)
    {}

    /// @{ @name Input & Output Iterator Operations

public:
    /** @copydoc List_ConstIterator::operator*()
     *  @note 반환된 참조를 통해 값을 변경할 수 있다.
     */
    auto operator*() const -> Value_t&
    {
        return const_cast<Value_t&>(Super_t::operator*());
    }

    /** @copydoc List_ConstIterator::operator->()
     */
    auto operator->() const -> Value_t*
    {
        return const_cast<Value_t*>(Super_t::operator->());
    }

    /// @} // Input & Output Iterator Operations

    /// @{ @name Forward Iterator Operations

public:
    /** @copydoc List_ConstIterator::operator++ */
    auto operator++() -> List_Iterator&
    {
        Super_t::operator++();
        return *this;
    }

    /** @copydoc List_ConstIterator::operator++(int) */
    auto operator++(int) -> List_Iterator
    {
        const auto temp = *this;
        operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations

    /// @{ @name Bidirectional Iterator Operation

    /** @copydoc List_ConstIterator::operator--() */
    auto operator--() -> List_Iterator&
    {
        Super_t::operator--();
        return *this;
    }

    /** @copydoc List_ConstIterator::operator--(int) */
    auto operator--(int) -> List_Iterator
    {
        const auto temp = *this;
        operator--();
        return temp;
    }

    /// @} // Bidirectional Iterator Operation
};

} // namespace rds

#endif // RDS_LIST_ITERATOR_HPP
