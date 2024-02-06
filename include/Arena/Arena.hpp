#ifndef RDS_ARENA_HPP
#define RDS_ARENA_HPP

#include <cstddef>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief
/// @tparam N
/// @details
/// 동적인 저장 기간이 필요한 작은, 또는 한 두개의 객체에 대해, 충분히 작기 때문에
/// **스택 메모리**를 사용할 수 있게 하는 간단한 아레나 템플릿이다. \n
/// 아레나(Arena)는 컴파일 시에 크기가 정해진 @p char 형 버퍼를 가지고 있다. 이는
/// 스택이나 정적 저장소 또는 로컬 스레드 저장소에 변수로 아레나 객체를 생성하는 것을
/// 가능하게 한다. 이 버전의 메모리 배치는 어떠한 타입에도 적합한 @p malloc 을 사용한
/// 것과 동일하게 구성된다. 일부 배치(Align) 조건에 대해 작은 타입으로 구성된 아레나의
/// 경우 조금은 낭비적인 요소가 있을 수 있지만, 여기서는 무시한다. @p char 배열인
/// 버퍼는, 스택에 할당될 수도 있다. 배열에 @p alignas 지정자를 적용하지 않는다면 @p
/// char 이외의 타입으로 배치될 일은 없다. \n
/// 헬퍼(Helper) @ref align_up 함수는 비트 연산에 사용하지 않으면 복잡하게 보일 수 있다.
/// 하지만 여기서는 배치 조건을 반올림하는 기능으로만 사용한다.
template <std::size_t Size_, std::size_t alignment = alignof(std::max_align_t)>
class Arena
{
public:
    using buffer_t = char;
    using Size_t   = std::size_t;

private:
    alignas(alignment) buffer_t m_buffer[Size_];
    buffer_t* m_ptr{};

public:
    Arena() noexcept
        : m_ptr(m_buffer)
    {}
    Arena(const Arena&)            = delete;
    Arena& operator=(const Arena&) = delete;

    auto   Reset() noexcept
    {
        m_ptr = m_buffer;
    }

    static constexpr auto Size() noexcept
    {
        return Size_;
    }

    auto Used() const noexcept
    {
        return static_cast<Size_t>(m_ptr - m_buffer);
    }

    template <Size_t RequiredAlignment>
    auto Allocate(Size_t size_to_alloc) -> buffer_t*
    {
        static_assert(RequiredAlignment <= alignment,
                      "alignment is too small for this arena");

        RDS_Assert(pointer_in_buffer(m_ptr) && "short_alloc has outlived arena");

        const auto aligned_size = alignment_size(size_to_alloc);
        if (static_cast<Size_t>(m_buffer + Size_ - m_ptr) >= aligned_size)
        {
            buffer_t* r  = m_ptr;
            m_ptr       += aligned_size;
            return r;
        }

        static_assert(
            alignment <= alignof(std::max_align_t),
            "you've chosen an alginment that is larger than alignof(std::max_align_t), "
            "and can't be guaranteed by normal operator new");

        return static_cast<buffer_t*>(::operator new(size_to_alloc));
    }

    auto Deallocate(buffer_t* p, Size_t size) noexcept -> void
    {
        RDS_Assert(pointer_in_buffer(m_ptr) && "short_alloc has outlived arena");
        if (pointer_in_buffer(p))
        {
            size = alignment_size(size);
            if (p + size = m_ptr)
                m_ptr = p;
        }
        else
            ::operator delete(p);
    }

private:
    /// @brief 인자로 전달한 @p size 와 가장 가까운 @p alignment 의 배수를 반환한다.
    /// (비트 연산 사용)
    /// @details 예를 들어 @p size = 23 이고 @p alignment = 8 이라면, 반환값은 24이다.
    static auto alignment_size(Size_t size) noexcept -> Size_t
    {
        return (size + (alignment - 1)) & ~(alignment - 1);
    }

    /// @brief 인자로 전달된 @p ptr 을
    auto pointer_in_buffer(const buffer_t* ptr) const noexcept -> bool
    {

        //   Size_ = 5;
        //   m_buffer + 0                        m_buffer + (Size_ - 1)
        //   ↓                                   ↓
        //   0        1        2        3        4
        //  [ ]      [ ]      [ ]      [ ]      [ ]

        // 왜 (ptr < m_buffer + Size_) 가 아니라 (ptr <= m_buffer + Size_) 인 것이지?

        return (m_buffer + 0 <= ptr) && (ptr <= m_buffer + Size_);
    }
};

RDS_END

#endif // RDS_ARENA_HPP