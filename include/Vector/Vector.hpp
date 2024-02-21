/// @file Vector.hpp

#ifndef RDS_VECTOR_HPP
#define RDS_VECTOR_HPP

#include <cstddef>

#include "RDS_CoreDefs.h"

#include "Allocator_Trait.hpp"
#include "Mallocator.hpp"

#include "Vector_ConstIterator.hpp"
#include "Vector_Iterator.hpp"

RDS_BEGIN

/// @brief 동적 배열 클래스
/// @tparam T_t
template <class T_t, class Alloc_t = Mallocator<T_t>>
class Vector
{
public:
    using Allocator_t = Alloc_t;

public: // Type Aliases
    using Value_t      = T_t;
    using Size_t       = std::size_t;
    using Difference_t = std::ptrdiff_t;

public: // Iterator Type Aliases
    using ConstIterator = Vector_ConstIterator<Vector<Value_t>>;
    using Iterator      = Vector_Iterator<Vector<Value_t>>;

public: // Default Ctros
    Vector()              = default;
    Vector(const Vector&) = default;

public:
    Vector(Size_t size, const Value_t& init_val);
    Vector(const std::initializer_list<Value_t>& init_list);

public:
    ~Vector();

public: // Element Access
    auto operator[](Size_t index) const -> const Value_t&;
    auto operator[](Size_t index) -> Value_t&;
    auto At(Size_t index) const -> const Value_t&;
    auto At(Size_t index) -> Value_t&;

public:
    auto Front() const -> const Value_t&;
    auto Front() -> Value_t&;
    auto Back() const -> const Value_t&;
    auto Back() -> Value_t&;

public:
    auto GetSentinelPointer() const -> const Value_t*;

public: // Iterators
    auto Begin() const -> ConstIterator;
    auto Begin() -> Iterator;
    auto End() const -> ConstIterator;
    auto End() -> Iterator;

public:
    auto CBegin() const -> ConstIterator;
    auto CEnd() const -> ConstIterator;

public:
    auto Size() const -> Size_t;
    auto Capacity() const -> Size_t;
    auto MaxSize() const -> Size_t;
    auto Empty() const -> bool;
    auto Reserve(Size_t reserve_size) -> void; // 커지는 쪽으로만 반응함
    auto Resize() -> void;
    auto Shrink() -> void;

public: // cppreference 다시 참고하여 매개변수 형식 확정지을 것
    auto Assign(const Value_t& val, Size_t n)
        -> void; // Iterator 버전은 템플릿으로 구현
    template <class InputIt_t>
    auto Assign(InputIt_t first, InputIt_t last) -> void;
    auto Assign(const std::initializer_list<Value_t>& init_list) -> void;
    auto PushBack(const Value_t& val) -> void;
    auto PopBack() -> void;
    auto Insert(Iterator it_pos, const Value_t&) -> Iterator;
    auto Insert(Iterator it_pos, const Value_t&, Size_t n) -> void;
    template <class InputIt_t>
    auto Insert(Iterator it_pos, InputIt_t first, InputIt_t last) -> void;
    auto Erase(Iterator it_pos) -> Iterator;
    auto Erate(Iterator it_first, Iterator it_last) -> Iterator;
    auto Swap(Vector& other) -> void;
    auto Clear() -> void;
    template <class... Args_t>
    auto Emplace(ConstIterator it_pos, Args_t&&... args) -> Iterator;
    template <class... Args_t>
    auto EmplaceBack(Args_t&&... args) -> void;

public:
    auto operator==(const Vector& other) const -> bool;
    auto operator!=(const Vector& other) const -> bool;

public:
    auto IsValidOffset(Size_t offset) const -> bool;

private:
    Value_t* m_ptr{nullptr};
    Size_t   m_size{};
    Size_t   m_capacity{};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t, class Alloc_t>
inline Vector<T_t, Alloc_t>::Vector(Size_t size, const Value_t& init_val)
    : m_size(size)
    , m_capacity(size)
{
    m_ptr = Allocator_Trait<Allocator_t>::Allocate(size);
    Allocator_Trait<Allocator_t>::Construct(m_ptr, size, init_val);
}

template <class T_t, class Alloc_t>
inline Vector<T_t, Alloc_t>::Vector(
    const std::initializer_list<Value_t>& init_list)
    : m_size(init_list.size())
    , m_capacity(init_list.size())
{
    m_ptr    = Allocator_Trait<Allocator_t>::Allocate(m_size);
    auto ptr = m_ptr;
    for (Size_t i = 0; i < m_size; ++i)
    {
        ptr[i] = *(init_list.begin() + i);
    }
}

template <class T_t, class Alloc_t>
inline Vector<T_t, Alloc_t>::~Vector()
{
    Allocator_Trait<Allocator_t>::Deconstruct(m_ptr, m_size);
    Allocator_Trait<Allocator_t>::Deallocate(m_ptr);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::operator[](Size_t index) const
    -> const Value_t&
{
    return m_ptr[index];
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::operator[](Size_t index) -> Value_t&
{
    return const_cast<Value_t&>(
        static_cast<const Vector&>(*this).operator[](index));
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::At(Size_t index) const -> const Value_t&
{
    RDS_Assert(IsValidOffset(index) && "Index out of range");
    return operator[](index);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::At(Size_t index) -> Value_t&
{
    return const_cast<Value_t&>(static_cast<const Vector&>(*this).At(index));
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Front() -> Value_t&
{
    return const_cast<Value_t&>(static_cast<const Vector&>(*this).Front());
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Back() const -> const Value_t&
{
    return operator[](m_size - 1);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Back() -> Value_t&
{
    return const_cast<Value_t&>(static_cast<const Vector&>(*this).Back());
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Front() const -> const Value_t&
{
    return operator[](0);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Size() const -> Size_t
{
    return m_size;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Capacity() const -> Size_t
{
    return m_capacity;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Empty() const -> bool
{
    return m_size == 0;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Reserve(Size_t reserve_size) -> void
{
    if (reserve_size <= m_capacity)
        return;

    // 재할당 후 복사
    auto* new_ptr = Allocator_Trait<Allocator_t>::Allocate(reserve_size);
    for (Size_t i = 0; i < m_size; ++i)
        new_ptr[i] = m_ptr[i];

    // 기존 요소들의 소멸자 호출 및 메모리 해제
    Allocator_Trait<Allocator_t>::Deconstruct(m_ptr, m_size);
    Allocator_Trait<Allocator_t>::Deallocate(m_ptr);

    // 새 메모리로 포인터 변경
    m_ptr = new_ptr;

    // 용량 변경
    m_capacity = reserve_size;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::IsValidOffset(Size_t offset) const -> bool
{
    return offset < m_size;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::GetSentinelPointer() const -> const Value_t*
{
    return m_ptr;
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Begin() const -> ConstIterator
{
    return ConstIterator(this, 0);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::Begin() -> Iterator
{
    return Iterator(this, 0);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::End() const -> ConstIterator
{
    return ConstIterator(this, m_size);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::End() -> Iterator
{
    return Iterator(this, m_size);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::CBegin() const -> ConstIterator
{
    return ConstIterator(this, 0);
}

template <class T_t, class Alloc_t>
inline auto Vector<T_t, Alloc_t>::CEnd() const -> ConstIterator
{
    return ConstIterator(this, m_size);
}

RDS_END

#endif // RDS_VECTOR_HPP
