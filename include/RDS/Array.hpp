#ifndef RDS_ARRAY_HPP
#define RDS_ARRAY_HPP

#include <initializer_list>

#include "RDS_CoreDefs.h"

#include "Array_Iterator.hpp"

namespace rds
{

/** @brief 정적 크기를 가지는 배열 템플릿 클래스
 *  @tparam __T_t 배열 원소의 자료형
 *  @tparam __Size_v 배열의 크기
 *  @details 원시 배열에 대한 래퍼 클래스이다.
 */
template <class __T_t, std::size_t __Size_v>
class Array
{
public:
    using Value_t      = __T_t;
    using Pointer_t    = __T_t*;
    using Reference_t  = __T_t&;
    using Difference_t = std::ptrdiff_t;

public:
    using Size_t = std::size_t;

public:
    using Iterator_t      = Array_Iterator<Array>;
    using ConstIterator_t = Array_ConstIterator<Array>;

public:
    /** @brief 기본 생성자 */
    Array()                                = default;
    /** @brief 기본 복사 생성자 */
    Array(const Array&)                    = default;
    /** @brief 기본 이동 생성자 */
    Array(Array&&)                         = default;
    /** @brief 기본 복사 대입 연산자 */
    auto operator=(const Array&) -> Array& = default;
    /** @brief 기본 이동 대입 연산자 */
    auto operator=(Array&&) -> Array&      = default;
    /** @brief 기본 소멸자  */
    ~Array()                               = default;

    /** @brief 배열의 초기 값을 지정하는 생성자 */
    Array(const Value_t& init_val)
    {
        for (Size_t i = 0; i < __Size_v; ++i)
            m_ptr[i] = init_val;
    }

    /** @brief 초기화 리스트를 받는 생성자
     *  @param[in] ilist 초기화 리스트
     */
    Array(std::initializer_list<Value_t> ilist)
    {
        for (Size_t i = 0; i < __Size_v; ++i)
            m_ptr[i] = *(ilist.begin() + i);
    }

    /** @brief 초기화 리스트를 받는 대입 연산자
     *  @param[in] ilist 초기화 리스트
     *  @return 연산 이후 이 배열에 대한 참조
     */
    auto operator=(const std::initializer_list<Value_t>& ilist)
        -> Array&; // TODO

    /// @{ @name Access

public:
    /** @brief 전달된 인덱스 번호의 배열 원소에 대한 참조를 반환한다.
     *  @param[in] index 배열 원소에 대한 인덱스
     *
     *  @note 인덱스의 범위 검사를 하지 않으므로, 주의한다.
     */
    auto operator[](Size_t index) const -> const Value_t&
    {
        return m_ptr[index];
    }

    /** @copydoc operator[](Size_t) const */
    auto operator[](Size_t index) -> Value_t&
    {
        return const_cast<Value_t&>(
            static_cast<const Array&>(*this).operator[](index));
    }

    /** @brief 전달된 인덱스 번호의 배열 원소에 대한 참조를 반환한다.
     *
     *  @warning Debug 구성에서 인덱스의 범위가 배열의 크기를 벗어나느 경우
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto At(Size_t index) const -> const Value_t&
    {
        RDS_Assert(IsValidOffset(index) && "Index out of range.");

        return operator[](index);
    }

    /** @copydoc At(Size_t)
     *
     */
    auto At(Size_t index) -> Value_t&
    {
        return const_cast<Value_t&>(static_cast<const Array&>(*this).At(index));
    }

    /** @brief 첫 번째 원소에 대한 참조를 반환한다.
     *  @return 첫 번째 원소에 대한 참조
     */
    auto Front() const -> const Value_t& { return operator[](0); }

    /** @copydoc Front() const
     *
     */
    auto Front() -> Value_t&
    {
        return const_cast<__T_t&>(
            static_cast<const Array<__T_t, __Size_v>&>(*this).Front());
    }

    /** @brief 마지막 원소에 대한 참조를 반환한다.
     *  @brief 마지막 원소에 대한 참조
     */
    auto Back() const -> const Value_t& { return operator[](__Size_v - 1); }

    /** @copydoc Back() const
     *
     */
    auto Back() -> Value_t&
    {
        return const_cast<__T_t&>(
            static_cast<const Array<__T_t, __Size_v>&>(*this).Back());
    }

    /** @brief 센티넬 원소에 대한 상수 포인터를 반환한다. */
    auto GetSentinelPointer() const -> const Value_t* { return m_ptr; }

    /// @} // Access

    /// @{ @name Iterators

public:
    /** @brief 첫 번째 원소를 가리키는 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 반복자
     */
    auto Begin() const -> ConstIterator_t { return ConstIterator_t(this, 0); }

    /** @copydoc Begin() const
     *
     */
    auto Begin() -> Iterator_t { return Iterator_t(this, 0); }

    /** @brief 끝을 가리키는 반복자를 반환한다.
     *  @return 끝을 가리키는 반복자
     *  @exception
     *  역참조 하면 안된다. Debug 구성에서는 비정상 종료하며, Release 구성에서는
     *  Undefined Behavior 이다.
     */
    auto End() const -> ConstIterator_t
    {
        return ConstIterator_t(this, __Size_v);
    }

    /** @copydoc End() const
     *
     */
    auto End() -> Iterator_t { return Iterator_t(this, __Size_v); }

    /** @brief 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 상수 반복자
     */
    auto CBegin() const -> ConstIterator_t { return ConstIterator_t(this, 0); }

    /** @brief 끝을 가리키는 상수 반복자를 반환한다.
     *  @return 끝을 가리키는 상수 반복자
     */
    auto CEnd() const -> ConstIterator_t
    {
        return ConstIterator_t(this, __Size_v);
    }

    /// @} // Iterators

    /// @{ @name Capacity

public:
    /** @brief 배열의 크기를 반환한다.
     *  @return 배열의 크기
     */
    auto Size() const -> Size_t { return __Size_v; }

    /** @brief 배열의 최대 크기를 반환한다.
     *  @return 배열의 최대 크기
     *  @note 정적 배열이므로 \ref Size() 와 같은 값을 반환한다.
     */
    auto MaxSize() const -> Size_t { return __Size_v; }

    // TODO 특수화
    /** @brief 배열이 비어있는지 확인한다.
     *  @return 배열이 비어있으면 `true`, 그렇지 않으면 `false`
     */
    auto Empty() const -> bool { return __Size_v == 0; }

    /// @} // Capacity

    /// @{ @name Operations

public:
    /** @brief 인자로 전달된 컨테이너와 이 컨테이너의 내용을 서로 바꾼다.
     *  @param[in] other 바꿀 대상이 되는 다른 컨테이너
     *  @details 한쪽이 비어있는 경우에도 정상 작동한다.
     */

    auto Swap(Array& other) -> void
    {
        // TODO 그냥 포인터만 이동하는 건 안되나?
        for (Size_t i = 0; i < __Size_v; ++i)
        {
            const auto temp = m_ptr[i];
            m_ptr[i]        = other.m_ptr[i];
            other.m_ptr[i]  = temp;
        }
    }

    /** @brief 배열의 모든 원소를 주어진 값으로 채운다.
     *  @param[in] val 채울 값
     */
    auto Fill(const Value_t& val) -> void
    {
        for (Size_t i = 0; i < __Size_v; ++i)
            m_ptr[i] = val;
    }

    /// @} // Operations

    /// @{ @name Comparators

public:
    /** @brief 두 배열의 동등성을 비교한다.
     *  @param other 비교할 배열
     *  @return 두 배열가 같으면 `true`, 그렇지 않으면 `false`
     *  @details 동등 비교 순서는 다음과 같다.\n
     *  1. 두 배열의 크기가 0이라면,항상 같은 배열이다.
     *  2. 두 배열의 크기가 0이 아니라면, 두 배열의 각 원소를 순회하며 모든
     *  원소가 같은 경우 같은 배열이고, 그렇지 않으면 다른 배열이다.
     */
    auto operator==(const Array& other) const -> bool
    {
        for (int i = 0; i < __Size_v; ++i)
        {
            if (m_ptr[i] != other.operator[](i))
                return false;
        }
        return true;
    }

    /** @brief 두 배열의 비동등성을 비교한다.
     *  @see \ref operator==(const Array&) const
     */
    auto operator!=(const Array& other) const -> bool
    {
        return !operator==(other);
    }

    /// @} // Comparators

    /// @{ @name Helper Methods

public:
    /** @brief 전달된 오프셋이 유효한지 확인한다.
     *  @return 오프셋이 유효하면 `true`, 그렇지 않으면 `false`
     *  @details 오프셋의 크기가 배열의 크기보다 작을 때, 유효하다.
     */
    auto IsValidOffset(Size_t offset) const -> bool
    {
        return offset < __Size_v;
    }

    /// @} // Helper Methods

private:
    /** @brief 래핑된 크기 `__Size_v`의원시 배열 */
    Value_t m_ptr[__Size_v];
};

} // namespace rds

#endif // RDS_ARRAY_HPP
