#ifndef RDS_ARRAY_HPP
#define RDS_ARRAY_HPP

#include <cstddef>

#include "Array_Iterator.hpp"
#include "IArray.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T, std::size_t Size>
class Array: public IArray<T, Size>
{
public:
    using Iterator_t = Array_Iterator<T, Size>;
    using Size_t = std::size_t;

public: // Iterators
    Iterator_t Begin() override
    {}
    Iterator_t End() override
    {}
    Iterator_t CBegin() override
    {}
    Iterator_t CEnd() override
    {}

public: // Capacity
    Size_t Size() const override
    {
        return Size;
    }
    Size_t MaxSize() const override
    {
        return Size;
    }
    bool Empty() const override
    {
        return (Size == 0);
    }

public: // Element Access
    T& operator[](std::size_t pos) override
    {
        return m_ptr[pos];
    }
    const T& operator[](std::size_t pos) const override
    {
        return m_ptr[pos];
    }
    T& At(std::size_t pos) override
    {
        return operator[pos];
    }

    const T& At(std::size_t pos) const override
    {
        return operator[pos];
    }
    T& Front() override
    {
        return operator[0];
    }
    const T& Front() const override
    {
        return operator[0];
    }
    T& Back() override
    {
        return operator[Size - 1];
    }
    const T& Back() const override
    {
        return operator[Size - 1];
    }

public: // Modifiers
    void Fill(const T& val) override
    {
        for (int i = 0; i < Size(); ++i)
            operator[i] = val;
    }
    void Swap(IArray& other) override
    {}

private:
    T m_ptr[Size];
};

RDS_END

#endif // RDS_ARRAY_HPP
