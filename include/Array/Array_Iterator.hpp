#ifndef RDS_ARRAY_ITERATOR_H
#define RDS_ARRAY_ITERATOR_H

#include <cstddef>

#include "Array_ConstIterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T, std::size_t Size>
class Array_Iterator: public Array_ConstIterator<T, Size>
{
public:
    using Super  = Array_ConstIterator<T, Size>;
    using Val_t  = typename Super::Val_t;
    using Diff_t = typename Super::Diff_t;
    using Size_t = std::size_t;
    using VE_t   = T;

public:
    /// @brief Default Constructor.
    Array_Iterator()
    {}

    /// @brief Constructor gets head pointer of array & offset.
    explicit Array_Iterator(Val_t* head, Size_t index = 0)
        : Super(head, index)
    {}

public:
    VE_t& operator*() const
    {
        return const_cast<VE_t&>(Super::operator*());
    }
    VE_t* operator->() const
    {
        return const_cast<VE_t*>(Super::operator->());
    }
    Array_Iterator& operator++()
    {
        Super::operator++();
        return *this;
    }
    Array_Iterator operator++(int)
    {
        const auto temp = operator*();
        Super::operator++();
        return temp;
    }
    Array_Iterator& operator--()
    {
        Super::operator--();
        return *this();
    }
    Array_Iterator operator--(int)
    {
        const auto temp = operator*();
        Super::operator--();
        return temp;
    }
    Array_Iterator& operator+=(const Diff_t offset)
    {
        Super::operator+=(offset);
        return *this();
    }
    Array_Iterator operator+(const Diff_t offset) const
    {
        auto temp = operator*();
        return temp.operator+=(offset);
    }
    Array_Iterator& operator-=(const Diff_t offset)
    {
        Super::operator-=(offset);
        return *this();
    }
    Array_Iterator operator-(const Diff_t offset)
    {
        auto temp = *this;
        return temp.operator-=(offset);
    }
};

RDS_END

#endif // RDS_ARRAY_ITERATOR_H