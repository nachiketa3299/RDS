#ifndef RDS_VECTOR_HPP
#define RDS_VECTOR_HPP

#include "RDS_CoreDefs.h"

#include "AllocatorTraits.hpp"
#include "Iterator.hpp"

#include "Vector_Iterator.hpp"

namespace rds
{

/** @brief 동적 크기를 가지는 배열 템플릿 클래스
 *  @tparam __T_t 배열 원소에 대한 자료형.
 *  @tparam __Alloc_t 배열 원소에 대한 메모리 할당자 자료형 (기본값은 \ref
 *  Nallocator)
 */
template <class __T_t, template <class> class __Alloc_t = Nallocator>
class Vector
{
public:
    using Allocator_t = __Alloc_t<__T_t>;
    using Size_t      = std::size_t;

public:
    using Value_t      = __T_t;
    using Pointer_t    = __T_t*;
    using Reference_t  = __T_t&;
    using Difference_t = std::ptrdiff_t;

public:
    using ConstIterator_t = Vector_ConstIterator<Vector>;
    using Iterator_t      = Vector_Iterator<Vector>;

public:
    /** @brief 기본 생성자 */
    Vector()                                 = default;
    /** @brief 기본 복사 생성자 */
    Vector(const Vector&)                    = default;
    /** @brief 기본 이동 생성자 */
    Vector(Vector&&)                         = default;
    /** @brief 복사 대입 연산자 */
    auto operator=(const Vector&) -> Vector& = default;
    /** @brief 이동 대입 연산자 */
    auto operator=(Vector&&) -> Vector&      = default;

    /** @brief 기본 소멸자  */
    ~Vector()
    {
        AllocatorTraits<Allocator_t>::Deconstruct(m_ptr, m_size);
        AllocatorTraits<Allocator_t>::Deallocate(m_ptr);
    }

    /** @brief 벡터의 초기 크기와 초기 값을 지정하는 생성자
     * @param[in] size 생성할 벡터의 크기
     * @param[in] init_val 생성할 벡터의 초기값.
     */
    Vector(Size_t size, const Value_t& init_val = Value_t())
        : m_size(size)
        , m_capacity(size)
    {
        m_ptr = AllocatorTraits<Allocator_t>::Allocate(size);
        AllocatorTraits<Allocator_t>::Construct(m_ptr, size, init_val);
    }

    /** @brief 초기화 리스트를 받는 생성자
     *  @param[in] ilist 초기화 리스트
     */
    Vector(const std::initializer_list<Value_t>& ilist)
        : m_size(ilist.size())
        , m_capacity(ilist.size())
    {
        m_ptr    = AllocatorTraits<Allocator_t>::Allocate(m_size);
        auto ptr = m_ptr;
        for (Size_t i = 0; i < m_size; ++i)
            ptr[i] = *(ilist.begin() + i);
    }

    /** @brief 초기화 리스트를 받는 대입 연산자
     *  @param[in] ilist 초기화 리스트
     *  @return 연산 이후 이 벡터에 대한 참조
     */
    auto operator=(const std::initializer_list<Value_t>& ilist) -> Vector& {}

    // template <class __InputIterator_t>
    // auto Assign(__InputIterator_t it_first, __InputIterator_t it_last) ->
    // void
    // {
    //     AllocatorTraits<Allocator_t>::Deconstruct(m_ptr, m_capacity);
    //     AllocatorTraits<Allocator_t>::Deallocate(m_ptr);

    //     const auto count = DistanceBetween(it_first, it_last);

    //     m_ptr = AllocatorTraits<Allocator_t>::Allocate(count);

    //     for (Size_t i = 0; i < count; ++i)
    //         m_ptr[i] = *it_first++;
    // }

    auto Assign(Size_t count, const Value_t& val) -> void
    {
        AllocatorTraits<Allocator_t>::Deconstruct(m_ptr, m_capacity);
        AllocatorTraits<Allocator_t>::Deallocate(m_ptr);

        AllocatorTraits<Allocator_t>::Allocate(count);
        AllocatorTraits<Allocator_t>::Construct(m_ptr, count, val);

        m_capacity = count;
        m_size     = count;
    }

    auto Assign(const std::initializer_list<Value_t>& ilist) -> void
    {
        AllocatorTraits<Allocator_t>::Deconstruct(m_ptr, m_capacity);
        AllocatorTraits<Allocator_t>::Deallocate(m_ptr);
    }

    /// @{  @name Access

public:
    /** @brief 전달된 인덱스 번호의 벡터 원소에 대한 참조를 반환한다.
     *  @param[in] index 벡터 원소에 대한 인덱스
     *
     *  @note 인덱스의 범위 검사를 하지 않으므로, 주의한다.
     */
    auto operator[](Size_t index) const -> const Value_t&
    {
        return m_ptr[index];
    }

    /** @copydoc operator[](Size_t) const */
    auto operator[](Size_t index) -> Value_t&
    {
        return const_cast<Value_t&>(
            static_cast<const Vector&>(*this).operator[](index));
    }

    /** @brief 전달된 인덱스 번호의 벡터 원소에 대한 참조를 반환한다.
     *
     *  @warning Debug 구성에서 인덱스의 범위가 벡터의 크기를 벗어나느 경우
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto At(Size_t index) const -> const Value_t&
    {
        RDS_Assert(IsValidOffset(index) && "Index out of range");

        return operator[](index);
    }

    /** @copydoc At(Size_t) */
    auto At(Size_t index) -> Value_t&
    {
        return const_cast<Value_t&>(
            static_cast<const Vector&>(*this).At(index));
    }

    /** @brief 첫 번째 원소에 대한 참조를 반환한다.
     *  @return 첫 번째 원소에 대한 참조
     */
    auto Front() const -> const Value_t& { return operator[](0); }

    /** @copydoc Front() const
     *
     */
    auto Front() -> Value_t&
    {
        return const_cast<Value_t&>(static_cast<const Vector&>(*this).Front());
    }

    /** @brief 마지막 원소에 대한 참조를 반환한다.
     *  @brief 마지막 원소에 대한 참조
     */
    auto Back() const -> const Value_t& { return operator[](m_size - 1); }

    /** @copydoc Back() const
     *
     */
    auto Back() -> Value_t&
    {
        return const_cast<Value_t&>(static_cast<const Vector&>(*this).Back());
    }

    /** @brief 센티넬 원소에 대한 상수 포인터를 반환한다. */
    auto GetSentinelPointer() const -> const Value_t* { return m_ptr; }

    /// @} // Access

    /// @{ @name Iterators

public:
    /** @brief 첫 번째 원소를 가리키는 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 반복자
     */
    auto Begin() const -> ConstIterator_t { return ConstIterator_t(this, 0); }

    /** @copydoc Begin() const
     *
     */
    auto Begin() -> Iterator_t { return Iterator_t(this, 0); }

    /** @brief 끝을 가리키는 반복자를 반환한다.
     *  @return 끝을 가리키는 반복자
     *  @exception
     *  역참조 하면 안된다. Debug 구성에서는 비정상 종료하며, Release 구성에서는
     *  Undefined Behavior 이다.
     */
    auto End() const -> ConstIterator_t
    {
        return ConstIterator_t(this, m_size);
    }

    /** @copydoc End() const
     *
     */
    auto End() -> Iterator_t { return Iterator_t(this, m_size); }

    /** @brief 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 상수 반복자
     */
    auto CBegin() const -> ConstIterator_t { return ConstIterator_t(this, 0); }

    /** @brief 끝을 가리키는 상수 반복자를 반환한다.
     *  @return 끝을 가리키는 상수 반복자
     */
    auto CEnd() const -> ConstIterator_t
    {
        return ConstIterator_t(this, m_size);
    }

    /// @} // Iterators

    /// @{ @name Capacity

public:
    /** @brief 벡터의 크기를 반환한다.
     *  @return 벡터의 크기
     */
    auto Size() const -> Size_t { return m_size; }

    /** @brief 배열의 최대 크기를 반환한다.
     *  @return 배열의 최대 크기
     */
    auto MaxSize() const -> Size_t; // TODO

    /** @brief 배열이 비어있는지 확인한다.
     *  @return 배열이 비어있으면 `true`, 그렇지 않으면 `false`
     */
    auto Empty() const -> bool { return m_size == 0; }

    /** @brief 벡터의 용량을 반환한다.
     *  @return 벡터의 용량
     */
    auto Capacity() const -> Size_t { return m_capacity; }

    /** @brief 벡터의 용량을 지정한 크기로 변경한다.
     *  @param[in] reserve_size 변경할 크기
     *  @details 지정한 크기보다 용량이 작은 경우에만 작동하며, 그렇지 않으면
     *  아무 것도 수행하지 않는다. 지정한 크기보다 용량이 작은 경우에는 재할당이
     *  이루어진다.
     */
    auto Reserve(Size_t reserve_size) -> void
    {
        if (reserve_size <= m_capacity)
            return;

        // 재할당 후 복사
        auto* new_ptr = AllocatorTraits<Allocator_t>::Allocate(reserve_size);
        for (Size_t i = 0; i < m_size; ++i)
            new_ptr[i] = m_ptr[i];

        // 기존 요소들의 소멸자 호출 및 메모리 해제
        AllocatorTraits<Allocator_t>::Deconstruct(m_ptr, m_size);
        AllocatorTraits<Allocator_t>::Deallocate(m_ptr);

        // 새 메모리로 포인터 변경
        m_ptr = new_ptr;

        // 용량 변경
        m_capacity = reserve_size;
    }

    /** @brief 사용하고 있지 않은 벡터의 용량을 제거한다.
     *  @details 현재 크기보다 용량이 큰 경우에만 작동하며, 그렇지 않으면 아무
     * 것도 수행하지 않는다. 현재 크기보다 용량이 큰 경우에는 재할당이
     * 이루어진다.
     */
    auto Shrink() -> void; // TODO

    /// @} // Capacity

    /// @{ @name Modifiers

public:
    /** @brief 벡터의 크기를 0으로 만든다. 용량은 변하지 않는다. */
    auto Clear() -> void; // TODO

    // TODO 이게 링커 에러를 일으키는 주범이므로 Resolution에 대해 생각해 봐야
    // 한다.
    /** @brief 주어진 벡터의 위치 이전에 입력 반복자로 전달된 컨테이너의
        원소들을 삽입한다.
        @tparam __InputIterator_t 입력 반복자의 자료형
     *  @param[in] this_it_pos 삽입할 위치를 나타내는 반복자로, 이 반복자가
        가리키는 노드 이전에 새 노드가 삽입된다.
     *  @param[in] other_it_first 삽입할 원소들의 시작을 나타내는 반복자
     *  @param[in] other_it_last 삽입할 원소들의 끝을 나타내는 반복자
     *  @return 삽입된 원소 중 첫 번째 원소를 가리키는 반복자
    */
    // template <class __InputIterator_t>
    // auto InsertBefore(ConstIterator_t   this_it_pos,
    //                   __InputIterator_t other_it_first,
    //                   __InputIterator_t other_it_last) -> Iterator_t; // TODO

    // TODO Release 구성에서 예외를 던지도록 구현하는 것이 나을 수도 있다.
    /** @brief 반복자가 가리키는 위치 이전에 새 원소들을 삽입한다.
     *  @param[in] it_pos 삽입할 위치를 나타내는 반복자로, 이 반복자가 가리키는
        노드 이전에 새 노드가 삽입된다.
     *  @param[in] count 삽입할 원소의 갯수
     *  @param[in] val 삽입할 원소들이 가질 값
     *  @return 삽입된 원소 중 첫 번째 원소를 가리키는 반복자
     *
     *  @note 재할당이 이루어지면, 이 함수 호출 후 반복자가 모두 무효화된다.
     *  @warning Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로 호출하는
        경우 비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto InsertBefore(ConstIterator_t it_pos, Size_t count, const Value_t& val)
        -> Iterator_t; // TODO

    /** @overload
     *  @brief 반복자가 가리키는 위치 이전에 새 원소를 하나 삽입한다.
     */
    auto InsertBefore(ConstIterator_t it_pos, const Value_t& val) -> Iterator_t
    {
        return InsertBefore(it_pos, 1, val);
    }

    /** @overload
     *  @brief 반복자가 가리키는 위치 이전에 새 원소를 하나 삽입한다.
     */
    auto InsertBefore(ConstIterator_t it_pos, Value_t&& val)
        -> Iterator_t; // TODO

    /** @overload
     *  @brief 반복자가 가리키는 위치 이전에 초기화 리스트에 있는 원소들을
     *  삽입한다.
     *  @param[in] ilist 삽입할 원소들의 초기화 리스트
     */
    auto InsertBefore(ConstIterator_t                       it_pos,
                      const std::initializer_list<Value_t>& ilist)
        -> Iterator_t;

    /** @brief 인자로 전달된 값을 벡터의 맨 뒤에 삽입한다.
     *  @param[in] val 삽입할 원소의 값
     *
     *  @note `InsertBefore` 메서드를 내부에서 \ref CEnd 를 인자로 호출하므로,
     *  항상 안전하게 수행된다.
     *  @see \ref InsertBefore(ConstIterator_t,const Value_t&)
     */
    auto PushBack(const Value_t& val) -> void { InsertBefore(CEnd(), val); }

    /** @brief 반복자가 가리키는 위치 이전에, 전달된 생성자 인자들로 새 원소를
        생성해 추가한다.
     *  @tparam __CtorArgs_t 새로 생성될 원소의 생성자에 전달할 인자들의 자료형
     *  @param[in] it_pos 삽입할 위치 이후를 가리키는 반복자
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 원소를 가리키는 반복자
     *
     *  @note 호출 후 기존의 반복자들이 무효화되지 않으며, `it_pos`가 역참조
     가능할 필요는 없다.
     *  @warning Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로
        호출하는 경우 비정상 종료하며, Release 구성에서는 정의되지 않은
        행동이다.
     */
    template <class... __CtorArgs_t>
    auto EmplaceBefore(ConstIterator_t it_pos, __CtorArgs_t&&... args)
        -> Iterator_t; // TODO

    /** @brief 전달된 생성자 인자들로 새 원소를 생성해 벡터의 맨 뒤에
     * 추가한다.
     *  @tparam __CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     *  인자들의 자료형
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 원소를 가리키는 반복자. \ref End 의 이전과 같다.
     *
     *  @note 비어 있는 벡터에서 이 연산을 수행해도 안전하다.
     *  @see \ref EmplaceBefore
     */
    template <class... __CtorArgs_t>
    auto EmplaceBack(__CtorArgs_t&&... args) -> void; // TODO

    /** @brief 반복자로 주어진 범위의 원소들을 제거한다. 시작 범위의 원소부터
     *  마지막 범위 이전 원소까지 제거된다.
     *  @param[in] it_fisrt 범위의 시작 위치를 가리키는 반복자
     *  @param[in] it_last 범위의 끝 위치를 가리키는 반복자
     *  @return 제거된 범위의 다음 위치를 가리키는 반복자
     *  @details 제거되는 원소의 범위는 `[it_first, it_last)` 이다.
     *  반복자 쌍이 서로 같은 경우, 아무 동작도 하지 않고 `it_last`와 동일한
     *  반복자의 사본을 반환한다.
     *
     *  @warning 올바르지 않은 범위에 대한 반복자 쌍으로 호출되는 경우 정의되지
     * 않은 행동이다.
     *  @warning Debug 구성에서 반복자 쌍이 이 리스트와 호환되지 않는 경우
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     *  @warning Debug 구성에서 `it_first`가 역참조 불가능하거나 `it_last`가
     *  유효하지 않으면 비정상 종료하고, Release 구성에서는 정의되지 않은
     *  행동이다.
     */
    auto Erase(ConstIterator_t it_first, ConstIterator_t it_last)
        -> Iterator_t; // TODO

    /** @overload
     *  @brief 반복자가 가리키는 위치에 있는 원소를 제거한다.
     *  @param[in] it_pos 제거할 원소의 위치를 가리키는 반복자
     *  @return 제거된 원소의 다음 위치를 가리키는 반복자
     *
     *  @warning Debug 구성에서 전달된 반복자가 더이상 증가시킬 수 없는 반복자인
     *  경우 비정상 종료하며, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto Erase(ConstIterator_t it_pos) -> Iterator_t; // TODO

    /** @brief 벡터의 맨 뒤에서 원소를 제거한다.
     *
     *  @warning Debug 구성에서 비어있는 리스트에 대해 호출되는 경우 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     *  @see \ref Erase(ConstIterator_t)
     */
    auto PopBack() -> void; // TODO

    /** @brief 인자로 전달된 컨테이너와 이 컨테이너의 내용을 서로 바꾼다.
     *  @param[in] other 바꿀 대상이 되는 다른 컨테이너
     *  @details 한쪽이 비어있는 경우에도 정상 작동한다.
     */
    auto Swap(Vector& other) -> void; // TODO

    /** @brief 컨테이너가 `count` 개수의 원소를 가지도록 크기를 변경한다.
     *  @param[in] count 변경할 크기
     *  @details 현재 크기가 `count`와 같은 경우 아무 것도 수행하지 않는다.\n
     *  현재 크기가 `count`보다 큰 경우, 처음부터 `count` 개수의 원소만 남기고
     *  삭제된다. \n 현재 크기가 `count`보다 작은 경우, 추가된 원소들은
     *  기본 초기화된다.
     */
    auto Resize(Size_t count) -> void; // TODO

    /** @overload
     *  @details 추가된 원소들이 기본 초기화 되는 것이 아니라, `val`로
     * 초기화된다.
     *
     */
    auto Resize(Size_t count, const Value_t& val) -> void; // TODO

    /// @} // Modifiers

    /// @{ @name Comparators

public:
    /** @brief 두 컨테이너의 동등성을 비교한다.
     *  @param other 비교할 컨테이너
     *  @return 두 컨테이너가 같으면 `true`, 그렇지 않으면 `false`
     *  @details 동등 비교 순서는 다음과 같다.\n
     *  1. *두 컨테이너의 크기가 다르면*, 항상 같은 컨테이너가 아니다.
     *  2. *두 컨테이너의 크기가 같고 크기가 0이라면*,항상 같은 컨테이너이다.
     *  3. *두 컨테이너의 크기가 같고 크기가 0이 아니라면*, 두 컨테이너의 각
     *  원소를 순회하며 모든 원소가 같은 경우 같은 컨테이너이고, 그렇지 않으면
     *  다른 컨테이너이다.
     */
    auto operator==(const Vector& other) const -> bool;

    /** @brief 두 컨테이너의 비동등성을 비교한다.
     *  @see \ref operator==(const Vector&) const
     */
    auto operator!=(const Vector& other) const -> bool;

    /// @} // Comparators

    /// @{ @name Helper Methods

public:
    /** @brief 전달된 오프셋이 유효한지 확인한다.
     *  @return 오프셋이 유효하면 `true`, 그렇지 않으면 `false`
     *  @details 오프셋의 크기가 벡터의 크기보다 작을 때, 유효하다.
     */
    auto IsValidOffset(Size_t offset) const -> bool { return offset < m_size; }

    /// @} // Helper Methods

private:
    /** @brief 벡터의 내부 배열의 시작 주소 */
    Value_t* m_ptr{nullptr};
    /** @brief 벡터의 크기 */
    Size_t   m_size{};
    /** @brief 벡터의 용량 */
    Size_t   m_capacity{};
};

} // namespace rds

#endif // RDS_VECTOR_HPP
