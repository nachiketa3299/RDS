/// @file Iterator.hpp

#ifndef RDS_ITERATOR_HPP
#define RDS_ITERATOR_HPP

#include "List.hpp"
#include "RDS_CoreDefs.h"
#include <concepts>
#include <iterator>

RDS_BEGIN

/*! @brief 출력 반복자(Output Iterator)를 나타내는 태그
    @details
    - 컨테이너를 한 번 전방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 있다.\n
    - 가리키는 값을 읽을 수 없다.
*/
struct OuputIterator_Tag
{};

/*! @brief 입력 반복자(Input Iterator)를 나타내는 태그
    @details
    - 컨테이너를 한 번 전방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 없다.\n
    - 가리키는 값을 읽을 수 있다.
*/
struct InputIterator_Tag
{};

/*! @brief 전방 반복자(Forward Iterator)를 나타내는 태그
    @details
    - 컨테이너를 여러 번 전방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 있다.\n
    - 가리키는 값을 읽을 수 있다.
*/
struct ForwardIterator_Tag: InputIterator_Tag
{};

/*! @brief 양방향 반복자(Bidirectional Iterator)를 나타내는 태그
    @details
    - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 있다.\n
    - 가리키는 값을 읽을 수 있다.
*/
struct BidirectionalIterator_Tag: ForwardIterator_Tag
{};

/*! @brief 임의 접근 반복자(Random Access Iterator)를 나타내는 태그
    @details
    - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 있다.\n
    - 가리키는 값을 읽을 수 있다.\n
    - 컨테이너의 요소에 비순차적으로 접근할 수 있다.
*/
struct RandomAccessIterator_Tag: BidirectionalIterator_Tag
{};

/*! @brief 연속 반복자(Contiguous Iterator)를 나타내는 태그
    @details
    - 컨테이너를 여러 번 전후방으로 스캔할 수 있다.\n
    - 가리키는 값에 쓸 수 있다.\n
    - 가리키는 값을 읽을 수 있다.\n
    - 컨테이너의 요소에 비순차적으로 접근할 수 있다.\n
    - 컨테이너의 논리적으로 인접한 요소가 물리적으로도 인접해 있다.
*/
struct ContiguosIterator_Tag: RandomAccessIterator_Tag
{};

// template <class __IteratorCategory_t, class __Value_t, class __Pointer_t,
//           class __Reference_t, class __Difference_t>
// struct Iterator
// {
//     using IteratorCategory_t;
//     using Value_t;
//     using Pointer_t;
//     using Reference_t;
//     using Difference_t;
// };

template <class __Iterator_t>
struct IteratorTraits
{
    using IteratorCategoty_t = typename __Iterator_t::IteratorCategory_t;
    using Value_t            = typename __Iterator_t::Value_t;
    using Pointer_t          = typename __Iterator_t::Pointer_t;
    using Reference_t        = typename __Iterator_t::Reference_t;
    using Difference_t       = typename __Iterator_t::Difference_t;
};

/// @brief 포인터 형식의 반복자에 대한 특성을 나타내는 템플릿 특수식
template <class __T_t>
struct IteratorTraits<__T_t*>
{
    using IteratorCategory_t = RandomAccessIterator_Tag;
    using Value_t            = __T_t;
    using Pointer_t          = __T_t*;
    using Reference_t        = __T_t&;
    using Difference_t       = PointerDifference_t;
};

RDS_END

RDS_BEGIN

namespace impl
{
template <class __BidirectionalIterator_t>
auto DistanceBetween(__BidirectionalIterator_t first,
                     __BidirectionalIterator_t last, BidirectionalIterator_Tag)
    -> typename IteratorTraits<__BidirectionalIterator_t>::Difference_t
{
    typename IteratorTraits<__BidirectionalIterator_t>::Difference_t distance =
        0;
    for (; first.operator!=(last); first.operator++(), ++distance) {}
    return distance;
}

template <class __RandomAccessIterator_t>
auto DistanceBetween(__RandomAccessIterator_t first,
                     __RandomAccessIterator_t last, RandomAccessIterator_Tag) ->
    typename IteratorTraits<__RandomAccessIterator_t>::Difference_t
{
    return last - first; // last.operator-(first);
}
} // namespace impl

template <class __Iterator_t>
auto DistanceBetween(__Iterator_t first, __Iterator_t last) ->
    typename IteratorTraits<__Iterator_t>::Difference_t
{
    /// (Tag Dispatch) 태그를 만들어서 태그에 맞는 함수가 호출되도록 한다.
    return impl::DistanceBetween(
        first, last, IteratorTraits<__Iterator_t>::IteratorCategory_t());
}

RDS_END

// @todo 언젠가 C++ Concepts를 이용해 구현하고 싶다.
#endif // RDS_ITERATOR_HPP
