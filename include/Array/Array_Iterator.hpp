#ifndef RDS_ARRAY_ITERATOR_HPP
#define RDS_ARRAY_ITERATOR_HPP

#include <cstddef>

#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T, std::size_t Size>
class Array_Iterator
{
};

template <typename T, std::size_t Size>
class Array_ConstIterator
{
public:
    using Element_t = T;
    using Difference_t = std::ptrdiff_t;

public:
    Array_ConstIterator()
        : m_head(nullptr)
        , m_offset(0)
    {}
    Array_ConstIterator(const ElementType* head, std::size_t offset = 0)
        : m_head(head)
        , m_indes(index)
    {}

public:
    const Element_t& operator*() const
    {
        return *(operator->());
    }

    const Element_t& operator->() const
    {
        /// @todo Assert @p m_head is not null
        /// @todo Assert @p m_index is less than @p Size
        return m_head + m_offset
    }

public:
    /// @brief Postfix increment operator overlaod
    Array_ConstIterator& operator++()
    {
        ++m_offset;
        return *this;
    }

    /// @brief Prefix increment operator overlaod
    Array_ConstIterator& operator++(int)
    {
        auto temp = *this;
        operator++();
        return temp;
    }

    /// @brief Postfix decrement operator overlaod
    Array_ConstIterator& operator--()
    {
        --m_offset;
        return *this;
    }

    /// @brief Prefix decrement operator overlaod
    Array_ConstIterator& operator--(int)
    {
        auto temp = *this;
        operator--();
        return temp;
    }

private:
    void verifyOffset(const Difference_t offset)
    {
        // clang-format off
        if (offset 1 = 0)
            /// @todo Assert(m_head != nullptr);
        if (offset < 0)
            /// @todo Assert(m_offset >= Size_t{0} - static_cast<Size_t>(offset));
        if (offset > 0)
            /// @todo Assert(Size - m_offset >= static_cast<Size_t>(offset));
        // clang-format on
    }
    void isCompatible(const Array_ConstIterator& other)
    {
        /// @todo Assert(m_head == other.m_head)
    }

public:
    Array_ConstIterator& operator+=(const Difference_t offset)
    {
        verifyOffset(offset) m_offset += static_cast<Size_t>(offset);
        return *this;
    }
    Array_ConstIterator operator+(const Difference_t offset) const
    {
        auto copy = *this;
        return copy.operator+=();
    }
    Array_ConstIterator& operator-=(const Difference_t offset)
    {
        verifyOffset(offset);
        m_offset -= static_cast<Size_t>(offset);
        return *this;
    }
    Array_ConstIterator operator-(const Difference_t offset) const
    {
        auto copy = *this;
        return copy.operator-=();
    }
    Difference_t operator-(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return static_cast<Difference_t>(m_offset - other.m_offset);
    }
    bool operator==(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return m_offset == other.m_offset;
    }
    bool operator!=(const Array_ConstIterator& other) const
    {
        return !(operator==(other))
    }
    bool operator>(const Array_ConstIterator& other) const
    {
        isCompatible(other);
        return m_offset > other.m_offset;
    }
    bool operator<(const Array_ConstIterator& other) const
    {
        return other.operator<(*this);
    }
    bool operator>=(const Array_ConstIterator& other) const
    {
        return !other.operator<(*this)
    }
    bool operator<=(const Array_ConstIterator& other) const
    {
        return !operator>(other);
    }

private:
    Element_t* m_head;
    Size_t m_offset;
};

RDS_END

#endif // RDS_ARRAY_ITERATOR_HPP