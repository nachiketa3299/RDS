/// @file Allocator_Trait.hpp

#ifndef RDS_ALLOCATOR_TRAIT_HPP
#define RDS_ALLOCATOR_TRAIT_HPP

#include <cstddef>

#include "Mallocator.hpp"
#include "Nallocator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Allocator 에 대한 제너릭 인터페이스 클래스
/// @tparam __Alloc_t 사용할 Allocator 클래스
template <class __Alloc_t>
class Allocator_Trait
{
public: // Type Aliases
    using Allocator_t  = __Alloc_t;
    using Value_t      = typename __Alloc_t::Value_t;
    using Size_t       = typename __Alloc_t::Size_t;
    using Difference_t = typename __Alloc_t::Difference_t;

public: // Memory Allocation / Deallocation
    /// @brief 인자로 전달된 크기만큼의 메모리를 할당한다.
    /// @param count 할당할 메모리의 크기
    /// @return 할당된 메모리의 시작 주소
    static auto Allocate(Size_t count) -> Value_t*
    {
        return Allocator_t().Allocate(count);
    }

    /// @brief 할당된 메모리를 해제한다.
    /// @param ptr 할당된 메모리의 시작 주소
    static auto Deallocate(const Value_t* ptr) -> void
    {
        Allocator_t().Deallocate(ptr);
    }

public: // Object Construction / Deconstruction
    /// @brief 포인터의 위치에 객체를 생성한다.
    /// @tparam ...CtorArgs_t 생성자에 전달할 인자(들)의 타입
    /// @param ptr 객체를 생성할 위치를 가리키는 포인터
    /// @param ...ctor_args 객체를 생성할 때 생성자에 전달할 인자(들)
    template <class... CtorArgs_t>
    static auto Construct(Value_t* ptr, Size_t count, CtorArgs_t&&... ctor_args)
        -> void
    {
        Allocator_t().Construct(ptr, count,
                                std::forward<CtorArgs_t>(ctor_args)...);
    }

    /// @brief 포인터의 위치에 있는 객체를 소멸시킨다.
    /// @param ptr 소멸시킬 객체의 시작 주소
    static auto Deconstruct(const Value_t* ptr, Size_t count) -> void
    {
        Allocator_t().Deconstruct(ptr, count);
    }
};

RDS_END

#endif // RDS_ALLOCATOR_TRAIT_HPP
