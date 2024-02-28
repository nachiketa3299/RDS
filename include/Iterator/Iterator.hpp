/// @file Iterator.hpp

#ifndef RDS_ITERATOR_HPP
#define RDS_ITERATOR_HPP

#include "RDS_CoreDefs.h"
#include "RDS_Tags.h"

#include "List.hpp"

RDS_BEGIN

// clang-format off
template < class __IteratorTag_t
         , class __Value_t
         , class __Pointer_t
         , class __Reference_t
         , class __Difference_t>
struct Iterator
{
    // clang-format on

    using IteratorTag_t = __IteratorTag_t;
    using Value_t       = __Value_t;
    using Pointer_t     = __Pointer_t;
    using Reference_t   = __Reference_t;
    using Difference_t  = __Difference_t;
};

template <class __Iterator_t>
struct IteratorTraits
{
    using IteratorTag_t = typename __Iterator_t::IteratorTag_t;
    using Value_t       = typename __Iterator_t::Value_t;
    using Pointer_t     = typename __Iterator_t::Pointer_t;
    using Reference_t   = typename __Iterator_t::Reference_t;
    using Difference_t  = typename __Iterator_t::Difference_t;
};

// 포인터 형식의 반복자에 대한 특성을 나타내는 템플릿 특수식
// 이지만... 필요성이 느껴질 때에 쓰도록 하자.
// template <class __T_t>
// struct IteratorTraits<__T_t*>
// {
//     using IteratorTag_t = RDS_TAG_ RandomAccessIterator;
//     using Value_t       = __T_t;
//     using Pointer_t     = __T_t*;
//     using Reference_t   = __T_t&;
//     using Difference_t  = PointerDifference_t;
// };

RDS_END

RDS_BEGIN

namespace impl
{
template <class __BidirectionalIterator_t>
auto DistanceBetween(__BidirectionalIterator_t first,
                     __BidirectionalIterator_t last,
                     RDS_TAG_                  BidirectionalIterator) ->
    typename IteratorTraits<__BidirectionalIterator_t>::Difference_t
{
    typename IteratorTraits<__BidirectionalIterator_t>::Difference_t distance =
        0;
    for (; first.operator!=(last); first.operator++(), ++distance) {}
    return distance;
}

template <class __RandomAccessIterator_t>
auto DistanceBetween(__RandomAccessIterator_t first,
                     __RandomAccessIterator_t last,
                     RDS_TAG_                 RandomAccessIterator) ->
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
    return impl::DistanceBetween(first, last,
                                 IteratorTraits<__Iterator_t>::IteratorTag_t());
}

RDS_END

// @todo 언젠가 C++ Concepts를 이용해 구현하고 싶다.
#endif // RDS_ITERATOR_HPP
