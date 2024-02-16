/// @file Mallocator.hpp

#ifndef RDS_MALLOCATOR_HPP
#define RDS_MALLOCATOR_HPP

#include <cstddef>
#include <new>

#include "RDS_Concepts.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief `malloc` 과 `free`, placement `new` 를 사용하는 메모리 할당자 클래스
/// @tparam T_t 할당할 메모리의 타입
template <class T_t>
class Mallocator
{
public: // Type Aliases
    using Val_t  = T_t;
    using Size_t = std::size_t;
    using Diff_t = std::ptrdiff_t; // @todo 조사

public: // Default CDtors
    Mallocator()                  = default;
    Mallocator(const Mallocator&) = default;
    ~Mallocator()                 = default;

public: // Memory Allocation / Deallocation
    auto Allocate(Size_t count) -> Val_t*;
    auto Deallocate(Val_t* const ptr) -> void;

public: // Object Construction / Destruction
    template <class... CtorArgs_t>
    auto Construct(Val_t* const ptr, const Size_t count, CtorArgs_t&&... CtorArgs)
        -> void;

    auto Deconstruct(Val_t* const ptr, const Size_t count) -> void;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t>
inline auto Mallocator<T_t>::Allocate(Size_t count) -> Val_t*
{
    // 그냥 메모리를 할당하기만 한다
    return static_cast<Val_t*>(malloc(sizeof(Val_t) * count));
}

template <class T_t>
inline auto Mallocator<T_t>::Deallocate(Val_t* const ptr) -> void
{
    // 그냥 메모리를 해제하기만 한다
    free(ptr);
}

template <class T_t>
template <class... CtorArgs_t>
inline auto Mallocator<T_t>::Construct(Val_t* const ptr, const Size_t count,
                                       CtorArgs_t&&... CtorArgs) -> void
{
    // 객체를 생성해야 한다
    //::new (ptr) Val_t(std::forward<CtorArgs_t>(CtorArgs)...);
    for (Size_t i = 0; i < count; ++i)
    {
        // Placement new
        ::new (ptr + i) Val_t(std::forward<CtorArgs_t>(CtorArgs)...);
    }
}

template <class T_t>
inline auto Mallocator<T_t>::Deconstruct(Val_t* const ptr, const Size_t count) -> void
{
    // 객체를 소멸시켜야 한다
    for (Size_t i = 0; i < count; ++i)
    {
        (ptr + i)->~Val_t();
    }
}

RDS_END

#endif // RDS_MALLOCATOR_HPP
