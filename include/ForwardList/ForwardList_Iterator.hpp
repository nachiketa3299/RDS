#ifndef RDS_FORWARDLIST_ITERATOR_HPP
#define RDS_FORWARDLIST_ITERATOR_HPP

#include "ForwardList_ConstIterator.hpp"

namespace rds
{

/** @brief \ref ForwardList 컨테이너에 대한 반복자 템플릿 클래스
 *  @tparam __ForwardList_t 이 반복자가 가리킬 리스트의 자료형
 *  @see \ref ForwardList_ConstIterator
 */
template <class __ForwardList_t>
class ForwardList_Iterator: public ForwardList_ConstIterator<__ForwardList_t>
{
public:
    using Super_t = ForwardList_ConstIterator<__ForwardList_t>;
    using Node_S_t =
        typename ForwardList_ConstIterator<__ForwardList_t>::Node_S_t;

    /// @{ @name Iterator Traits

public:
    using Value_t      = typename Super_t::Value_t;
    using Pointer_t    = typename Super_t::Pointer_t;
    using Reference_t  = typename Super_t::Reference_t;
    using Difference_t = typename Super_t::Difference_t;

    /// @} // Iterator Traits

public:
    /** @brief 기본 생성자 */
    ForwardList_Iterator()                            = default;
    /** @brief 기본 복사 생성자 */
    ForwardList_Iterator(const ForwardList_Iterator&) = default;
    /** @brief 기본 소멸자 */
    ~ForwardList_Iterator()                           = default;

    // TODO 이거 copydoc을 할 수 있는 방법이 없을까?
    /** @brief 전방 리스트에 대한 포인터와 노드의 위치를 받는 생성자
     *  @param cont_ptr 이 반복자가 가리키는 전방 리스트에 대한 포인터
     *  @param node_pos_ptr 이 반복자가 가리키는 노드에 대한 포인터
     *
     *  @warning 전방 리스트에 속하지 않은 노드를 전달하는 경우 정의되지 않은
     *  행동이다.
     */
    // TODO 이거 copydoc 이 안됨 ㅠㅠ
    explicit ForwardList_Iterator(const __ForwardList_t* cont_ptr,
                                  const Node_S_t*        node_pos_ptr)
        : Super_t(cont_ptr, node_pos_ptr)
    {}

    /// @{ @name Input & Output Iterator Operations

public:
    /** @copydoc ForwardList_ConstIterator::operator*()
     *  @note 반환된 참조를 통해 값을 변경할 수 있다.
     */
    auto operator*() const -> Value_t&
    {
        return const_cast<Value_t&>(Super_t::operator*());
    }

    /** @copydoc ForwardList_ConstIterator::operator->()
     *
     */
    auto operator->() const -> Value_t*
    {
        return const_cast<Value_t*>(Super_t::operator->());
    }

    /// @} // Input & Output Iterator Operations

    /// @{ @name Forward Iterator Operations

public:
    /** @copydoc ForwardList_ConstIterator::operator++ */
    auto operator++() -> ForwardList_Iterator&
    {
        Super_t::operator++();
        return *this;
    }

    /** @copydoc ForwardList_ConstIterator::operator++(int) */
    auto operator++(int) -> ForwardList_Iterator
    {
        const auto temp = *this;
        operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations
};

} // namespace rds

#endif // RDS_FORWARDLIST_ITERATOR_HPP
