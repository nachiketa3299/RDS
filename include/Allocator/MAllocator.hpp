#ifndef RDS_MALLOCATOR_HPP
#define RDS_MALLOCATOR_HPP

#include <cstddef>
#include <limits>
#include <new>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief malloc 을 사용하는 할당자 템플릿 클래스
/// @tparam T
/// @details
/// 상태 정보를 유지하지 않는(Stateless) 할당자이다. 이 말은 할당자 인스턴스 자체에서
/// 가변적인 상태 정보를 지니지 않겠다는 의미이다. 대신 할당과 해제 과정에서 @p malloc()
/// 과 @p free 로 명명된 전역 함수를 사용한다. 상태를 유지하지 않는 할당자는 같은 타입의
/// 할당자와 동일한지 비교해야 한다. 이는 @ref Mallocator 인스턴스와 무관하게 @ref
/// Mallocator 로 할당된 메모리가 반드시 @ref Mallocator 로 해제되어야 한다는 것을
/// 의미한다. 상태를 유지하지 않는 할당자는 복잡함이 최소화된 할당자이지만, 전역 상태에
/// 의존하기 때문에 제약이 있다.

template <typename T>
class Mallocator
{
public:
    using Val_t  = T;
    using Size_t = std::size_t;

public:
    Mallocator() noexcept {}; // 기본 ctor 이 필요하지 않다!

    template <class U>
    Mallocator(const Mallocator<U>&) const noexcept
    {
        return true;
    }

    template <class U>
    auto operator!=(const Mallocator<U>&) const noexcept
    {
        return false;
    }

public:
    auto Allocate(const Size_t size) const -> Val_t*
    {
        if (size == 0)
        {
            return nullptr;
        }

        const auto max_size = std::numeric_limits<Size_t>::max() / sizeof(T);

        if (size > max_size)
        {
            throw std::bad_array_new_length{};
        }

        void* const pv = malloc(size * sizeof(Val_t));

        if (pv == nullptr)
        {
            throw std::bad_alloc{};
        }

        return static_cast<Val_t*>(pv);
    }
    auto Deallocate(Val_t* const p, Size_t) const noexcept -> void
    {
        free(p);
    }
};

RDS_END

#endif // RDS_MALLOCATOR_HPP