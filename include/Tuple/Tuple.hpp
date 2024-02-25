/// @file Tuple.hpp

#ifndef RDS_TUPLE_HPP
#define RDS_TUPLE_HPP

#include <cstddef>
#include <tuple>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <class T_t>
struct Tuple_Val
{
    Tuple_Val();
    T_t value{};
};

template <class This_T_t, class... Rest_T_ts>
class Tuple: private Tuple<Rest_T_ts...>
{
public:
    using This_Value_t = This_T_t;

public:
    Tuple()             = default;
    Tuple(const Tuple&) = default;
    Tuple(Tuple&&)      = default;

public:
};

RDS_END

RDS_BEGIN
RDS_END

#endif // RDS_TUPLE_HPP