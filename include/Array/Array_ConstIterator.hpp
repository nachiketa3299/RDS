#ifndef RDS_ARRAY_CONSTITERATOR_H
#define RDS_ARRAY_CONSTITERATOR_H

#include <cstddef>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @class Array
/// @brief Template class for Static-sized array's const iterator.
/// @tparam T  value type for element in array
/// @tparam Size size of array
template <typename T, std::size_t Size>
class Array_ConstIterator
{
public:
    /// @brief value type for element in array
    using Val_t  = T;
    /// @brief difference type
    using Diff_t = std::ptrdiff_t;
    /// @brief size type
    using Size_t = std::size_t;

public:
    /// @brief Default Constructor.
    Array_ConstIterator()
        : m_head{nullptr}
        , index{0}
    {}
    /// @brief Constructor gets head pointer from an array and index
    Array_ConstIterator(const Val_t* head, Size_t index)
        : m_head(head)
        , m_offset(index)
    {}

private:
    /// @brief
    /// @todo WTF this means? (case for offset < 0 && offset > 0)
    void verifyOffset(const Diff_t offset)
    {
        if (offset != 0)
            RDS_Assert(m_head != nullptr);
        if (offset < 0)
            RDS_Assert(m_offset >= Size_t{0} - static_cast<Size_t>(offset));
        if (offset > 0)
            RDS_Assert(Size_t - m_offset >= static_cast<Size_t>(offset));
    }
    void isCompatible(const Array_ConstIterator& other)
    {
        RDS_Assert(m_head == other.m_head);
        return;
    }

public:
    /// @brief Dereferencing operator
    const Val_t& operator*() const
    {
        return *(operator->());
    }
    const Val_t* operator->() const
    {
        RDS_Assert(m_head != nullptr);
        RDS_Assert(m_offset < Size);
        return m_head + m_offset;
    }

public:
    /// @brief Prefix increment
    Val_t& operator++()
    {
        /// @todo validation test for head?
        ++m_offset;
        return operator*();
    }
    /// @brief Postfix increment
    Val_t operator++(int)
    {
        const auto temp = *this;
        operator++();
        return temp;
    }
    /// @brief Prefix decrement
    Val_t& operator--()
    {
        --m_offset;
        return operator*();
    }
    /// @brief Postfix decrement
    Val_t operator--(int)
    {
        const auto temp = *this;
        operator--();
        return operator*();
    }

public:
    Array_ConstIterator& operator+=(const Diff_t& offset)
    {
        verifyOffset(offset);
        m_offset += static_cast<Size_t>(offset);
        return operator*();
    }
    Array_ConstIterator operator+(const Diff_t& offset) const
    {
        auto temp = operator*();
        return temp.operator+=(offset);
    }
    Array_ConstIterator& operator-=(const Diff_t& offset)
    {
        verifyOffset(offset);
        m_offset -= static_cast<Size_t>(offset);
        return operator*();
    }
    Array_ConstIterator operator-(const Diff_t& offset) const
    {
        auto temp = operator*();
        return temp.operator-=(offset);
    }
    Diff_t operator-(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return static_cast<Diff_t>(m_offset - other.m_offset);
    }
    bool operator==(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return m_offset == other.m_offset;
    }
    bool operator!=(const Array_ConstIterator& other) const
    {
        return !(operator==(other));
    }
    bool operator<(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return m_offset < other.m_offset;
    }
    bool operator>(const Array_ConstIterator& other) const
    {
        return other.operator<(*this);
    }
    bool operator<=(const Array_ConstIterator& other) const
    {
        return !operator>(other);
    }
    bool operator>=(const Array_ConstIterator& other) const
    {
        return !operator<(other);
    }

private:
    Val_t* m_head;   //< head of array
    Size_t m_offset; //< offset from head of array
};

RDS_END

#endif // RDS_ARRAY_CONSTITERATOR_H