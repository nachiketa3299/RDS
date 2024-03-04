// TODO 컨테이너별로 테스트 할 것

#ifndef RDS_ITERATOR_HPP
#define RDS_ITERATOR_HPP

#include <type_traits> // is_base_of_v

#include "RDS_Tags.h"

namespace rds
{

/** @brief 모든 반복자의 기본 구조체
 *  @tparam __IteratorTag_t 반복자의 태그
 *  @tparam __Value_t 반복자가 가리키는 값의 자료형
 *  @tparam __Pointer_t 반복자의 포인터 자료형
 *  @tparam __Reference_t 반복자의 참조 자료형
 *  @tparam __Difference_t 반복자의 차이값 자료형
 *  @details 컨테이너의 모든 반복자들은 이 구조체를 상속해야 한다.
 */
// clang-format off
template < class __IteratorTag_t
         , class __Value_t
         , class __Pointer_t
         , class __Reference_t
         , class __Difference_t>
// clang-format on
struct Iterator
{

    using IteratorTag_t = __IteratorTag_t;
    using Value_t       = __Value_t;
    using Pointer_t     = __Pointer_t;
    using Reference_t   = __Reference_t;
    using Difference_t  = __Difference_t;
};

/** @brief 반복자에 대한 특성을 추출하는 인터페이스
 *  @tparam __Iterator_t 반복자의 자료형
 */
template <class __Iterator_t>
struct IteratorTraits
{
    using IteratorTag_t = typename __Iterator_t::IteratorTag_t;
    using Value_t       = typename __Iterator_t::Value_t;
    using Pointer_t     = typename __Iterator_t::Pointer_t;
    using Reference_t   = typename __Iterator_t::Reference_t;
    using Difference_t  = typename __Iterator_t::Difference_t;
};

/** @brief 두 반복자 사이의 거리를 구한다
 *  @tparam __Iterator_t 반복자의 자료형
 *  @param[in] first 첫 번째 요소를 가리키는 반복자
 *  @param[in] last 마지막 요소를 가리키는 반복자
 *  @return 두 반복자 사이의 거리
 *  @details
 *  `first` 부터 `last` 까지 몇 홉 거리인지 계산한다.
 *
 *  ### Complexity
 *  - 입력 반복자인 경우, 복잡도는 두 반복자의 거리에 선형으로 비례한다.
 *  - 임의 접근 반복자인 경우, 복잡도는 상수 시간에 비례한다. 또한, 거리의 값이
 *    음수가 될 수도 있다.
 *
 *  @warning - 입력 반복자를 사용할 경우, `first` → `last` 경로가 존재하지 않는
 경우 정의되지 않은 행동이다.
 *  @warning - 임의 접근 반복자를 사용하는 경우, `first` → `last` 경로가
 존재하지 않거나 `last` → `first` 경로가 존재하지 않는 경우, 정의되지 않은
 행동이다.
 */
template <class __InputIterator_t>
auto DistanceBetween(__InputIterator_t first, __InputIterator_t last) ->
    typename IteratorTraits<__InputIterator_t>::Difference_t
{
    using This_IteratorTag_t =
        typename IteratorTraits<__InputIterator_t>::IteratorTag_t;
    static_assert(std::is_base_of_v<tag::InputIterator, This_IteratorTag_t>);

    if constexpr (std::is_base_of_v<tag::RandomAccessIterator,
                                    This_IteratorTag_t>)
        return last - first;
    else
    {
        typename IteratorTraits<__InputIterator_t>::Difference_t distance = 0;

        while (first.operator!=(last))
        {
            first.operator++();
            ++distance;
        }

        return distance;
    }
}

/** @brief 반복자를 주어진 거리만큼 전진시킨다.
 *  @tparam __InputIterator_t 반복자의 자료형
 *  @param[in] it 전진시킬 반복자
 *  @param[in] n 전진시킬 거리
 *  @exception
 *  반복자의 자료형이 양방향 반복자 미만인 경우, Undefined Behavior이다.
 *  @details
 *  - 반복자의 자료형이 양방향 반복자 이상인 경우, `n`이 음수일 수 있으며 이
 *  경우 반복자는 `n` 만큼 후진한다.
 *  ### Complexity
 *  - 입력 반복자인 경우, 복잡도는 `n`에 선형으로 비례한다.
 *  - 임의 접근 반복자 이상인 경우, 복잡도는 상수 시간에 비례한다.
 */
template <class __InputIterator_t, class __Distance_t>
auto Advance(__InputIterator_t& it, __Distance_t n) -> void
{
    using This_IteratorTag_t =
        typename IteratorTraits<__InputIterator_t>::IteratorTag_t;
    static_assert(std::is_base_of_v<tag::InputIterator, This_IteratorTag_t>);

    // 반복자 종류에 따라서 이게 음수일수도, 양수일 수도 있다.
    auto distance = typename IteratorTraits<__InputIterator_t>::Difference_t(n);

    // 임의 접근 반복자 이상인 경우 그냥 더하면 상수 시간에 끝
    if constexpr (std::is_base_of_v<tag::RandomAccessIterator,
                                    This_IteratorTag_t>)
    {
        it.operator+=(distance);
    }

    else
    {
        // 대상: 임의 접근 반복자 미만
        while (distance > 0)
        {
            --distance;
            it.operator++();
        }

        if constexpr (std::is_base_of_v<tag::BidirectionalIterator,
                                        This_IteratorTag_t>)
        {
            // 대상: 임의 접근 반복자 미만, distance가 음수인 경우
            while (distance < 0)
            {
                ++distance;
                it.operator--();
            }
        }
    }
}

/** @brief `n` 번째 이후 반복자를 반환한다.
 *  @tparam __InputIterator_t 반복자의 자료형
 *  @param[in] it 다음 반복자를 구할 대상 반복자
 *  @param[in] n 다음 반복자의 거리
 *  @return `n` 번째 이후 반복자의 사본
 *  @details
 *  ### Complexity
 *  - 반복자의 자료형이 임의 접근 반복자인 경우 상수 시간, 그 외의 경우 `n`에
 *    선형으로 비례한다.
 */
template <class __InputIterator_t>
constexpr auto
Next(__InputIterator_t                                        it,
     typename IteratorTraits<__InputIterator_t>::Difference_t n = 1)
    -> __InputIterator_t
{
    Advance(it, n);
    return it;
}

/** @brief `n` 번째 이전 반복자를 반환한다.
 *  @tparam __BidirectionalIterator_t 반복자의 자료형
 *  @param[in] it 이전 반복자를 구할 대상 반복자
 *  @param[in] n 이전 반복자의 거리
 *  @return `n` 번째 이전 반복자의 사본
 *  @details
 *  ### Comlexity
 *  - 반복자의 자료형이 임의 접근 반복자인 경우 상수 시간, 그 외의 경우 `n`에
 *    선형으로 비례한다.
 */
template <class __BidirectionalIterator_t>
constexpr auto
Previous(__BidirectionalIterator_t                                        it,
         typename IteratorTraits<__BidirectionalIterator_t>::Difference_t n = 1)
    -> __BidirectionalIterator_t
{
    Advance(it, -n);
    return it;
}

} // namespace rds

#endif // RDS_ITERATOR_HPP