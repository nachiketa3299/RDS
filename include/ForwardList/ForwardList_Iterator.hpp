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
    using Node_S_t = typename ForwardList_t::Node_S_t;

public:
    ForwardList_Iterator()                            = default;
    ForwardList_Iterator(const ForwardList_Iterator&) = default;

public:
    ForwardList_Iterator(ForwardList_t* list, Node_S_t* node);
};

RDS_END

RDS_BEGIN
RDS_END

#endif // RDS_FORWARDLIST_ITERATOR_HPP