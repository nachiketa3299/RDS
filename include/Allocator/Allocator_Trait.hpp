/// @file Allocator_Trait.hpp

#ifndef RDS_ALLOCATOR_TRAIT_HPP
#define RDS_ALLOCATOR_TRAIT_HPP

#include <cstddef>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Allocator 에 대한 제너릭 인터페이스 클래스
/// @tparam Alloc_t 사용할 Allocator 클래스
template <class Alloc_t>
class Allocator_Trait
{
public: // Type Aliases
    using Val_t  = typename Alloc_t::Val_t;
    using Size_t = std::size_t;

public: // Memory Allocation / Deallocation
    /// @brief 인자로 전달된 크기만큼의 메모리를 할당한다.
    /// @param count 할당할 메모리의 크기
    /// @return 할당된 메모리의 시작 주소
    static auto Allocate(Size_t count) -> Val_t*;

    /// @brief 할당된 메모리를 해제한다.
    /// @param ptr 할당된 메모리의 시작 주소
    static auto Deallocate(Val_t* const ptr) -> void;

public: // Object Construction / Deconstruction
    /// @brief 포인터의 위치에 객체를 생성한다.
    /// @tparam ...CtorArgs_t 생성자에 전달할 인자(들)의 타입
    /// @param ptr 객체를 생성할 위치를 가리키는 포인터
    /// @param ...CtorArgs 객체를 생성할 때 생성자에 전달할 인자(들)
    template <class... CtorArgs_t>
    static auto Construct(Val_t* const ptr, const Size_t count,
                          CtorArgs_t&&... CtorArgs) -> void;

    /// @brief 포인터의 위치에 있는 객체를 소멸시킨다.
    /// @param ptr 소멸시킬 객체의 시작 주소
    static auto Deconstruct(Val_t* const ptr, const Size_t count) -> void;

public:
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class Alloc_t>
inline auto Allocator_Trait<Alloc_t>::Allocate(Size_t count) -> Val_t*
{
    return Alloc_t().Allocate(count);
}

template <class Alloc_t>
inline auto Allocator_Trait<Alloc_t>::Deallocate(Val_t* const ptr) -> void
{
    Alloc_t().Deallocate(ptr);
}

template <class Alloc_t>
template <class... CtorArgs_t>
inline auto Allocator_Trait<Alloc_t>::Construct(Val_t* const ptr, const Size_t count,
                                                CtorArgs_t&&... CtorArgs) -> void
{
    Alloc_t().Construct(ptr, count, std::forward<CtorArgs_t>(CtorArgs)...);
}

template <class Alloc_t>
inline auto Allocator_Trait<Alloc_t>::Deconstruct(Val_t* const ptr, const Size_t count)
    -> void
{
    Alloc_t().Deconstruct(ptr, count);
}

RDS_END

#endif // RDS_ALLOCATOR_TRAIT_HPP
