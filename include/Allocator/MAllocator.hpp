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
    auto Allocate(Size_t count) -> Val_t*
    {
        return static_cast<Val_t*>(malloc(sizeof(Val_t) * count));
    }

    /// @todo 이게 애초에 매개변수가 `const Val_t*` 이 아니어야 하는 것 아닌가?
    auto Deallocate(const Val_t* ptr) -> void
    {
        free(const_cast<void*>(static_cast<const void*>(ptr)));
    }

public: // Object Construction / Destruction
    template <class... CtorArgs_t>
    auto Construct(Val_t* ptr, Size_t count, CtorArgs_t&&... CtorArgs) -> void
    {
        for (Size_t i = 0; i < count; ++i)
        {
            // Placement new
            ::new (ptr + i) Val_t(std::forward<CtorArgs_t>(CtorArgs)...);
        }
    }

    auto Deconstruct(const Val_t* ptr, Size_t count) -> void
    {
        for (Size_t i = 0; i < count; ++i)
        {
            (ptr + i)->~Val_t();
        }
    }
};

RDS_END

#endif // RDS_MALLOCATOR_HPP
