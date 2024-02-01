#ifndef RDS_IARRAY_H
#define RDS_IARRAY_H

#include <cstddef>

#include "Array_Iterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T, std::size_t Size>
class IArray
{
public: // Iterators
    virtual Array_Iterator<T, Size> Begin() = 0;
    virtual Array_Iterator<T, Size> End() = 0;
    virtual Array_Iterator<T, Size> CBegin() = 0;
    virtual Array_Iterator<T, Size> CEnd() = 0;

public: // Capacity
    virtual std::size_t Size() const = 0;
    virtual std::size_t MaxSize() const = 0;
    virtual bool Empty() const = 0;

public: // Element Access
    virtual T& operator[](std::size_t pos) = 0;
    virtual const T& operator[](std::size_t pos) const = 0;
    virtual T& At(std::size_t pos) = 0;
    virtual const T& At(std::size_t pos) const = 0;
    virtual T& Front() = 0;
    virtual const T& Front() const = 0;
    virtual T& Back() = 0;
    virtual const T& Back() const = 0;

public: // Modifiers
    virtual void Fill(const T& val) = 0;
    virtual void Swap(IArray& other) = 0;
};

RDS_END

#endif // RDS_IARRAY_H