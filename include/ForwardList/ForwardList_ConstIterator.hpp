/// @file ForwardList_ConstIterator.hpp

#ifndef RDS_FORWARDLIST_CONSTITERATOR_HPP
#define RDS_FORWARDLIST_CONSTITERATOR_HPP

#include "RDS_CoreDefs.h"

RDS_BEGIN

template <class ForwardList_t>
class ForwardList_ConstIterator
{
public:
    using Value_t  = typename ForwardList_t::Value_t;
    using Node_S_t = typename ForwardList_t::Node_S_t;

public:
    ForwardList_ConstIterator()                                 = default;
    ForwardList_ConstIterator(const ForwardList_ConstIterator&) = default;

public:
    ForwardList_ConstIterator(const ForwardList_t* list, const Node_S_t* node);
};

RDS_END

RDS_BEGIN
RDS_END

#endif // RDS_FORWARDLIST_CONSTITERATOR_HPP