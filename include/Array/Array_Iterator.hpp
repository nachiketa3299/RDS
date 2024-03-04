#ifndef RDS_ARRAY_ITERATOR_HPP
#define RDS_ARRAY_ITERATOR_HPP

#include "Array_ConstIterator.hpp"

namespace rds
{

/** @brief \ref Array 컨테이너에 대한 반복자 템플릿 클래스
 *  @tparam __Array_t 이 반복자가 가리킬 배열 자료형
 *  @see \ref Array_ConstIterator
 */
template <class __Array_t>
class Array_Iterator: public Array_ConstIterator<__Array_t>
{
public:
    /** @brief 이 반복자의 기초 클래스 */
    using Super_t = Array_ConstIterator<__Array_t>;
    using Size_t  = typename Super_t::Size_t;

    /// @{ @name Iterator Traits

public:
    using Value_t      = typename Super_t::Value_t;
    using Pointer_t    = typename Super_t::Pointer_t;
    using Reference_t  = typename Super_t::Reference_t;
    using Difference_t = typename Super_t::Difference_t;

    /// @} // Iterator Traits

public:
    /** @brief 기본 생성자 */
    Array_Iterator()                      = default;
    /** @brief 기본 복사 생성자 */
    Array_Iterator(const Array_Iterator&) = default;
    /** @brief 기본 소멸자 */
    ~Array_Iterator()                     = default;

    /** @brief 배열에 대한 포인터와 원소에 대한 인덱스를 받는 생성자
     *  @param cont_ptr 반복자가 가리키는 배열에 대한 포인터
     *  @param index 반복자가 가리키는 원소에 대한 인덱스
     *
     *  @warning 인덱스가 배열의 범위를 벗어나는 경우 정의되지 않은 행동이다.
     */
    explicit Array_Iterator(const __Array_t* cont_ptr, Size_t index)
        : Super_t(cont_ptr, index)
    {}

    /// @{ @name Input & Output Iterator Operations

public:
    /** @copydoc Array_ConstIterator::operator*()
     *
     */
    auto operator*() const -> Value_t&
    {
        return const_cast<Value_t&>(Super_t::operator*());
    }

    /** @copydoc Array_ConstIterator::operator->()
     *
     */
    auto operator->() const -> Value_t*
    {
        return const_cast<Value_t*>(Super_t::operator->());
    }

    /// @} // Input & Output Iterator Operations

    /// @{ @name Forward Iterator Operations

public:
    /** @copydoc Array_ConstIterator::operator++()
     *
     */
    auto operator++() -> Array_Iterator&
    {
        Super_t::operator++();
        return *this;
    }

    /** @copydoc Array_ConstIterator::operator++(int)
     *
     */
    auto operator++(int) -> Array_Iterator
    {
        const auto temp = *this;
        Super_t::operator++();
        return temp;
    }

    /// @} // Forward Iterator Operations

    /// @{ @name Bidirectional Iterator Operations

public:
    /** @copydoc Array_ConstIterator::operator--()
     *
     */
    auto operator--() -> Array_Iterator&
    {
        Super_t::operator--();
        return *this;
    }

    /** @copydoc Array_ConstIterator::operator--(int)
     *
     */
    auto operator--(int) -> Array_Iterator
    {
        const auto temp = *this;
        Super_t::operator--();
        return temp;
    }

    /// @} // Bidirectional Iterator Operations

    /// @{ @name Random Access Iterator Operations

public: 
    /** @copydoc Array_ConstIterator::operator+=
     *
     */
    auto operator+=(const Difference_t offset) -> Array_Iterator&
    {
        Super_t::operator+=(offset);
        return *this;
    }

    /** @copydoc Array_ConstIterator::operator+
     *
     */
    auto operator+(const Difference_t offset) const -> Array_Iterator
    {
        auto temp = *this;
        return temp.operator+=(offset);
    }

    /** @copydoc Array_ConstIterator::operator-=
     *
     */
    auto operator-=(const Difference_t offset) -> Array_Iterator&
    {
        Super_t::operator-=(offset);
        return *this;
    }

    /** @copydoc Array_ConstIterator::operator-
     *
     */
    auto operator-(const Difference_t offset) -> Array_Iterator
    {
        auto temp = *this;
        return temp.operator-=(offset);
    }

    /// @} // Random Access Iterator Operations

    /// @{ @name Data Access

public: 
    /** @brief 이 반복자가 가리키는 컨테이너의 원소에 대한 포인터를
     *  반환한다.
     *  @return 이 반복자가 가리키는 컨테이너의 원소에 대한 포인터
     */
    auto GetDataPointer() const -> Value_t*
    {
        return const_cast<Value_t*>(Super_t::GetDataPointer());
    }

    /// @} // Data Access
};

} // namespace rds

#endif // RDS_ARRAY_ITERATOR_HPP
