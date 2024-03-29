#ifndef RDS_NALLOCATOR_HPP
#define RDS_NALLOCATOR_HPP

#include "Assertion.h"
#include "RDS_CoreDefs.h"

namespace rds
{

/// @brief `new` 와 `delete`를 사용하는 메모리 할당자
/// @tparam __T_t 할당할 메모리의 자료형
template <class __T_t>
class Nallocator
{
public:
    using Value_t      = __T_t;
    using Size_t       = std::size_t;
    using Difference_t = std::ptrdiff_t;

public:
    Nallocator()                  = default;
    Nallocator(const Nallocator&) = default;
    ~Nallocator()                 = default;

    /// @{ @name Memory Allocation & Deallocation
public:
    /** @copydoc AllocatorTraits::Allocate
     *
     *  @exception Release 구성에서, 할당이 실패한 경우 `std::bad_alloc`
     */
    auto Allocate(Size_t count) -> Value_t*
    {
        // TODO 여기서 할당이 제대로 이루어지지 않는 경우 `std::bad_alloc`이
        // throw 되는지 확인해야 함
        auto* ptr =
            static_cast<Value_t*>(::operator new(sizeof(Value_t) * count));
        return ptr;
    }

    /** @copydoc AllocatorTraits::Deallocate */
    auto Deallocate(const Value_t* ptr) -> void
    {
        ::operator delete(const_cast<Value_t*>(ptr));
    }

    /// @} // Memory Allocation & Deallocation

    /// @{ @name Object Construction & Deconstruction

public:
    /** @copydoc AllocatorTraits::Construct */
    template <class... __CtorArgs_t>
    auto Construct(Value_t* ptr, Size_t count, __CtorArgs_t&&... ctor_args)
        -> void
    {
        // count 만큼 반복하면서 Placement New로 객체를 생성한다.
        for (Size_t i = 0; i < count; ++i)
        {
            ::new (ptr + i) Value_t(std::forward<__CtorArgs_t>(ctor_args)...);
        }
    }

    /** @copydoc AllocatorTraits::Deconstruct */
    auto Deconstruct(const Value_t* ptr, Size_t count) -> void
    {
        // count 만큼 반복하면서 소멸자를 호출한다.
        for (Size_t i = 0; i < count; ++i)
        {
            (ptr + i)->~Value_t();
        }
    }

    /// @} // Object Construction & Deconstruction
};
} // namespace rds

#endif // RDS_NALLOCATOR_HPP