#ifndef RDS_VECTOR_ITERATOR_HPP
#define RDS_VECTOR_ITERATOR_HPP

#include "RDS_CoreDefs.h"
#include "Vector_ConstIterator.hpp"

RDS_BEGIN

template <typename Cont_t>
class Vector_Iterator: public Vector_ConstIterator<Cont_t>
{
};

RDS_END

#endif // RDS_VECTOR_ITERATOR_HPP