#ifndef SHORT_ALLOC_H
#define SHORT_ALLOC_H

#include <cassert>
#include <cstddef>
#include <cstdint>

template <std::size_t N, std::size_t alignment = alignof(std::max_align_t)>
class arena
{
    alignas(alignment) char buf_[N];
    char* ptr_;

public:
    ~arena()
    {
        ptr_ = nullptr;
    }
    arena() noexcept
        : ptr_(buf_)
    {}
    arena(const arena&)            = delete;
    arena& operator=(const arena&) = delete;

    template <std::size_t RequiredAlignment>
    char*                        allocate(std::size_t n);
    void                         deallocate(char* p, std::size_t n) noexcept;

    static constexpr std::size_t size() noexcept
    {
        return N;
    }
    std::size_t used() const noexcept
    {
        return static_cast<std::size_t>(ptr_ - buf_);
    }
    void reset() noexcept
    {
        ptr_ = buf_;
    }

private:
    static std::size_t alignment_size(std::size_t n) noexcept
    {
        return (n + (alignment - 1)) & ~(alignment - 1);
    }

    bool pointer_in_buffer(char* p) noexcept
    {
        return std::uintptr_t(buf_) <= std::uintptr_t(p) &&
               std::uintptr_t(p) <= std::uintptr_t(buf_) + N;
    }
};

template <std::size_t N, std::size_t alignment>
template <std::size_t RequiredAlignment>
char* arena<N, alignment>::allocate(std::size_t n)
{
    static_assert(RequiredAlignment <= alignment, "alignment is too small for this arena");
    assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
    const auto aligned_n = alignment_size(n);
    if (static_cast<decltype(aligned_n)>(buf_ + N - ptr_) >= aligned_n)
    {
        char* r  = ptr_;
        ptr_    += aligned_n;
        return r;
    }

    static_assert(alignment <= alignof(std::max_align_t),
                  "you've chosen an "
                  "alignment that is larger than alignof(std::max_align_t), and "
                  "cannot be guaranteed by normal operator new");
    return static_cast<char*>(::operator new(n));
}

template <std::size_t N, std::size_t alignment>
void arena<N, alignment>::deallocate(char* p, std::size_t n) noexcept
{
    assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
    if (pointer_in_buffer(p))
    {
        n = alignment_size(n);
        if (p + n == ptr_)
            ptr_ = p;
    }
    else
        ::operator delete(p);
}

template <class T, std::size_t N, std::size_t Align = alignof(std::max_align_t)>
class short_alloc
{
public:
    using value_type                = T;
    static auto constexpr alignment = Align;
    static auto constexpr size      = N;
    using arena_type                = arena<size, alignment>;

private:
    arena_type& a_;

public:
    short_alloc(const short_alloc&)            = default;
    short_alloc& operator=(const short_alloc&) = delete;

    short_alloc(arena_type& a) noexcept
        : a_(a)
    {
        static_assert(size % alignment == 0,
                      "size N needs to be a multiple of alignment Align");
    }
    template <class U>
    short_alloc(const short_alloc<U, N, alignment>& a) noexcept
        : a_(a.a_)
    {}

    template <class _Up>
    struct rebind
    {
        using other = short_alloc<_Up, N, alignment>;
    };

    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(a_.template allocate<alignof(T)>(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) noexcept
    {
        a_.deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
    }

    template <class T1, std::size_t N1, std::size_t A1, class U, std::size_t M,
              std::size_t A2>
    friend bool operator==(const short_alloc<T1, N1, A1>& x,
                           const short_alloc<U, M, A2>&   y) noexcept;

    template <class U, std::size_t M, std::size_t A>
    friend class short_alloc;
};

template <class T, std::size_t N, std::size_t A1, class U, std::size_t M,
          std::size_t A2>
inline bool operator==(const short_alloc<T, N, A1>& x,
                       const short_alloc<U, M, A2>& y) noexcept
{
    return N == M && A1 == A2 && &x.a_ == &y.a_;
}

template <class T, std::size_t N, std::size_t A1, class U, std::size_t M,
          std::size_t A2>
inline bool operator!=(const short_alloc<T, N, A1>& x,
                       const short_alloc<U, M, A2>& y) noexcept
{
    return !(x == y);
}

#endif // SHORT_ALLOC_H