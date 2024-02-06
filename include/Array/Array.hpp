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
template <typename T, std::size_t Size_>
class Array
{
public:
    /// @brief Array's element type.
    using Val_t  = T;
    /// @brief Array's size type
    using Size_t = std::size_t;
    using It_t   = Array_Iterator<Val_t, Size_>;
    using CIt_t  = Array_ConstIterator<Val_t, Size_>;

public:
    /// @brief 기본 생성자
    /// @note 쓰레기 값으로 배열이 차게 된다.
    Array() = default;

    /// @brief 복사 생성자
    /// @todo see stl <array>
    Array(const Array& other)
    {
        for (int i = 0; i < Size_; ++i)
            m_ptr[i] = other[i];
    }

public:
    Val_t& operator[](Size_t index)
    {
        return m_ptr[index];
    }

    const Val_t& operator[](Size_t index) const
    {
        return m_ptr[index];
    }

    Val_t& At(Size_t index)
    {
        RDS_Assert(index < Size_);
        return m_ptr[index];
    }

    const Val_t& At(Size_t index) const
    {
        RDS_Assert(index < Size_);
        return m_ptr[index];
    }

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
    It_t Begin()
    {
        return It_t(m_ptr, 0);
    }

    /// @brief 시작 지점 (index = 0) 에 대한 상수 반복자를 생성하여 반환한다.
    CIt_t Begin() const
    {
        return CIt_t(m_ptr, 0);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 반복자를 생성하여 반환한다.
    It_t End()
    {
        return It_t(m_ptr, Size_);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 상수 반복자를 생성하여 반환한다.
    CIt_t End() const
    {
        return CIt_t(m_ptr, Size_);
    }

    /// @brief 시작 지점 (index = 0) 에 대한 반복자를 생성하여 반환한다.
    CIt_t CBegin() const
    {
        return CIt_t(m_ptr, 0);
    }

    /// @brief 끝 지점 (index = Size_) 에 대한 상수 반복자를 생성하여 반환한다.
    CIt_t CEnd() const
    {
        return CIt_t(m_ptr, Size_);
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

#endif // RDS_ARRAY_H