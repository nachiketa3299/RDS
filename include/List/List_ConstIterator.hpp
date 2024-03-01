/// @file List_ConstIterator.hpp

#ifndef RDS_LIST_CONSTITERATOR_HPP
#define RDS_LIST_CONSTITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "Assertion.h"
#include "Iterator.hpp"

RDS_BEGIN

/** @brief `List` 컨테이너에 대한 상수 반복자 템플릿 클래스
 *  @tparam __List_t 이 상수 반복자가 가리킬 리스트에 대한 자료형
 *  @note 양방향 반복자이다.
 */
// clang-format off
template <class __List_t>
class List_ConstIterator
    : public Iterator< RDS_TAG_ BidirectionalIterator
                     , typename __List_t::Value_t
                     , typename __List_t::Pointer_t
                     , typename __List_t::Reference_t
                     , typename __List_t::Difference_t>
{
public:
    using Node_D_t = typename __List_t::Node_D_t;

    /// @{ @name Iterator Traits
public:
    using Iterator_t = Iterator< RDS_TAG_ BidirectionalIterator
                               , typename __List_t::Value_t
                               , typename __List_t::Pointer_t
                               , typename __List_t::Reference_t
                               , typename __List_t::Difference_t>;
    // clang-format on
    using IteratorTag_t = typename Iterator_t::IteratorTag_t;
    using Value_t       = typename Iterator_t::Value_t;
    using Pointer_t     = typename Iterator_t::Pointer_t;
    using Reference_t   = typename Iterator_t::Reference_t;
    using Difference_t  = typename Iterator_t::Difference_t;

    /// @}

public:
    /** @brief 기본 생성자 */
    List_ConstIterator()                                    = default;
    /** @brief 기본 복사 생성자 */
    List_ConstIterator(const List_ConstIterator<__List_t>&) = default;
    /** @brief 기본 복사 대입 연산자 */
    auto operator=(const List_ConstIterator<__List_t>&)
        -> List_ConstIterator<__List_t>&               = default;
    /** @brief 기본 이동 생성자 */
    List_ConstIterator(List_ConstIterator<__List_t>&&) = default;
    /** @brief 기본 이동 대입 연산자 */
    auto operator=(List_ConstIterator<__List_t>&&)
        -> List_ConstIterator<__List_t>& = default;
    /** @brief 기본 소멸자 */
    ~List_ConstIterator()                = default;

    /** @brief 리스트 내 노드 위치와 리스트 자체에 대한 포인터를 받는 생성자
     * @param cont_ptr 이 상수 반복자가 가리키는 리스트 자체에 대한 포인터
     * @param node_pos_ptr 이 상수 반복자가 가리키는 리스트의 노드에 대한 포인터
     */
    explicit List_ConstIterator(const __List_t* cont_ptr,
                                const Node_D_t* node_pos_ptr)
        : m_cont_ptr(cont_ptr)
        , m_data_ptr(node_pos_ptr)
    {}

public:
    /**
     * @brief 이 상수 반복자가 가리키는 리스트 노드내 값에 대한 상수 참조를
     * 반환한다.
     * @exception
     * - Debug 구성에서 이 반복자가 역참조가 불가능한 경우 비정상 종료한다. \n
     * - Release 구성에서는 Undefined Behavior이다.
   /// @todo 역참조가 불가능한 경우에 대해 Release 구성에서 예외를 던지게 한다면
     * 더 좋을 것 같다.
     */
    auto operator*() const -> const Value_t&
    {
        RDS_Assert(IsDereferencible() &&
                   "Cannot dereference invalid iterator.");
        return m_data_ptr->val;
    }

    /** @brief 이 상수 반복자가 가리키는 리스트 노드내 값에 대한 상수 포인터수를
     * 반환한다.
     *  @return 이 상수 반복자가 가리키는 리스트 노드내 값에 대한 상수 포인터
     */
    auto operator->() const -> const Value_t*
    {
        /// @todo 여기서 무슨 일이 일어나고 있는지 정확히 설명할 수 있어야
        /// 합니다.
        return std::pointer_traits<
            const typename __List_t::Value_t*>::pointer_to(operator*());
    }

    /// @{ @name Forward Iterator Operations
public:
    /** @brief 이 반복자가 가리키는 위치를 하나 증가시킨다.
     *  @return 연산 후 이 반복자에 대한 참조
     *  @details 현재 노드가 센티넬 노드가 아닌 경우에만 연산을 수행한다.
     *  @exception Debug 구성에서 현재 노드가 센티넬 노드인 경우 비정상
     *  종료한다. Release 구성에서는 Undefined Behavior이다.
    /// @todo Release 구성에서 예외를 던지게 한다면 더 좋을 것 같다.
     */
    auto operator++() -> List_ConstIterator&
    {
        RDS_Assert(m_data_ptr != m_cont_ptr->GetSentinelPointer() &&
                   "Cannot increment end iterator.");

        m_data_ptr = m_data_ptr->next;
        return *this;
    }

    /** @copybrief `operator++()`
     *  @return 연산 전 이 반복자에 대한 사본
     *  @details `operator++()`를 내부에서 호출한다.
     */
    auto operator++(int) -> List_ConstIterator
    {
        const auto temp = *this;
        operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations
    /// @{ @name Bidirectional Iterator Operation

    /** @brief 이 반복자가 가리키는 위치를 하나 감소시킨다.
     *  @return 연산 후 이 반복자에 대한 참조
     *  @exception
     *  반복자가 가리키는 노드의 이전 노드가 센티넬 노드인 경우, \n
     *  - Debug 구성에서는 비정상 종료한다. \n
     *  - Release 구성에서는 Undefined Behavior이다.
     */
    auto operator--() -> List_ConstIterator&
    {
        // 이전 노드가 센티넬 노드가 아닌 경우에만 감소 연산을 수행한다.
        RDS_Assert(m_data_ptr->prev != m_cont_ptr->GetSentinelPointer() &&
                   "Cannot decrement begin iterator.");

        m_data_ptr = m_data_ptr->prev;
        return *this;
    }

    /** @copybrief `operator--()`
     *  @return 연산 전 이 반복자에 대한 사본
     *  @details `operator--()`를 내부에서 호출한다.
     */
    auto operator--(int) -> List_ConstIterator
    {
        const auto temp = *this;
        operator--();
        return temp;
    }

    /// @} // Bidirectional Iterator Operation

public:
    /** @brief 두 반복자가 같은지 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 같은 경우 `true`, 그렇지 않으면 `false`
     *  @details
     *  두 반복자의 동등성은 다음의 두 조건을 만족할 때 성립한다.\n
     *  - 두 반복자가 같은 리스트를 가리키고 있다. \n
     *  - 두 반복자가 같은 노드를 가리키고 있다.
     *  @exception
    /// @todo 유효성 여부에 대해서 다시 알아볼 필요가 있다. 기존 설명은 노드와
    반복자에 대한 주소가 모두 `nullptr`이면 같은 것으로 취급한다고 작성하였는데,
    실제로 그런지 확인해 볼 필요가 있다.
     */
    auto operator==(const List_ConstIterator<__List_t>& other) const -> bool
    {
        return IsCompatible(*other.m_cont_ptr) &&
               (m_data_ptr == other.m_data_ptr);
    }

    /** @brief 두 반복자가 다른지 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 다른 경우 `true`, 그렇지 않으면 `false`
     *  @details `operator==()`의 반대 결과를 반환한다.
     */
    auto operator!=(const List_ConstIterator<__List_t>& other) const -> bool
    {
        return !(operator==(other));
    }

    // 반복자가 역참조 가능한 경우, 유효하다.
public: // Helper Functions
    /** @brief 반복자가 유효한지 확인한다.
     *  @details
     *  반복자가 유효하려면 다음의 두 조건을 만족해야 한다.\n
     *  - 이 반복자가 가리키는 리스트에 대한 포인터가 `nullptr`이 아니다. \n
     *  - 이 반복자가 가리키는 리스트 내 노드에 대한 포인터가 `nullptr`이
     *  아니다.
     *  @note 단순히 `nullptr` 체크만 수행한다. 만일 실제로 리스트에 속한 노드의
     *  주소를 가지고 있는게 아니더라도, 유효한 것으로 간주하므로 주의한다.
     */
    auto IsValid() const -> bool
    {
        return m_cont_ptr != nullptr && m_data_ptr != nullptr;
    }

    /** @brief 반복자가 가리키는 위치를 역참조할 수 있는지 확인한다.
     *  @brief 역참조가 가능하면 `true`, 그렇지 않으면 `false`
     *  @details
     *  역참조가 가능하려면 다음의 두 조건을 만족해야 한다.\n
     *  - 반복자가 유효해야 한다. \n
     *  - 반복자가 리스트의 센티넬 노드를 가리키고 있지 않아야 한다.
     *  @note `IsValid`를 포함하는 검사이므로, 역참조 가능한 반복자라면, 유효한
     *  반복자이다.
     */
    auto IsDereferencible() const -> bool
    {
        if (!IsValid())
            return false;
        return m_data_ptr != m_cont_ptr->GetSentinelPointer();
    }

    /** @brief 리스트와 반복자의 호환성 여부를 확인한다.
     *  @param[in] list 호환성을 확인할 리스트
     *  @return 호환이 되면 `true`, 그렇지 않으면 `false`
     *  @details
     *  리스트와 반복자가 호환되려면 다음을 만족해야 한다.\n
     *  - 리스트에 대한 포인터에 저장된 값이 전달된 리스트의 주소값과 같아야
     *  한다.
     */
    auto IsCompatible(const __List_t& list) const -> bool
    {
        return m_cont_ptr == &list;
    }

public: // Data Access
    /** @brief 반복자가 가리키는 노드에 대한 상수 포인터를 반환한다.
     *  @return 반복자가 가리키는 노드에 대한 상수 포인터
     */
    auto GetDataPointer() const -> const Node_D_t* { return m_data_ptr; }

protected:
    /** @brief 반복자가 가리키는 리스트에 대한 상수 포인터 */
    const __List_t* m_cont_ptr{nullptr};
    /** @brief 반복자가 가리키는 리스트 내 노드에 대한 상수 포인터 */
    const Node_D_t* m_data_ptr{nullptr};
};

RDS_END

#endif // RDS_LIST_CONSTITERATOR_HPP