#ifndef RDS_ALLOCATOR_HPP
#define RDS_ALLOCATOR_HPP

#include <cstddef>
#include <memory>

#include "RDS_CoreDefs.h"

RDS_BEGIN
std::allocator<int> a;

/// @brief
template <typename T>
class Allocator
{
    static_assert(!std::is_const_v<T>,
                  "C++ Standard forbids containers of const elements.");

public:
    using Val_t  = T;
    using Size_t = std::size_t;
    using Diff_t = std::ptrdiff_t;

public:
    Allocator() noexcept
    {}

    Allocator(const Allocator&) noexcept = default;

    template <class _Other>
    Allocator(const Allocator<_Other>&) noexcept
    {}

    Allocator& operator=(const Allocator&) = default;

    ~Allocator() = default;

public:
    void Deallocate(Val_t* const ptr, const Size_t count)
    {
        ::operator delete(ptr, count);
    }

    template <class Obj_t, class... T_t>
    void Construct(Obj_t* const ptr, T_t&&... _Args)
    {
        ::new (ptr) Obj_t(std::forward<T_t>(_Args)...);
    }

private:
};

RDS_END

#endif // RDS_ALLOCATOR_HPP