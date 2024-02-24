/// @file ForwardList_Iterator.hpp

#ifndef RDS_FORWARDLIST_ITERATOR_HPP
#define RDS_FORWARDLIST_ITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "ForwardList_ConstIterator.hpp"

RDS_BEGIN

template <class ForwardList_t>
class ForwardList_Iterator: public ForwardList_ConstIterator<ForwardList_t>
{
public:
    using Super_t = ForwardList_ConstIterator<ForwardList_t>;

public:
    using Value_t  = typename ForwardList_t::Value_t;
    using Size_t   = typename ForwardList_t::Size_t;
    using Node_S_t = typename ForwardList_t::Node_S_t;

public:
    ForwardList_Iterator()                            = default;
    ForwardList_Iterator(const ForwardList_Iterator&) = default;
    ~ForwardList_Iterator()                           = default;

public:
    explicit ForwardList_Iterator(const ForwardList_t* flist_ptr,
                                  const Node_S_t*      snode_ptr);

public:
    auto operator*() const -> Value_t&;
    auto operator->() const -> Value_t*;

public:
    auto operator++() -> ForwardList_Iterator&;
    auto operator++(int) -> ForwardList_Iterator;
};

RDS_END

// IMPLEMENTATION //

RDS_BEGIN

template <class ForwardList_t>
inline ForwardList_Iterator<ForwardList_t>::ForwardList_Iterator(
    const ForwardList_t* flist_ptr, const Node_S_t* snode_ptr)
    : Super_t(flist_ptr, snode_ptr)
{}

template <class ForwardList_t>
inline auto ForwardList_Iterator<ForwardList_t>::operator*() const -> Value_t&
{
    return const_cast<Value_t&>(Super_t::operator*());
}

template <class ForwardList_t>
inline auto ForwardList_Iterator<ForwardList_t>::operator->() const -> Value_t*
{
    return const_cast<Value_t*>(Super_t::operator->());
}

template <class ForwardList_t>
inline auto ForwardList_Iterator<ForwardList_t>::operator++()
    -> ForwardList_Iterator&
{
    Super_t::operator++();
    return *this;
}

template <class ForwardList_t>
inline auto ForwardList_Iterator<ForwardList_t>::operator++(int)
    -> ForwardList_Iterator
{
    const auto temp = *this;
    operator++();
    return temp;
}

RDS_END

#endif // RDS_FORWARDLIST_ITERATOR_HPP
