#ifndef RDS_ARRAY_H
#define RDS_ARRAY_H

#include <array>
#include <cstddef>

#include "Array_ConstIterator.hpp"
#include "Array_Iterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Static-sized array template class
/// @tparam type of array's each element
/// @tparam Size size of array
template <class _T, std::size_t Size_>
class Array
{
public:
    /// @brief Element type
    using Val_t  = _T;
    using Size_t = std::size_t;

public:
    using Iterator      = Array_Iterator<Val_t, Size_>;
    using ConstIterator = Array_ConstIterator<Val_t, Size_>;

public:
    Array() = default;

    /// @brief Copy Constructor
    /// @todo see stl <array>
    Array(const Array& other)
    {
        for (int i = 0; i < Size_; ++i)
            m_ptr[i] = other[i];
    }

public: // Element Access
    Val_t&       operator[](Size_t index);
    const Val_t& operator[](Size_t index) const;
    Val_t&       At(Size_t index);
    const Val_t& At(Size_t index) const;

    Val_t& Front()
    {
        return m_ptr[0];
    }

    const Val_t& Front() const
    {
        return m_ptr[0];
    }

    Val_t& Back()
    {
        return m_ptr[Size_ - 1];
    }

    const Val_t& Back() const
    {
        return m_ptr[Size_ - 1];
    }

public:
    /// @brief 시작 지점 (index = 0) 에 대한 반복자를 생성하여 반환한다.
    Iterator Begin()
    {
        return Iterator(m_ptr, 0);
    }

    /// @brief 시작 지점 (index = 0) 에 대한 상수 반복자를 생성하여 반환한다.
    ConstIterator Begin() const
    {
        return ConstIterator(m_ptr, 0);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 반복자를 생성하여 반환한다.
    Iterator End()
    {
        return Iterator(m_ptr, Size_);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 상수 반복자를 생성하여 반환한다.
    ConstIterator End() const
    {
        return ConstIterator(m_ptr, Size_);
    }

    /// @brief 시작 지점 (index = 0) 에 대한 반복자를 생성하여 반환한다.
    ConstIterator CBegin() const
    {
        return ConstIterator(m_ptr, 0);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 상수 반복자를 생성하여 반환한다.
    ConstIterator CEnd() const
    {
        return ConstIterator(m_ptr, Size_);
    }

public:
    Size_t Size() const
    {
        return Size_;
    }

    Size_t MaxSize() const
    {
        return Size_;
    }

    bool Empty() const
    {
        return false;
    }

private:
    Val_t m_ptr[Size_];
};

/// @brief Specialization in @p Size_ = 0 for template class @ref Array
template <typename T>
class Array<T, 0>
{
public:
    bool IsEmpty() const
    {
        return true;
    }
};

RDS_END

RDS_BEGIN

template <class _T, std::size_t Size_>
inline auto Array<_T, Size_>::operator[](Size_t index) -> Val_t&
{
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class _T, std::size_t Size_>
inline auto Array<_T, Size_>::operator[](Size_t index) const -> const Val_t&
{
    return m_ptr[index];
}

template <class _T, std::size_t Size_>
inline auto Array<_T, Size_>::At(Size_t index) -> Val_t&
{
    RDS_Assert(index < Size_);
    return const_cast<Val_t&>(static_cast<const Array&>(*this).operator[](index));
}

template <class _T, std::size_t Size_>
inline auto Array<_T, Size_>::At(Size_t index) const -> const Val_t&
{
    RDS_Assert(index < Size_);
    return operator[](index);
}

RDS_END

#endif // RDS_ARRAY_H