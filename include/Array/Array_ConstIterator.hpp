#ifndef RDS_ARRAY_CONSTITERATOR_HPP
#define RDS_ARRAY_CONSTITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "Assertion.h"
#include "Iterator.hpp"

namespace rds
{

/** @brief \ref Array 컨테이너에 대한 상수 반복자 템플릿 클래스
 *  @tparam __Array_t 이 상수 반복자가 가리킬 배열 자료형
 *  @details 임의 접근 반복자이다.
 */
// clang-format off
template <class __Array_t>
class Array_ConstIterator
    : public Iterator< tag::RandomAccessIterator
                        , typename __Array_t::Value_t
                        , typename __Array_t::Pointer_t
                        , typename __Array_t::Reference_t
                        , typename __Array_t::Difference_t>
{
public:
    using Size_t = typename __Array_t::Size_t;

    /// @{ @name Iterator Traits
public:
    using Iterator_t = Iterator< tag::RandomAccessIterator
                               , typename __Array_t::Value_t
                               , typename __Array_t::Pointer_t
                               , typename __Array_t::Reference_t
                               , typename __Array_t::Difference_t>;

    // clang-format on

    using IteratorTag_t = typename Iterator_t::IteratorTag_t;
    using Value_t       = typename Iterator_t::Value_t;
    using Pointer_t     = typename Iterator_t::Pointer_t;
    using Reference_t   = typename Iterator_t::Reference_t;
    using Difference_t  = typename Iterator_t::Difference_t;

    /// @} // Iterator Traits

public:
    /** @brief 기본 생성자 */
    Array_ConstIterator()                                 = default;
    /** @brief 기본 복사 생성자 */
    Array_ConstIterator(const Array_ConstIterator& other) = default;
    /** @brief 기본 소멸자 */
    ~Array_ConstIterator()                                = default;

    /** @brief 컨테이너에 대한 포인터와 원소에 대한 인덱스를 받는 생성자
     *  @param cont_ptr 반복자가 가리키는 컨테이너에 대한 포인터
     *  @param index 반복자가 가리키는 원소에 대한 인덱스
     *
     *  @warning 인덱스가 컨테이너의 범위를 벗어나는 경우 정의되지 않은
     *  행동이다.
     */
    explicit Array_ConstIterator(const __Array_t* cont_ptr, Size_t index)
        : m_cont_ptr(cont_ptr)
        , m_data_offset(index)
    {}

    /// @{ @name Input & Ouput Iterator Operations
public:
    /** @brief 이 반복자가 가리키는 원소에 대한 참조를 반환한다.
     *
     *  @warning Debug 구성에서 이 반복자가 역참조가 불가능한 경우 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator*() const -> const Value_t&
    {
        RDS_Assert(IsDereferencible() &&
                   "Cannot dereference iterator out of range.");

        return *(operator->());
    }

    /** @brief 이 반복자가 가리키는 원소에 대한 포인터를 반환한다.
     *  @return 이 반복자가 가리키는 원소에 대한 포인터
     */
    auto operator->() const -> const Value_t*
    {
        return m_cont_ptr->GetSentinelPointer() + m_data_offset;
    }

    // TODO 유효하지 않은 반복자에 대한 동등성 비교 테스트할 것
    /** @brief 두 반복자의 동등성을 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 같은 경우 `true`, 그렇지 않으면 `false`
     *  @details
     *  두 반복자의 동등성은 다음과 같이 정의한다.
     *  - 두 반복자가 같은 리스트를 가리키고 있다.
     *  - 두 반복자가 같은 노드를 가리키고 있다.
     */
    auto operator==(const Array_ConstIterator& other) const -> bool
    {
        RDS_Assert(IsCompatible(*other.m_cont_ptr) &&
                   "Incompatible iterators.");
        return m_data_offset == other.m_data_offset;
    }

    /** @brief 두 반복자의 비동등성을 비교한다.
     *  @param[in] other 비교할 반복자
     *  @return 두 반복자가 다른 경우 `true`, 그렇지 않으면 `false`
     *  @see \ref operator==
     */
    auto operator!=(const Array_ConstIterator& other) const -> bool
    {
        return !(operator==(other));
    }

    /// @} // Input Iterator Operations

    /// @{ @name Forward Iterator Operations
public:
    /** @brief 이 반복자가 가리키는 위치를 하나 증가시킨다
     *  @return 연산 후 이 반복자에 대한 참조
     *
     *  @warning Debug 구성에서 이 반복자가 배열의 끝 위치를 넘어서는 경우
     * 비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator++() -> Array_ConstIterator&
    {
        ++m_data_offset;
        RDS_Assert(IsValidPos() && "Iterator out of range.");
        return *this;
    }

    /** @overload
     *  @return 연산 전 이 반복자에 대한 사본
     */
    auto operator++(int) -> Array_ConstIterator
    {
        const auto temp = *this;
        operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations

    /// @{ @name Bidirectional Iterator Operations
public:
    /** @brief 이 반복자가 가리키는 위치를 하나 감소시킨다
     *  @return 연산 후 이 반복자에 대한 참조
     *
     *  @warning 현재 노드의 이전 노드가 센티넬 노드인 경우, Debug 구성에서는
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator--() -> Array_ConstIterator&
    {
        --m_data_offset;
        RDS_Assert(IsValidPos() && "Iterator out of range.");
        return *this;
    }

    /** @overload
     *  @return 연산 전 이 반복자에 대한 사본
     */
    auto operator--(int) -> Array_ConstIterator
    {
        const auto temp = *this;
        operator--();
        return temp;
    }

    /// @} // Bidirectional Iterator Operations

    /// @{ @name Random Access Iterator Operations

public:
    /** @brief 이 반복자가 가리키는 위치를 주어진 값만큼 증가시킨다.
     *  @param[in] offset 증가시킬 값
     *  @return 연산 후 이 반복자에 대한 참조
     *
     *  @warning Debug 구성에서 연산의 결과로 반복자가 배열의 끝 이후에 위치하는
     *  경우 비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator+=(const Difference_t offset) -> Array_ConstIterator&
    {
        m_data_offset += static_cast<Size_t>(offset);
        RDS_Assert(IsValidPos() && "Iterator out of range.");
        return *this;
    }

    /** @copybrief operator+=
     *  @param[in] offset 증가시킬 값
     *  @return 연산 전 이 반복자에 대한 사본
     *
     *  @see \ref operator+=
     */
    auto operator+(const Difference_t offset) const -> Array_ConstIterator
    {
        auto temp = *this;
        return temp.operator+=(offset);
    }

    /** @brief 이 반복자가 가리키는 위치를 주어진 값만큼 감소시킨다.
     *  @param[in] offset 감소시킬 값
     *  @return 연산 후 이 반복자에 대한 참조
     *
     *  @warning Debug 구성에서 연산의 결과로 배열의 시작 이전에 위치하는 경우
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator-=(const Difference_t offset) -> Array_ConstIterator&
    {
        m_data_offset -= static_cast<Size_t>(offset);
        RDS_Assert(IsValidPos() && "Iterator out of range.");
        return *this;
    }

    /** @copybrief operator-=
     *  @param[in] offset 감소시킬 값
     *  @return 연산 전 이 반복자에 대한 사본
     *
     *  @see \ref operator-=
     */
    auto operator-(const Difference_t offset) -> Array_ConstIterator
    {
        auto temp = *this;
        return temp.operator-=(offset);
    }

    /** @brief 이 반복자와 다른 반복자 간의 차이를 계산한다.
     *  @param[in] other 차이를 계산할 다른 반복자
     *  @return 이 반복자와 다른 반복자 간의 차이
     *
     *  @warning Debug 구성에서 두 반복자가 호환되지 않는 경우 비정상 종료하고,
     *  Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator-(const Array_ConstIterator& other) const -> Difference_t
    {
        RDS_Assert(IsCompatible(*other.m_cont_ptr) &&
                   "Incompatible iterators.");
        return static_cast<Difference_t>(m_data_offset - other.m_data_offset);
    }

    /** @brief 이 반복자가 다른 반복자보다 앞에 위치하는지 비교한다.
     *  @param[in] other 비교할 다른 반복자
     *  @return 이 반복자가 다른 반복자보다 앞에 위치하는 경우 `true`, 그렇지
     *  않으면 `false`
     *
     *  @warning Debug 구성에서 두 반복자가 호환되지 않는 경우 비정상 종료하고,
     *  Release 구성에서는 정의되지 않은 행동이다.
     */
    auto operator<(const Array_ConstIterator& other) const -> bool
    {
        RDS_Assert(IsCompatible(*other.m_cont_ptr) &&
                   "Incompatible iterators.");
        return m_data_offset < other.m_data_offset;
    }

    /** @brief 이 반복자가 다른 반복자보다 뒤에 위치하는지 비교한다.
     *  @param[in] other 비교할 다른 반복자
     *  @return 이 반복자가 다른 반복자보다 뒤에 위치하는 경우 `true`, 그렇지
     *  않으면 `false`
     *
     *  @see \ref operator<
     */
    auto operator>(const Array_ConstIterator& other) const -> bool
    {
        return other.operator<(*this);
    }

    /** @brief 이 반복자가 다른 반복자보다 앞에 위치하거나 같은지 비교한다.
     *  @param[in] other 비교할 다른 반복자
     *  @return 이 반복자가 다른 반복자보다 앞에 위치하거나 같은 경우 `true`,
     * 그렇지 않으면 `false`
     *
     *  @see \ref operator<
     */
    auto operator<=(const Array_ConstIterator& other) const -> bool
    {
        return !operator>(other);
    }

    /** @brief 이 반복자가 다른 반복자보다 뒤에 위치하거나 같은지 비교한다.
     *  @param[in] other 비교할 다른 반복자
     *  @return 이 반복자가 다른 반복자보다 뒤에 위치하거나 같은 경우 `true`,
     * 그렇지 않으면 `false`
     *
     *  @see \ref operator<
     */
    auto operator>=(const Array_ConstIterator& other) const -> bool
    {
        return !operator<(other);
    }

    /// @} // Random Access Iterator Operations

    /// @{ @name Helpers Methods

private:
    /** @brief 이 반복자가 유효한지 검사한다.
     *  @return 유효한 반복자이면 `true`, 그렇지 않으면 `false`
     *  @details
     *  유효한 반복자에 대한 정의는 아래와 같다.
     *  - 배열에 대한 포인터가 `nullptr`이 아니다.
     *
     *  @note 단순한 `nullptr` 체크만 수행한다. 반복자가 가리키는 위치가 배열의
     *  크기를 벗어나더라도, 유효한 것으로 간주하므로 주의한다.
     */
    auto IsValid() const -> bool { return m_cont_ptr != nullptr; }

    /** @brief 이 반복자가 가리키는 위치가 유효한지 검사한다.
     *  @return 유효한 위치이면 `true`, 그렇지 않으면 `false`
     *  @details
     *  유효한 위치에 대한 정의는 아래와 같다.
     *  - 반복자가 가리키는 원소에 대한 인덱스가 배열의 크기보다 작거나 같아야
     *  한다.
     *
     *  @note 단순히 배열의 크기를 벗어나지 않는지만 검사한다. 유효한 배열을
     *  가리키는 반복자가 아닐 수도 있음을 주의한다.
     */
    auto IsValidPos() const -> bool
    {
        return m_data_offset <= m_cont_ptr->Size();
    }

    /** @brief 반복자가 가리키는 위치를 역참조할 수 있는지 확인한다.
     *  @brief 역참조가 가능하면 `true`, 그렇지 않으면 `false`
     *  @details
     *  역참조가 가능한 반복자의 정의는 아래와 같다.
     *  - 반복자가 유효해야 한다.
     *  - 반복자가 가리키는 위치가 유효해야 한다.
     *  - 반복자가 가리키는 위치가 \ref End 가 아니어야 한다.
     *
     *  @note \ref IsValid 와 \ref IsValidPos 를 포함하는 검사이므로, 역참조
     *  가능한 반복자라면, 유효한 컨테이너의, 유효한 위치를 가리키고 있다.
     */
    auto IsDereferencible() const -> bool
    {
        if (!IsValid())
            return false;
        if (!IsValidPos())
            return false;
        return m_data_offset != m_cont_ptr->Size();
    }

    /** @brief 주어진 배열과 반복자가 호환되는지 확인한다.
     *  @param[in] array 호환성을 확인할 배열
     *  @return 호환이 되면 `true`, 그렇지 않으면 `false`
     *  @details
     *  배열과 반복자가 호환되려면 다음을 만족해야 한다.
     *  - 배열에 대한 포인터가 전달된 배열의 주소값과 같아야 한다.
     */
    auto IsCompatible(const __Array_t& array) const -> bool
    {
        return m_cont_ptr == &array;
    }

    /// @} // Helpers

    /// @{ @name Data Access
public:
    /** @brief 이 반복자가 가리키는 컨테이너의 원소에 대한 상수 포인터를
     *  반환한다.
     *  @return 이 반복자가 가리키는 컨테이너의 원소에 대한 상수 포인터
     */
    auto GetDataPointer() const -> const Value_t*
    {
        return m_cont_ptr->GetSentinelPointer() + m_data_offset;
    }

    /// @} // Data Access

protected:
    /** @brief 반복자가 가리키는 배열에 대한 상수 포인터 */
    const __Array_t* m_cont_ptr{nullptr};
    /** @brief 반복자가 가리키는 원소의 인덱스에 대한 값 */
    Size_t           m_data_offset{0};
};

} // namespace rds

#endif // RDS_ARRAY_CONSTITERATOR_HPP
