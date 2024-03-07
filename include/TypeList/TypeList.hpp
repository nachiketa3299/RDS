#ifndef RDS_TYPELIST_HPP
#define RDS_TYPELIST_HPP

#include "RDS_CoreDefs.h"

namespace rds
{

template <class... __Types_t>
class TypeList
{};

// Front

namespace impl
{
template <class __TypeList_t>
class Front;

template <class __Head_t, class... __Tail_t>
class Front<TypeList<__Head_t, __Tail_t...>>
{
public:
    using Type_t = __Head_t;
};
} // namespace impl

template <class __TypeList_t>
using Front = typename impl::Front<__TypeList_t>::Type_t;

// PopFront

namespace impl
{
template <class __TypeList_t>
class PopFront;

template <class __Head_t, class... __Tail_t>
class PopFront<TypeList<__Head_t, __Tail_t...>>
{
public:
    using Type_t = TypeList<__Tail_t...>;
};
} // namespace impl

template <class __TypeList_t>
using PopFront = typename impl::PopFront<__TypeList_t>::Type_t;

// PushFront
namespace impl
{
template <class __TypeList_t, class __NewElementType_t>
class PushFront;

template <class... __Elements_t, class __NewElementType_t>
class PushFront<TypeList<__Elements_t...>, __NewElementType_t>
{
public:
    using Type_t = TypeList<__NewElementType_t, __Elements_t...>;
};
} // namespace impl

template <class __TypeList_t, class __NewElementType_t>
using PushFront =
    typename impl::PushFront<__TypeList_t, __NewElementType_t>::Type_t;

// Indexing

namespace impl
{
template <class __TypeList_t, std::size_t __Index_v>
class Get: public Get<PopFront<PopFront<__TypeList_t>, __Index_v - 1>>
{};

template <class __TypeList_t>
class Get<__TypeList_t, 0>: public Front<__TypeList_t>
{};

} // namespace impl

template <class __TypeList_t, std::size_t __Index_v>
using Get = typename impl::Get<__TypeList_t, __Index_v>::Type_t;

} // namespace rds

#endif // RDS_TYPELIST_HPP