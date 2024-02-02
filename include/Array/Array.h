#ifndef RDS_ARRAY_H
#define RDS_ARRAY_H

#include <cstddef>

#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T, std::size_t Size>
class Array
{
public:
    /// @brief Array's element type.
    using Val_t = T;

private:
    T ptr[Size];
};

RDS_END

#endif // RDS_ARRAY_H