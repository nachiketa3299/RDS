#ifndef RDS_ALLOCATOR_H
#define RDS_ALLOCATOR_H

#include <cstddef>

/// @brief Custom allocator class
/// @tparam alloc_t Type to allocate
template <typename alloc_t>
class Allocator
{
    Allocator() noexcept
    {
    }

    ~Allocator() noexcept
    {
    }

    alloc_t* Allocate(std::size_t n)
    {
        return static_cast<alloc_t*>(::operator new(n * sizeof(T)));
    }

    void Deallocate(alloc_t* p, std::size_t n) noexcept
    {
        /// Deallocates memeory
        ::operator delete(p);
    }

    /// @brief Construct object with placement new
    template <typename... args>
    void Construct(alloc_t* p, Args&&)
    {
        /// @todo std::forward?
        new (p) alloc_t(std::forward<Args>(args)...);
    }

    void Destroy(alloc_t* p) noexcept
    {
        p->~alloc_t();
    }

    std::size_t MaxSize() const noexcept
    {
        return static_cast<std::size_t>(-1) / size_of(alloc_t);
    };
};
#endif // RDS_ALLOCATOR_H