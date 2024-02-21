/// @file Vector_Iterator.hpp

#ifndef RDS_VECTOR_ITERATOR_HPP
#define RDS_VECTOR_ITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "Vector_ConstIterator.hpp"

RDS_BEGIN

template <typename Vector_t>
class Vector_Iterator: public Vector_ConstIterator<Vector_t>
{
public:
    using Super = Vector_ConstIterator<Vector_t>;

public:
    using Value_t      = typename Vector_t::Value_t;
    using Size_t       = typename Vector_t::Size_t;
    using Difference_t = typename Vector_t::Difference_t;

public:
    Vector_Iterator()                                 = default;
    Vector_Iterator(const Vector_Iterator<Vector_t>&) = default;
    ~Vector_Iterator()                                = default;

public:
    Vector_Iterator(const Vector_t* cont_ptr, Size_t index);

public:
    auto operator*() -> Value_t&;
    auto operator->() -> Value_t*;

public:
    auto operator++() -> Vector_Iterator&;
    auto operator++(int) -> Vector_Iterator&;
    auto operator--() -> Vector_Iterator&;
    auto operator--(int) -> Vector_Iterator&;

public:
    auto operator+=(const Difference_t& offset) -> Vector_Iterator&;
    auto operator+(const Difference_t& offset) -> Vector_Iterator;
    auto operator-=(const Difference_t& offset) -> Vector_Iterator&;
    auto operator-(const Difference_t& offset) -> Vector_Iterator;

public:
    auto GetDataPoinert() -> Value_t*;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <typename Vector_t>
inline Vector_Iterator<Vector_t>::Vector_Iterator(const Vector_t* cont_ptr,
                                                  Size_t          index)
    : Super(cont_ptr, index)
{}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator*() -> Value_t&
{
    return const_cast<Value_t&>(Super::operator*());
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator->() -> Value_t*
{
    return const_cast<Value_t*>(Super::operator->());
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator++() -> Vector_Iterator&
{
    Super::operator++();
    return *this;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator++(int) -> Vector_Iterator&
{
    const auto temp = *this;
    Super::operator++();
    return temp;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator--() -> Vector_Iterator&
{
    Super::operator--();
    return *this;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator--(int) -> Vector_Iterator&
{
    const auto temp = *this;
    Super::operator--();
    return temp;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator+=(const Difference_t& offset)
    -> Vector_Iterator&
{
    Super::operator+=(offset);
    return *this;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator+(const Difference_t& offset)
    -> Vector_Iterator
{
    auto temp = *this;
    return temp.operator+=(offset);
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator-=(const Difference_t& offset)
    -> Vector_Iterator&
{
    Super::operator-=(offset);
    return *this;
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::operator-(const Difference_t& offset)
    -> Vector_Iterator
{
    auto temp = *this;
    return temp.operator-=(offset);
}

template <typename Vector_t>
inline auto Vector_Iterator<Vector_t>::GetDataPoinert() -> Value_t*
{
    return const_cast<Value_t*>(Super::GetDataPointer());
}

RDS_END

#endif // RDS_VECTOR_ITERATOR_HPP
