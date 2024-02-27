/// @file Mallocator.hpp

#ifndef RDS_MALLOCATOR_HPP
#define RDS_MALLOCATOR_HPP

#include <cstddef>
#include <new>
#include <stdexcept>

#include "Assertion.h"
#include "RDS_Concepts.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @todo Difference_t 형식 재정의 (애초에 필요한지)
/// @brief `malloc` 과 `free`, placement `new` 를 사용하는 메모리 할당자 클래스
/// @tparam __T_t 할당할 메모리의 타입
template <class __T_t>
class Mallocator
{
public: // Type Aliases
    using Value_t      = __T_t;
    using Size_t       = std::size_t;
    using Difference_t = std::ptrdiff_t;

public: // Default CDtors
    Mallocator()                  = default;
    Mallocator(const Mallocator&) = default;
    ~Mallocator()                 = default;

public: // Memory Allocation / Deallocation
    auto Allocate(Size_t count) -> Value_t*
    {
        auto* ptr = static_cast<Value_t*>(malloc(sizeof(Value_t) * count));
        RDS_Assert(ptr != nullptr && "Failed to allocate memory.");

        if (ptr == nullptr)
        {
            throw std::bad_alloc();
        }

        return ptr;
    }

    /// @todo 이게 애초에 매개변수가 `const Value_t*` 이 아니어야 하는 것
    /// 아닌가?
    auto Deallocate(const Value_t* ptr) -> void
    {
        free(const_cast<void*>(static_cast<const void*>(ptr)));
    }

public: // Object Construction / Destruction
    template <class... CtorArgs_t>
    auto Construct(Value_t* ptr, Size_t count, CtorArgs_t&&... CtorArgs) -> void
    {
        for (Size_t i = 0; i < count; ++i)
        {
            // Placement new
            ::new (ptr + i) Value_t(std::forward<CtorArgs_t>(CtorArgs)...);
        }
    }

    auto Deconstruct(const Value_t* ptr, Size_t count) -> void
    {
        for (Size_t i = 0; i < count; ++i)
        {
            (ptr + i)->~Value_t();
        }
    }
};

RDS_END

#endif // RDS_MALLOCATOR_HPP