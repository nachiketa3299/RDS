#ifndef RDS_FORWARDLIST_CONSTITERATOR_HPP
#define RDS_FORWARDLIST_CONSTITERATOR_HPP

#include "RDS_CoreDefs.h"

#include <memory> // std::pointer_traits

#include "Assertion.h"
#include "Iterator.hpp"

namespace rds
{

/** @brief \ref FowardList 컨테이너에 대한 상수 반복자 템플릿 클래스
 *  @tparam __ForwardList_t 이 상수 반복자가 가리킬 리스트에 대한 자료형
 *  @note 전방 반복자이다.
 */
// clang-format off
template <class __ForwardList_t>
class ForwardList_ConstIterator
    : public Iterator< tag::ForwardIterator
                     , typename __ForwardList_t::Value_t
                     , typename __ForwardList_t::Pointer_t
                     , typename __ForwardList_t::Reference_t
                     , typename __ForwardList_t::Difference_t>
{
public:
    using Node_S_t = typename __ForwardList_t::Node_S_t;

    /// @{ @name Iterator Traits
public:
    using Iterator_t = Iterator< tag::ForwardIterator
                               , typename __ForwardList_t::Value_t
                               , typename __ForwardList_t::Pointer_t
                               , typename __ForwardList_t::Reference_t
                               , typename __ForwardList_t::Difference_t>;
    // clang-format on
    using IteratorTag_t = typename Iterator_t::IteratorTag_t;
    using Value_t       = typename Iterator_t::Value_t;
    using Pointer_t     = typename Iterator_t::Pointer_t;
    using Reference_t   = typename Iterator_t::Reference_t;
    using Difference_t  = typename Iterator_t::Difference_t;

    /// @} // Iterator Traits

public:
    /** @brief 기본 생성자 */
    ForwardList_ConstIterator()                                 = default;
    /** @brief 기본 복사 생성자 */
    ForwardList_ConstIterator(const ForwardList_ConstIterator&) = default;
    /** @brief 기본 이동 생성자 */
    ForwardList_ConstIterator(ForwardList_ConstIterator&&)      = default;
    /** @brief 기본 복사 대입 연산자 */
    auto operator=(const ForwardList_ConstIterator&)
        -> ForwardList_ConstIterator& = default;
    /** @brief 기본 이동 대입 연산자 */
    auto operator=(ForwardList_ConstIterator&&)
        -> ForwardList_ConstIterator& = default;
    /** @brief 기본 소멸자 */
    ~ForwardList_ConstIterator()      = default;

    /** @brief 전방 리스트에 대한 포인터와 노드의 위치를 받는 생성자
     *  @param cont_ptr 이 반복자가 가리키는 전방 리스트에 대한 포인터
     *  @param node_pos_ptr 이 반복자가 가리키는 노드에 대한 포인터
     *
     *  @warning 전방 리스트에 속하지 않은 노드를 전달하는 경우 정의되지 않은
     *  행동이다.
     */
    explicit ForwardList_ConstIterator(const __ForwardList_t* cont_ptr,
                                       const Node_S_t*        node_pos_ptr)
        : m_cont_ptr(cont_ptr)
        , m_data_ptr(node_pos_ptr)
    {}

    /// @{ @name Input & Output Iterator Operations
public:
    // TODO 역참조가 불가능한 경우 Release 구성에서 예외를 던지게 한다면 더 좋을
    // 것 같다.
    /** @brief 이 반복자가 가리키는 노드의 값에 대한 참조를 반환한다.
     *
     *  @warning Debug 구성에서 이 반복자가 역참조가 불가능한 경우 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator*() const -> const Value_t&
    {
        RDS_Assert(IsDereferencible() &&
                   "Cannot dereference invalid iterator.");
        return m_data_ptr->val;
    }

    /** @brief 이 반복자가 가리키는 노드의 값에 대한 포인터를 반환한다.
     *  @return 이 반복자가 가리키는 노드의 값에 대한 포인터
     */
    auto operator->() const -> const Value_t*
    {
        return std::pointer_traits<
            const typename __ForwardList_t::Value_t*>::pointer_to(operator*());
    }

    // TODO 유효하지 않은 반복자에 대한 동등성 비교 테스트할 것
    /** @brief 두 반복자의 동등성을 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 같은 경우 `true`, 그렇지 않으면 `false`
     *  @details
     *  두 반복자의 동등성은 다음과 같이 정의한다.
     *  - 두 반복자가 같은 전방 리스트를 가리키고 있다.
     *  - 두 반복자가 같은 노드를 가리키고 있다.
     */
    auto operator==(const ForwardList_ConstIterator& other) const -> bool
    {
        return IsCompatible(*other.m_cont_ptr) &&
               (m_data_ptr == other.m_data_ptr);
    }

    /** @brief 두 반복자가 비동등성을 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 다른 경우 `true`, 그렇지 않으면 `false`
     *  @details \ref operator== 의 반대 결과를 반환한다.
     */
    auto operator!=(const ForwardList_ConstIterator& other) const -> bool
    {
        return !operator==(other);
    }

    /// @} // Input & Output Iterator Operations

    /// @{ @name Forward Iterator Operations
public:
    // TODO Release 구성에서 예외를 던지게 한다면 더 좋을 것 같다.
    /** @brief 이 반복자가 가리키는 위치를 하나 증가시킨다.
     *  @return 연산 후 이 반복자에 대한 참조
     *  @details 현재 노드가 센티넬 노드가 아닌 경우에만 연산을 수행한다.
     *
     *  @warning Debug 구성에서 현재 노드가 센티넬 노드인 경우 비정상  종료하고,
     *  Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator++() -> ForwardList_ConstIterator&
    {
        RDS_Assert(m_data_ptr != m_cont_ptr->GetSentinelPointer() &&
                   "Cannot increment end iterator.");

        m_data_ptr = m_data_ptr->next;
        return *this;
    }

    /** @overload
     *  @return 연산 전 이 반복자에 대한 사본
     */
    auto operator++(int) -> ForwardList_ConstIterator
    {
        const auto temp = *this;
        operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations

    /// @{ @name Helper Methods

public:
    /** @brief 반복자가 유효한지 확인한다.
     *  @details
     *  유효한 반복자에 대한 정의는 아래와 같다.
     *  - 전방 리스트에 대한 포인터가 `nullptr`이 아니다.
     *  - 노드에 대한 포인터가 `nullptr`이 아니다.
     *
     *  @note 단순한 `nullptr` 체크만 수행한다. 실제로 전방 리스트에 속한 노드를
     *  가리키고 있는 것이 아니더라도, 유효한 것으로 간주하므로 주의한다.
     */
    auto IsValid() const -> bool
    {
        return m_cont_ptr != nullptr && m_data_ptr != nullptr;
    }

    /** @brief 반복자가 가리키는 위치를 역참조할 수 있는지 확인한다.
     *  @brief 역참조가 가능하면 `true`, 그렇지 않으면 `false`
     *  @details
     *  역참조가 가능한 반복자의 정의는 아래와 같다.
     *  - 반복자가 유효해야 한다.
     *  - 반복자가 가리키는 위치가 전방 리스트의 끝이 아니어야 한다. (센티널
     *    노드가 아니어야 한다.)
     *
     *  @note \ref IsValid 를 포함하는 검사이므로, 역참조 가능한 반복자라면,
     *  유효한 반복자이다.
     */
    auto IsDereferencible() const -> bool
    {
        // 유효하지 않은 반복자는 역참조할 수 없다.
        if (!IsValid())
            return false;
        return m_data_ptr != m_cont_ptr->GetSentinelPointer();
    }

    /** @brief 주어진 전방 리스트와 반복자가 호환되는지 확인한다.
     *  @param[in] flist 호환성을 확인할 전방 리스트
     *  @return 호환이 되면 `true`, 그렇지 않으면 `false`
     *  @details
     *  전방 리스트와 반복자가 호환되려면 다음을 만족해야 한다.
     *  - 전방 리스트에 대한 포인터가 전달된 전방 리스트의 주소값과 같아야 한다.
     */
    auto IsCompatible(const __ForwardList_t& flist) const -> bool
    {
        // 컨테이너에 대한 포인터에 저장된 값이 전달된 전방 리스트의 주소값과
        // 같은지 확인한다.
        return m_cont_ptr == &flist;
    }

    /// @} // Helper Methods

    /// @{ @name Data Access
public:
    /** @brief 이 반복자가 가리키는 컨테이너의 원소에 대한 상수 포인터를
     *  반환한다.
     *  @return 이 반복자가 가리키는 컨테이너의 원소에 대한 상수 포인터
     *
     *  @note 이 포인터는 반복자가 가리키는 노드에 대한 포인터이다.
     */
    auto GetDataPointer() const -> const Node_S_t* { return m_data_ptr; }

    /// @} // Data Access

public:
    /** @brief 반복자가 가리키는 전방 리스트에 대한 상수 포인터 */
    const __ForwardList_t* m_cont_ptr{nullptr};
    /** @brief 반복자가 가리키는 리스트 내 노드에 대한 상수 포인터 */
    const Node_S_t*        m_data_ptr{nullptr};
};

} // namespace rds

#endif // RDS_FORWARDLIST_CONSTITERATOR_HPP
