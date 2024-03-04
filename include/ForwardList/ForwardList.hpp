#ifndef RDS_FORWARDLIST_HPP
#define RDS_FORWARDLIST_HPP

#include <initializer_list>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "AllocatorTraits.hpp"
#include "Node_S.hpp"

#include "ForwardList_Iterator.hpp"

/*
================================================================================
* Forward List
--------------------------------------------------------------------------------
* Example of Size 0 ForwardList
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     Begin/End
    ┌→ [node_s]n╶┐
    └────────────┘
--------------------------------------------------------------------------------
* Example of Size n ForwardList (n!=0)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
          End        Begin
    ┌→ [node_s]n→ [node_0]n→ [node_1]n→ [node_2]n→ ... [node_n-1]n╶┐
    └──────────────────────────────────────────────────────────────┘
                     Front
--------------------------------------------------------------------------------
*/

namespace rds
{

/** @brief 동적 단일 연결 리스트에 대한 템플릿 클래스
 *  @tparam __T_t 전방 리스트 내 원소에 대한 자료형. 리스트 노드에 의해 래핑되어
 *  있다.
 *  @tparam __Alloc_t 전방 리스트의 원소에 대한 메모리 할당자 자료형 (기본값은
 *  \ref Nallocator)
 *  @details
 *  \ref Node_S 노드를 내부에서 사용하며, 전방 리스트의 맨 앞에는 센티넬 노드가
 *  항상 존재한다.
 */
template <class __T_t, template <class> class __Alloc_t = Nallocator>
class ForwardList
{
public:
    /** @brief 이 전방 리스트의 원소의 생성과 소멸을 관리하는 할당자 자료형이다.
     *
     *  @note 할당자는 `__T_t`를 생성하는 것이 아니라, `Node_S<__T_t>`
     *  를 생성한다.
     */
    using Allocator_t = __Alloc_t<Node_S<__T_t>>;
    using Size_t      = std::size_t;
    using Node_S_t    = Node_S<Value_t>;

public:
    using Value_t      = __T_t;
    using Pointer_t    = __T_t*;
    using Reference_t  = __T_t&;
    using Difference_t = std::ptrdiff_t;

public:
    using ConstIterator_t = ForwardList_ConstIterator<ForwardList>;
    using Iterator_t      = ForwardList_Iterator<ForwardList>;

public:
    /** @brief 기본 생성자
     *  @details
     *  아무 원소도 가지지 않는 전방 리스트를 생성한다.\n 센티넬 노드의 다음
     *  노드와 이전 노드를 자기 자신으로 초기화한다.
     */
    ForwardList() { __InitializeSentinelNode(); }

    /** @brief 복사 생성자
     *  @param[in] other 복사할 다른 리스트
     */
    ForwardList(const ForwardList& other); // TODO

    /** @brief 이동 생성자
     *  @param[in] temp_other 이동시킬 다른 전방 리스트
     *  @details 전방 리스트의 소유권을 이전시키는 작업을 한다. 다른 전방
     *  리스트의 센티넬 노드 이후에 있는 노드들을 이 전방 리스트로 이동시킨다.
     */
    ForwardList(ForwardList&& temp_other); // TODO

    /** @brief 복사 대입 연산자
     *  @param[in] other 복사하여 이 전방 리스트에 대입할 다른 전방 리스트
     *  @return 연산 이후 이 전방 리스트에 대한 참조
     */
    auto operator=(const ForwardList& other) -> ForwardList&; // TODO

    /** @brief 이동 대입 연산자
     *  @param[in] temp_other 이동하여 이 전방 리스트에 대입할 다른 전방 리스트
     *  @return 연산 이후 이 전방 리스트에 대한 참조
     */
    auto operator=(ForwardList&& other) -> ForwardList&; // TODO

    /** @brief 소멸자. 전방 리스트가 보유한 노드들을 정리한다.
     */
    ~ForwardList() noexcept
    {
        auto* ptr = m_sentinel_node.next;
        while (ptr != std::address_of(m_sentinel_node))
        {
            auto* to_delete = ptr;
            ptr             = ptr->next;

            DeleteNode(to_delete);
        }
    }

    /** @brief 전방 리스트의 초기 크기와 초기 값을 지정하는 생성자
     *  @param[in] size 생성할 전방 리스트의 크기
     *  @param[in] init_val 생성할 전방 리스트의 초기값.
     *  @details `size` 가 0이면, `init_val`에 상관없이 아무 동작도 하지 않는다.
     */
    ForwardList(Size_t size, const Value_t& init_val)
        : ForwardList()
    {
        for (Size_t i = 0; i < size; ++i)
            InsertAfter(CBeforeBegin(), init_val);
    }

    /** @brief 전방 리스트의 초기 크기를 지정하는 생성자.
     *  @details 전달된 크기만큼의 전방 리스트를 생성하며, 각 원소는 기본
     *  초기화된다.
     */
    ForwardList(Size_t size)
        : ForwardList(size, Value_t())
    {}

    /** @brief 초기화 리스트를 받는 생성자
     *  @param[in] ilist 초기화 리스트
     */
    ForwardList(const std::initializer_list<Value_t>& ilist); // TODO

    /** @brief 초기화 리스트를 받는 대입 연산자
     *  @param[in] ilist 초기화 리스트
     *  @return 연산 이후의 이 전방 리스트에 대한 참조
     */
    auto operator=(std::initializer_list<Value_t>& init_list)
        -> ForwardList&; // TODO

    template <class __InputIterator_t>
    auto Assign(__InputIterator_t it_first, __InputIterator_t it_last)
        -> void;                                                      // TODO
    auto Assign(Size_t count, const Value_t& val) -> void;            // TODO
    auto Assign(const std::initializer_list<Value_t>& ilist) -> void; // TODO

    /// @{  @name Node Management
private:
    /** @brief 센티넬 노드의 링크를 자기 자신을 가리키도록 초기화한다. */
    inline auto __InitializeSentinelNode() -> void
    {
        m_sentinel_node.next = &m_sentinel_node;
    }

public:
    // TODO  Node_S의 복사 생성자를 호출하는지 확인해야함
    /** @brief 새로운 노드를 생성하고 그 노드의 주소를 반환한다.
     *  @param[in] val 새로 생성될 노드에 들어갈 값
     *  @return 새로 생성된 노드의 주소
     */
    static auto CreateNode(const Value_t& value) const -> Node_S_t*
    {
        Node_S_t* ptr = AllocatorTraits<Allocator_t>::Allocate(1);
        AllocatorTraits<Allocator_t>::Construct(ptr, 1, value);

        return ptr;
    }

    /** @copybrief CreateNode(const Value_t&)
     *  @tparam __CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     * 인자들의 자료형 목록
     *  @param[in] ctor_args 노드가 보유한 값의 자료형의 생성자에 전달할 인자들
     *  @return 새로 생성된 노드의 주소
     *
     *  @note \ref Node_S 의 연관된 생성자를 호출한다.
     */
    template <class..__CtorArgs_t>
    static auto CreateNode(__CtorArgs_t&&... ctor_args) -> Node_S_t*
    {
        Node_S_t* ptr = AllocatorTraits<Allocator_t>::Allocate(1);
        AllocatorTraits<Allocator_t>::Construct(
            ptr, 1, std::forward<__CtorArgs_t>(ctor_args)...);
    }

    /** @brief 전달된 포인터에 있는 노드를 삭제한다.
     *  @param[in] node_ptr 삭제할 노드의 주소
     */
    static auto DeleteNode(const Node_S_t* node) const -> void
    {
        AllocatorTraits<Allocator_t>::Deconstruct(node, 1);
        AllocatorTraits<Allocator_t>::Deallocate(node);
    }

    /// @} // Node Management

    /// @{  @name Access
public:
    /** @brief 첫번째 원소에 대한 참조를 반환한다.
     *  @return 첫번째 원소에 대한 참조
     *
     *  @warning Debug 구성에서 리스트가 비어있는 경우 비정상 종료하고, Release
     *  구성에서는 정의되지 않은 행동이다.
     */
    auto Front() const -> const Value_t&
    {
        RDS_Assert(static_cast<int>(m_size) > 0 &&
                   "Cannot access front of empty list.");
        return m_sentinel_node.next->val;
    }

    /** @copydoc Front() const
     *
     */
    auto Front() -> Value_t&
    {
        return const_cast<__T_t&>(
            static_cast<const ForwardList&>(*this).Front());
    }

    /** @brief 센티넬 노드에 대한 상수 포인터를 반환한다.
     *  @return 센티넬 노드에 대한 상수 포인터
     *
     *  @warning 센티넬 노드의 값은 아무런 의미가 없으며, 이에 접근하거나
     *  변경하려는 시도는 모두 정의되지 않은 행동이다.
     */
    auto GetSentinePointer() const -> const Node_S_t*
    {
        return &m_sentinel_node;
    }

    /// @} // Access

    /// @{  @name Iterators

public: // Iterators
    /** @brief 첫 번째 원소 이전 원소를 가리키는 반복자를 반환한다.
     *  @return 첫 번째 이전 원소를 가리키는 반복자
     *
     *  @warning 이 반복자를 역참조하면 안된다. 역참조시 Debug 구성에서는 비정상
     *  종료하며, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto BeforeBegin() const -> ConstIterator_t
    {
        return ConstIterator_t(this, &m_sentinel_node);
    }

    /** @copydoc BeforeBegin() const
     *
     */
    auto BeforeBegin() -> Iterator_t
    {
        return Iterator_t(this, &m_sentinel_node);
    }

    /** @brief 첫 번째 원소를 가리키는 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 반복자
     *
     *  @warning 비어 있는 전방 리스트에 대해서도 호출할 수 있지만, 이렇게
     *  얻어진 반복자는 역참조하면 안된다. 역참조시 Debug 구성에서는 비정상
     *  종료하며, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto Begin() const -> ConstIterator_t
    {
        return ConstIterator_t(this, m_sentinel_node.next);
    }

    /** @copydoc Begin() const
     *
     */
    auto Begin() -> Iterator_t
    {
        return Iterator_t(this, m_sentinel_node.next);
    }

    /** @brief 끝을 가리키는 반복자를 반환한다.
     *  @return 끝을 가리키는 반복자
     *
     *  @warning 역참조시 Debug 구성에서는 비정상 종료하며, Release 구성에서는
     *  정의되지 않은 행동이다.
     */
    auto End() const -> ConstIterator_t
    {
        return ConstIterator_t(this, &m_sentinel_node);
    }

    /** @copydoc End() const
     *
     */
    auto End() -> Iterator_t { return Iterator_t(this, &m_sentinel_node); }

    /** @brief 첫 번째 원소 이전에 있는 원소를 가리키는 상수 반복자를 반환한다.
     *  @return 첫 번째 이전 원소를 가리키는 상수 반복자
     */
    auto CBeforeBegin() const -> ConstIterator_t { return BeforeBegin(); }

    /** @brief 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 상수 반복자
     */
    auto CBegin() const -> ConstIterator_t { return Begin(); }

    /** @brief 끝을 가리키는 상수 반복자를 반환한다.
     *  @return 끝을 가리키는 상수 반복자
     */
    auto CEnd() const -> ConstIterator_t { return End(); }

    /// @}

    /// @{ @name Capacity
public:
    /** @brief 전방 리스트의 크기를 반환한다.
     *  @return 전방 리스트의 크기
     *  @details O(1) 이다.
     */
    auto Size() const -> Size_t { return m_size; }

    auto MaxSize() const -> Size_t; // TODO

    /** @brief 전방 리스트가 비어있는지 확인한다.
     *  @return 전방 리스트가 비어있으면 `true`, 그렇지 않으면 `false`이다.
     */
    auto Empty() const -> bool { return m_size == 0; }

    /// @} // Capacity

    /// @{ @name Modifiers
public:
    /** @brief 전방 리스트의 모든 원소(노드)를 삭제하고, 센티넬 노드를
     * 초기화한다.
     *  @details 전방 리스트가 현재 보유하고 있는 모든 노드들을 삭제한다.
     *  그리고, 센티넬 노드를 초기화한다. 만일 전방 리스트가 비어있다면, 아무런
     *  동작도 하지 않는다.
     */
    auto Clear() -> void
    {
        // 첫 번째 노드의 주소를 가져온다.
        auto* ptr = m_sentinel_node.next;

        // 센티넬 노드 다음부터 시작하여 센티넬 노드까지 순회하며 메모리 해제
        // 이 전방 리스트가 비어 있다면 첫 번째 노드의 주소가 센티넬 노드의
        // 주소와 동일하므로 while 문으로 진입하지 않는다.
        while (ptr != &m_sentinel_node)
        {
            auto* to_delete = ptr;
            ptr             = ptr->next;

            DeleteNode(to_delete);
        }

        m_size = 0;

        // 센티넬 노드 초기화
        __InitializeSentinelNode();
    }

    // TODO 이게 링커 에러를 일으키는 주범이므로 Resolution에 대해 생각해 봐야
    // 한다.
    /** @brief 주어진 전방 리스트의 위치 이후에 입력 반복자로 전달된 컨테이너의
        원소들을 삽입한다.
        @tparam __InputIterator_t 입력 반복자의 자료형
     *  @param[in] this_it_pos 삽입할 위치를 나타내는 반복자로, 이 반복자가
        가리키는 노드 이후에 새 노드가 삽입된다.
     *  @param[in] other_it_first 삽입할 원소들의 시작을 나타내는 반복자
     *  @param[in] other_it_last 삽입할 원소들의 끝을 나타내는 반복자
     *  @return 삽입된 원소 중 첫 번째 원소를 가리키는 반복자
    */
    // template <class __InputIterator_t>
    // auto InsertAfter(ConstIterator_t   this_it_pos,
    //                  __InputIterator_t other_it_first,
    //                  __InputIterator_t other_it_last); // TODO

    /** @brief 반복자가 가리키는 위치 이후에 새 원소들을 삽입한다.
     *  @param[in] it_pos 삽입할 위치를 나타내는 반복자로, 이 반복자가 가리키는
     *  노드 이후에 새 노드가 삽입된다.
     *  @param count 삽입할 원소의 갯수
     *  @param[in] val 삽입할 원소들이 가지는 값
     *  @return 삽입된 노드들 중 첫 번째 노드를 가리키는 반복자
     *
     *  @note 호출 후 기존의 반복자들이 무효화되지 않으며, `it_pos`가 역참조
     *  가능할 필요는 없다.
     *  @warning Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로 호출하는
     *  경우 비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto InsertAfter(ConstIterator_t it_pos, Size_t count, const Value_t& val)
        -> Iterator_t
    {
        RDS_Assert(it_pos.IsValid() && "Invalid iterator.");
        RDS_Assert(it_pos.IsCompatible(*this) &&
                   "ForwardList is not compatible.");

        if (count < 1)
            return Iterator_t(this, it_pos.GetDataPointer());

        /*
        ------------------------------------------------------------------------
         * Before InsertAfter(it_pos, count, val)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
               it_pos
                 ↓
         [ ]n-> [ ]n-> [ ]n-> [ ]n->
                 ↑      ↑
               prev    next
        ------------------------------------------------------------------------
         * After InsertAfter(it_pos, count, val)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                it_pos  head   tail
                 ↓       ↓      ↓
         [ ]n-> [ ]n->> [N]n-> [N]n->> [ ]n->
                 ↑                      ↑
               prev                   next
        ------------------------------------------------------------------------
          2 Links to be updated:
        */

        auto* prev_node_ptr = const_cast<Node_S_t*>(it_pos.GetDataPointer());
        auto* next_node_ptr = prev_node_ptr->next;

        /*
         새로 삽입될 노드들을 위한 포인터
         여러 개 삽입되기 때문에 가장 선두(head)에 있는 노드의 주소와
         가장 마지막(tail)에 있는 노드의 주소를 따로 저장한다.
        */
        Node_S_t* new_node_ptr_head = CreateNode(val);
        auto*     new_node_ptr_tail = new_node_ptr_head;

        // 새로운 노드들을 생성하고 연결한다.
        for (Size_t i = 1; i < count; ++i)
        {
            Node_S_t* new_node_ptr = CreateNode(val);

            new_node_ptr_tail->next = new_node_ptr;
            new_node_ptr_tail       = new_node_ptr;
        }

        // 연결된 새 노드들을 이제 리스트의 올바른 위치에 연결한다.
        prev_node_ptr->next     = new_node_ptr_head;
        new_node_ptr_tail->next = next_node_ptr;

        m_size += count;

        return Iterator_t(this, new_node_ptr_head);
    }

    /** @overload
     *  @brief 반복자가 가리키는 위치 이후에 새 원소를 삽입한다.
     */
    auto InsertAfter(ConstIterator_t it_pos, const Value_t& value) -> void
    {
        return InsertAfter(it_pos, 1, value);
    }

    /** @overload
     *  @brief 반복자가 가리키는 위치 이전에 새 원소를 하나 삽입한다.
     */
    auto InsertBefore(ConstIterator_t it_pos, Valut_t&& val)
        -> Iterator_t; // TODO

    /** @overload
     *  @brief 반복자가 가리키는 위치 이후에 초기화 리스트에 있는 원소들을
     * 삽입한다.
     */
    auto InsertAfter(ConstIterator_t                       it_pos,
                     const std::initializer_list<Value_t>& ilist)
        -> void; // TODO

    /** @brief 인자로 전달된 값을 전방 리스트의 맨 앞에 삽입한다.
     *  @param[in] val 삽입할 원소의 값
     *
     *  @see \ref InsertAfter(ConstIterator_t,const Value_t&)
     */
    auto PushFront(const Value_t& val) -> void
    {
        InsertAfter(CBeforeBegin(), val);
    }

    /** @brief 반복자가 가리키는 위치 이전에, 전달된 생성자 인자들로 새 원소를
     *  생성해 추가한다.
     *  @tparam __CtorArgs_t 새로 생성될 원소의 생성자에 전달할 인자들의 자료형
     *  @param[in] it_pos 삽입할 위치 이전을 가리키는 반복자
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 원소를 가리키는 반복자
     *
     *  @note 호출 후 기존의 반복자들이 무효화되지 않으며, `it_pos`가 역참조
     가능할 필요는 없다.
     *  @warning Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로
        호출하는 경우 비정상 종료하며, Release 구성에서는 정의되지 않은
        행동이다.
     */
    template <class... CtorArgs_t>
    auto EmplaceAfter(ConstIterator_t it_pos, CtorArgs_t&&... ctor_args)
        -> Iterator_t
    {
        RDS_Assert(it_pos.IsValid() && "Invalid iterator.");
        RDS_Assert(it_pos.IsCompatible(*this) &&
                   "ForwardList is not compatible.");

        Node_S_t* new_node_ptr =
            CreateNode(std::forward<CtorArgs_t>(ctor_args)...);

        auto* ins_node_ptr = const_cast<Node_S_t*>(it_pos.GetDataPointer());

        auto* next_node_ptr = ins_node_ptr->next;

        ins_node_ptr->next = new_node_ptr;
        new_node_ptr->next = next_node_ptr;

        auto it_last = it_pos;

        ++m_size;

        return Iterator_t(this, new_node_ptr);
    }

    /** @brief 전달된 생성자 인자들로 새 원소를 생성해 전방 리스트의 맨 앞에
     *  추가한다.
     *  @tparam __CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     *  인자들의 자료형
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 원소를 가리키는 반복자. \ref Begin 과 같다.
     *
     *  @note 비어 있는 리스트에서 이 연산을 수행해도 안전하다.
     *  @see \ref EmplaceAfter
     */
    template <class... CtorArgs_t>
    auto EmplaceFront(CtorArgs_t&&... ctor_args) -> Iterator_t
    {
        return EmplaceAfter(CBeforeBegin(),
                            std::forward<CtorArgs_t>(ctor_args)...);
    }

    // TODO 삭제 순회 중에 센티넬 노드를 만날 가능성을 완전히 배제할 수 없다는
    // 점
    /** @brief 반복자로 주어진 범위의 원소들을 제거한다. 시작 범위의 다음
     *  원소부터 마지막 범위 이전 원소까지 제거된다.
     *
     *  @param[in] it_fisrt 범위의 시작 위치를 가리키는 반복자
     *  @param[in] it_last 범위의 끝 위치를 가리키는 반복자
     *  @return 제거된 범위의 다음 원소를 가리키는 반복자
     *  @details 제거되는 원소의 범위는 `(it_first, it_last)` 이다.
     *
     *  @warning 올바르지 않은 범위에 대한 반복자 쌍으로 호출되는 경우 정의되지
     *  않은 행동이다. 기본적으로 `it_first`와 `it_last` 가 같은 반복자이면,
     *  Debug 구성에서는 비정상 종료하고 Release 구성에서는 정의되지 않은
     *  행동이다.
     *  @warning Debug 구성에서 반복자 쌍이 이 전방 리스트와 호환되지 않는 경우
     *  비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     *  @warning Debug 구성에서 `it_first`와 `it_last`가 유효하지 않으면 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto EraseAfter(ConstIterator_t it_first, ConstIterator_t it_last)
        -> Iterator_t
    {
        RDS_Assert(it_first.IsValid() && "Start of range is not valid.");
        RDS_Assert(it_last.IsValid() && "End of range is not valid.");

        RDS_Assert(it_first.IsCompatible(*this) &&
                   "ForwardList is not compatible with given iterator.");
        RDS_Assert(it_last.IsCompatible(*this) &&
                   "ForwardList is not compatible with given iterator.");

        RDS_Assert(it_first != it_last && "Invalid range.");

        /*
        ------------------------------------------------------------------------
         * Before Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            range_start(it_first->next)
                    ↓
         ... [B]n→ [X]n→ [X]n→ [X]n→ [A]n→ ...
              ↑                       ↑
         range_before(it_first)  range_after(it_last)
        ------------------------------------------------------------------------
         * After Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

         ... [B]->>                  [A]n→ ...
              ↑                       ↑
         range_before(it_first)  range_after(it_last)
        ------------------------------------------------------------------------
            1 link to be updated:
        */

        auto* range_before_ptr =
            const_cast<Node_S_t*>(it_first.GetDataPointer());
        auto* range_start_ptr = range_before->next;

        auto* range_after_ptr = const_cast<Node_S_t*>(it_last.GetDataPointer());

        // 삭제 범위 전후 노드에 대한 재연결
        range_before_ptr->next = range_after_ptr;

        // 삭제 범위를 순회하며 노드 삭제
        const auto* p = range_start_ptr;
        while (p != range_after_ptr)
        {
            const auto* to_delete = p;
            p                     = p->next;

            DeleteNode(to_delete);
            --m_size;
        }

        return Iterator_t(this, range_after_ptr);
    }

    /** @overload
     *  @brief 반복자가 가리키는 위치 이후에 있는 원소를 제거한다.
     *  @param[in] it_pos 제거할 원소의 이전 위치를 가리키는 반복자
     *  @return 제거된 원소의 다음 위치를 가리키는 반복자
     *
     *  @warning Debug 구성에서 전달된 반복자가 두 번 증가시킬 수 없는 반복자인
     *  경우 비정상 종료하며, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto EraseAfter(ConstIterator_t it_pos) -> Iterator_t
    {
        auto it_last = it_pos;
        it_last.operator++();
        it_last.operator++();
        return Erase(it_pos, it_last);
    }

    /** @brief 전방 리스트의 맨 앞에서 원소를 제거한다.
     *
     *  @see \ref EraseAfter(ConstIterator_t)
     */
    auto PopFront() -> void { EraseAfter(CBeforeBegin()); }

    /** @brief 인자로 전달된 전방 리스트와 이 전방 리스트의 내용을 서로 바꾼다.
     *  @param[in] other 바꿀 대상이 되는 다른 전방 리스트
     *  @details 한쪽이 비어 있는 경우에도 정상 작동한다.
     */
    auto Swap(ForwardList& other) -> void; // TODO

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

    /// @{ @name Operations
public:
    /** @brief 조건에 맞는 원소를 제거한다.
     *  @tparam __UnaryPredicate_t 조건자의 자료형
     *  @param[in] unary_pred 조건자
     *  @return 제거된 원소의 갯수
     */
    template <class UnaryPredicate_t>
    auto RemoveIf(UnaryPredicate_t unary_pred) -> Size_t
    {
        Size_t remove_count = 0;
        for (auto it = CBeforeBegin(); it != CEnd();)
        {
            if (!unary_pred(it.operator*()))
            {
                it.operator++();
                continue;
            }

            it = EraseAfter(it);
            ++remove_count;
        }

        return remove_count;
    }

    /** @brief 특정 값을 가지는 원소를 제거한다.
     *  @param[in] value 제거할 원소의 값
     *  @return 제거된 원소의 갯수
     *
     *  @see \ref RemoveIf
     */
    inline auto Remove(const Value_t& value) -> Size_t
    {
        return RemoveIf([&value](const Value_t& val) { return val == value; });
    }

    /** @brief 다른 전방 리스트의 범위 내 원소들을 잘라내어, 이 전방 리스트의
     *  특정 위치에 이전에 삽입한다.
     *  @param[in] this_it_pos 삽입할 이 전방 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 전방 리스트
     *  @param[in] other_it_first 다른 전방 리스트에서 잘라낼 원소들의 시작 위치
     *  @param[in] other_it_last 다른 전방 리스트에서 잘라낼 원소들의 마지막
     *  위치
     *  @details
     *  잘리는 범위는 `[other_it_first, other_it_last)` 이다.\n
     *  크기 변경 연산이 포함되어 있고, 이때문에 O(1)이 아니다. 복잡도는
     *  `[other_it_first, other_it_last)`사이 원소의 갯수에 선형으로 비례한다.\n
     *  반복자들은 다음과 같은 조건을 만족해야 한다.
     *  - `this_it_pos`는 유효해야 한다.
     *  - `this_it_pos`가 이 전방 리스트와 호환되어야 한다.
     *  - `other_it_first`는 `other`와 호환되어야 한다.
     *  - `other_it_first`는 역참조 가능해야 한다.
     *  - `other_it_last`는 유효해야 한다.
     *  - `other_it_last`는 `other`와 호환되어야 한다.
     *
     *  @warning 다른 전방 리스트가 비어 있는 경우 정상적으로 범위를 전달할
     *  방법이 없으며, 전달하는 경우 Debug 구성에서는 비정상 종료하고 Release
     *  구성에서는 정의되지 않은 행동이다.
     */
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other,
                     ConstIterator_t other_it_first,
                     ConstIterator_t other_it_last) -> void
    {
        auto* other_range_before_ptr =
            const_cast<Node_S_t*>(other_it_first.GetDataPointer());
        auto* other_range_start_ptr = other_range_before_ptr->next;
        auto* other_range_after_ptr =
            const_cast<Node_S_t*>(other_it_last.GetDataPointer());

        auto*  other_range_end_ptr = other_range_start_ptr;
        Size_t other_range_node_count{1};
        while (other_range_end_ptr->next != other_range_after_ptr)
        {
            other_range_end_ptr = other_range_end_ptr->next;
            ++other_range_node_count;
        }

        auto* this_range_before_ptr =
            const_cast<Node_S_t*>(this_it_pos.GetDataPointer());
        auto* this_range_after_ptr = this_range_before_ptr->next;

        this_range_before_ptr->next = other_range_start_ptr;
        other_range_end_ptr->next   = this_range_after_ptr;

        other_range_before_ptr->next = other_range_after_ptr;

        m_size       += other_range_node_count;
        other.m_size -= other_range_node_count;
    }

    /** @overload
     *  @param[in] this_it_pos 삽입할 이 전방 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 전방 리스트
     *  @param[in] other_it_pos 다른 전방 리스트에서 잘라낼 원소들의 시작 위치
     */
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other,
                     ConstIterator_t other_it_pos) -> void
    {
        SpliceAfter(this_it_pos, other, other_it_pos, other.CEnd());
    }

    /** @overload
     *  @param[in] this_it_pos 삽입할 이 전방 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 전방 리스트
     */
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other) -> void
    {
        SpliceAfter(this_it_pos, other, other.CBeforeBegin(), other.CEnd());
    }

    template <class __Compare_t>
    auto Sort(__Compare_t comp) -> void; // TODO
    template <class __Compare_t>
    auto Merge(ForwardList& other, __Compare_t comp) -> void; // TODO
    auto Merge(ForwardList& other) -> void;                   // TODO
    template <class __Compare_t>
    auto Merge(ForwardList&& other, __Compare_t comp) -> void; // TODO
    auto Merge(ForwardList&& other) -> void;                   // TODO

    /** @brief 전방 리스트의 원소의 체결방식을 역순으로 바꾼다.
     *  @details 전방 리스트의 크기가 2 미만이면 아무런 동작도 하지 않는다.
     */
    auto Reverse() -> void
    {
        if (m_size < 2)
            return;

        auto* prev_node_ptr = std::addressof(m_sentinel_node);
        auto* curr_node_ptr = m_sentinel_node.next;
        auto* next_node_ptr = curr_node_ptr->next;

        while (next_node_ptr != std::addressof(m_sentinel_node))
        {
            curr_node_ptr->next = prev_node_ptr;
            prev_node_ptr       = curr_node_ptr;
            curr_node_ptr       = next_node_ptr;
            next_node_ptr       = next_node_ptr->next;
        }

        curr_node_ptr->next  = prev_node_ptr;
        m_sentinel_node.next = curr_node_ptr;
    }

    template <class __BinaryPredicate_t>
    auto Unique(__BinaryPredicate_t pred) -> Size_t; // TODO
    auto Unique() -> Size_t;                         // TODO

    /// @} // Operations

    /// @{ @name Comparators
public:
    /** @brief 두 전방 리스트의 동등성을 비교한다.
     *  @param other 비교할 전방 리스트
     *  @return 두 전방 리스트가 같으면 `true`, 그렇지 않으면 `false`
     *  @details 동등 비교 순서는 다음과 같다.\n
     *  1. *두 전방 리스트의 크기가 다르면*, 항상 같은 전방 리스트가 아니다.
     *  2. *두 전방 리스트의 크기가 같고 크기가 0이라면*,항상 같은 전방
     *     리스트이다.
     *  3. *두 전방 전방 리스트의 크기가 같고 크기가 0이 아니라면*, 두 전방
     *     리스트의 각 원소를 순회하며 모든 원소가 같은 경우 같은 전방
     *     리스트이고, 그렇지 않으면 다른 전방 리스트이다.
     */
    auto operator==(const ForwardList& other) const -> bool; // TODO
    auto operator!=(const ForwardList& other) const -> bool; // TODO

    /// @} // Comparators

private:
    /** @brief 전방 리스트의 센티넬 노드이다. */
    Node_S_t m_sentinel_node;
    /** @brief 전방 리스트의 크기이다. */
    Size_t   m_size{0};
};

} // namespace rds

#endif // RDS_FORWARDLIST_HPP