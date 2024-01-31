#ifndef RDS_VECTOR_H
#define RDS_VECTOR_H

#include "RDS_CoreDefs.h"

RDS_BEGIN

class Vector
{
protected:
    using VE_t = float;
    inline static constexpr VE_t INIT_VAL = 0.f;
    inline static constexpr VE_t DEFAULT_EQUALITY_THRESHOLD = 0.000001f;
    inline static constexpr VE_t DEFAULT_NORMALIZE_THRESHOLD = 0.000001f;
};

RDS_END

#endif // RDS_VECTOR_H