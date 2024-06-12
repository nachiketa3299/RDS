#ifndef RDS_ALGORITHM_HPP
#define RDS_ALGORITHM_HPP

#include "Functional.hpp"

#include <initializer_list>
#include <utility>

namespace rds
{

#pragma region MinMax

// Dangling Reference 반환하지 않게 하려고 const __T_t&를 반환
// TODO __Compare_t 를 __Compare_t&& 로 받는건 어떨까?
// Callable Object 에 대한 약간의 공부가 더 필요함. (특히 거대한 객체를 캡처하고
// 있는 경우)

template <class __T_t, class __Compare_t>
auto Compare(const __T_t& left, const __T_t& right, __Compare_t compare)
    -> const __T_t&
{
    return compare(left, right) ? left : right;
}

/** @brief 전달된 두 값 중 작은 값을 반환한다.
 *   @note 이 버전의 `Min`은 값을 비교할 때 원소의 `operator<`를 사용한다.
 */
template <class __T_t>
inline auto Min(const __T_t& left, const __T_t& right) -> const __T_t&
{
    return Compare(left, right, Less<__T_t>());
}

/** @overload Min
 *   @note 이 버전의 `Mint은 값을 비교할 때, 주어진 비교자 `compare`를
 *   사용한다.
 */
template <class __T_t, class __Compare_t>
inline auto Min(const __T_t& left, const __T_t& right, __Compare_t compare)
    -> const __T_t&
{
    return Compare(left, right, compare);
}

/** @brief 전달된 두 값 중 큰 값을 반환한다.
 *   @note 이 버전의 `Min`은 값을 비교할 때 원소의 `operator<`를 사용한다.
 */
template <class __T_t>
inline auto Max(const __T_t& left, const __T_t& right) -> const __T_t&
{
    return Compare(left, right, Greater<__T_t>());
}

/** @overload Max
 *   @note 이 버전의 `Max`은 값을 비교할 때, 주어진 비교자 `compare`를
 *   사용한다.
 */
template <class __T_t, class __Compare_t>
inline auto Max(const __T_t& left, const __T_t& right, __Compare_t compare)
    -> const __T_t&
{
    return Compare(left, right, compare);
}

#pragma endregion MinMax

#pragma region MinMaxElement

template <class __Iterator_t>
using Derive_Value_t_From_Iterator_t =
    std::remove_reference_t<decltype(*std::declval<__Iterator_t>())>;

template <class __ForwardIterator_t, class __Compare_t>
auto CompareElement(__ForwardIterator_t it_first, __ForwardIterator_t it_last,
                    __Compare_t compare) -> __ForwardIterator_t
{
    if (it_first == it_last)
        return it_last;

    auto it_target = it_first;

    while (++it_first != it_last)
    {
        if (compare(*it_first, *it_target))
            it_target = it_first;
    }

    return it_target;
}

/** @brief 주어진 범위에서 가장 작은 원소를 가리키는 반복자를 반환한다.
 *   @note 이 버전의 `MinElement`는 주어진 범위의 원소를 비교할 때, 원소의
 *   `operator<`를 사용한다.
 */
template <class __ForwardIterator_t>
inline auto MinElement(__ForwardIterator_t it_first,
                       __ForwardIterator_t it_last) -> __ForwardIterator_t
{
    using Value_t = Derive_Value_t_From_Iterator_t<__ForwardIterator_t>;
    return CompareElement(it_first, it_last, Less<Value_t>());
}

/** @overload MinElement
 *   @note 이 버전의 `MinElement`는 주어진 범위의 원소를 비교할 때, 주어진
 * 비교자 `compare`를 사용한다.
 */
template <class __ForwardIterator_t, class __Compare_t>
inline auto MinElement(__ForwardIterator_t it_first,
                       __ForwardIterator_t it_last, __Compare_t compare)
    -> __ForwardIterator_t
{
    return CompareElement(it_first, it_last, compare);
}

/** @brief 주어진 범위에서 가장 큰 원소를 가리키는 반복자를 반환한다.
 *   @note 이 버전의 `MinElement`는 주어진 범위의 원소를 비교할 때, 원소의
 *   `operator>`를 사용한다.
 */
template <class __ForwardIterator_t>
inline auto MaxElement(__ForwardIterator_t it_first,
                       __ForwardIterator_t it_last) -> __ForwardIterator_t
{
    using Value_t = Derive_Value_t_From_Iterator_t<__ForwardIterator_t>;
    return CompareElement(it_first, it_last, Greater<Value_t>());
}

/** @overload MaxElement
 *   @note 이 버전의 `ManElement`는 주어진 범위의 원소를 비교할 때, 주어진
 * 비교자 `compare`를 사용한다.
 */
template <class __ForwardIterator_t, class __Compare_t>
inline auto MaxElement(__ForwardIterator_t it_first,
                       __ForwardIterator_t it_last, __Compare_t compare)
    -> __ForwardIterator_t
{
    return CompareElement(it_first, it_last, compare);
}

#pragma endregion MinMaxElement

#pragma region Fill

/** @brief 반복자로 주어진 범위의 모든 원소를 주어진 값으로 채운다.
 */
template <class __ForwardIterator_t, class __T_t>
auto Fill(__ForwardIterator_t it_first, __ForwardIterator_t it_last,
          const __T_t& val) -> void
{
    for (; it_first != it_last; ++it_first)
        *it_first = val;
}

/** @brief 주어진 반복자의 위치부터 주어진 갯수만큼의 원소를 값으로 채운다.
 *   @warning 컨테이너의 크기를 넘어서는 인덱스에 접근할 수 있으므로 주의한다.
 */
template <class __OutputIterator_t, class __Size_t, class __T_t>
auto FillN(__OutputIterator_t it_first, __Size_t count, const __T_t& val)
    -> __OutputIterator_t
{
    for (; count > 0; --count)
        *it_first++ = val;
    return it_first;
}

#pragma endregion Fill

} // namespace rds

#endif // RDS_ALGORITHM_HPP