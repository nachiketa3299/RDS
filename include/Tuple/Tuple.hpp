#ifndef RDS_TUPLE_HPP
#define RDS_TUPLE_HPP

namespace rds
{

template <class... __Types_t>
class Tuple
{};

template <class __Head_t, class... __Tail_t>
class Tuple
{
    __Head_t           m_head;
    Tuple<__Tail_t...> m_tail;
};

template <>
class Tuple<>
{};

} // namespace rds

#endif RDS_TUPLE_HPP