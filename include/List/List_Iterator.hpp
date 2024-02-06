#ifndef RDS_LIST_ITERATOR
#define RDS_LIST_ITERATOR

#include "List_ConstIterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T>
class List_Iterator: public List_ConstIterator<T>
{
};

RDS_END

#endif // RDS_LIST_ITERATOR