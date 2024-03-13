// TODO 예를 들어 List<int&> 같은게 컴파일되면 안된다. 뭔 일이 일어나는지
// 확인할 것
// TODO 반복자가 무효화되지 않는 경우에 대한 문서화

#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <initializer_list>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "AllocatorTraits.hpp"

#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"

/*
================================================================================
* List
--------------------------------------------------------------------------------
* Example of Size 0 List
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      Begin/End
    ┌────────────┐
    └╴p[ node ] ←┘
    ┌→ [   s  ]n╶┐
    └────────────┘
--------------------------------------------------------------------------------
* Example of Size n List (n!=0)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           End         Begin
    ┌──────────────────────────────────────────────────────────────────┐
    └╴p[ node ] ←─p[ node ] ←─p[ node ] ←─p[ node ]   ... ←─p[ node ] ←┘
    ┌→ [   s  ]n─→ [   0  ]n─→ [   1  ]n─→ [   2  ]n─→ ...   [   n-1]n╶┐
    └──────────────────────────────────────────────────────────────────┘
                       Front                                     Back
--------------------------------------------------------------------------------
*/

namespace rds
{

/** @brief 동적 이중 연결 리스트에 대한 템플릿 클래스
 *  @tparam __T_t 리스트 내 원소에 대한 자료형. 리스트 노드에 의해 래핑되어
 * 있다.
 *  @tparam __Alloc_t 리스트의 원소에 대한 메모리 할당자 자료형 (기본값은 \ref
 *  Nallocator)
 *  @details
 *  \ref Node_D 노드를 내부에서 사용하며, 리스트의 맨 앞에는 센티넬 노드가 항상
 *  존재한다.
 */
template <class __T_t, template <class> class __Alloc_t = Nallocator>
class List
{
public:
    /** @brief 이 리스트의 원소의 생성과 소멸을 관리하는 할당자 자료형이다.
     *
     *  @note 할당자는 `__T_t`를 생성하는 것이 아니라, `Node_D<__T_t>`
     *  를 생성한다.
     */
    using Allocator_t = __Alloc_t<Node_D<__T_t>>;
    using Size_t      = std::size_t;
    using Node_D_t    = Node_D<__T_t>;

public:
    using Value_t      = __T_t;
    using Pointer_t    = __T_t*;
    using Reference_t  = __T_t&;
    using Difference_t = std::ptrdiff_t;

public:
    using ConstIterator_t = List_ConstIterator<List>;
    using Iterator_t      = List_Iterator<List>;

public:
    /** @brief 기본 생성자
     *  @details
     *  아무 원소도 가지지 않는 리스트를 생성한다.\n 센티넬 노드의 다음 노드와
     *  이전 노드를 자기 자신으로 초기화한다.
     */
    List() { __InitializeSentinelNode(); }

    /** @brief 복사 생성자
     *  @param[in] other 복사할 다른 리스트
     *  @details 다른 리스트의 값을 순회하며 이 리스트에 `PushBack` 으로
     *  복사한다.
     */
    List(const List& other)
        : List()
    {
        // Prevents shallow copy
        for (auto it = other.CBegin(); it != other.CEnd(); ++it)
            PushBack(*it);
    }

    /** @brief 이동 생성자
     *  @param[in] temp_other 이동시킬 다른 리스트
     *  @details 리스트의 소유권을 이전시키는 작업을 한다. 다른 리스트의 센티넬
     *  노드 이후에 있는 노드들을 이 리스트로 이동시킨다.
     */
    List(List&& temp_other)
        : List()
    {
        operator=(static_cast<List&&>(temp_other));
        // named rvalue ref considered as lvalue so we fucking need to
        // static cast to &&
    }

    /** @brief 복사 대입 연산자
     *  @param[in] other 복사하여 이 리스트에 대입할 다른 리스트
     *  @return 연산 이후 이 리스트에 대한 참조
     *  @details 이 리스트의 모든 노드들을 \ref Clear 를 이용해 삭제하고, 다른
     *  리스트의 값을 순회하며 이 리스트에 \ref PushBack 으로 복사하여 넣는다.\n
     *  만일, `other`의 주소가 이 리스트와 같다면, 아무런 동작도 하지 않는다.
     */
    auto operator=(const List& other) -> List&
    {
        // 애초에 같은 거면 복사고 뭐고 할 필요가 없다.
        if (this == &other)
            return *this;

        // 기존의 노드들을 모두 삭제
        Clear();

        // 다른 리스트의 값을 순회하며 이 리스트에 `PushBack` 으로 복사
        for (auto it = other.CBegin(); it != other.CEnd(); ++it)
            PushBack(*it);
        return *this;
    }

    /** @brief 이동 대입 연산자
     *  @param[in] temp_other 이동하여 이 리스트에 대입할 다른 리스트
     *  @return 연산 이후 이 리스트에 대한 참조
     *  @details 우선 이 리스트의 모든 노드들을 \ref Clear 를 이용해 삭제한다.
     */
    auto operator=(List&& temp_other) -> List&
    {
        /*
        ------------------------------------------------------------------------
         * Before operator=(List&& temp_other)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         + temp_other:
            [s]n->   <-p[A]n->   <-p[B]n->   <-p[s]
         + this:
            [s]n->  <-p[s]
        ------------------------------------------------------------------------
         * After operator=(List&& temp_other)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         + temp_other:
            [s]n->>                   <<-p[s]
         + this:
            [s]n->> <<-p[A]n->   <-p[B]n->> <<-p[s]
        ------------------------------------------------------------------------
         6 Links to be updated:
        */

        Clear();

        // `temp_other`가 비어있으면 앞으로 나올 로직이 고장난다.
        if (temp_other.m_size == 0)
            return *this;

        // 소유권을 이전시킨다
        // 총 6개의 링크가 업데이트 되어야 함
        auto* temp_first_node_ptr = temp_other.m_sentinel_node.next;
        auto* temp_last_node_ptr  = temp_other.m_sentinel_node.prev;

        m_sentinel_node.next = temp_other.m_sentinel_node.next;
        m_sentinel_node.prev = temp_other.m_sentinel_node.prev;

        temp_first_node_ptr->prev = &m_sentinel_node;
        temp_last_node_ptr->next  = &m_sentinel_node;

        // `temp_other` 가 소멸되면서 노드들이 해제되는걸 방지하기 위해
        // 자기 자신을 가리키게 하자. (`nullptr` 이면 소멸자에서 순회를 못 함)
        temp_other.m_sentinel_node.next = &temp_other.m_sentinel_node;
        temp_other.m_sentinel_node.prev = &temp_other.m_sentinel_node;

        // 크기도 이전시킴
        m_size = temp_other.m_size;

        return *this;
    }

    /** @brief 소멸자. 리스트가 보유한 노드들을 정리한다.
     *  @details \ref Clear 메서드를 호출하여 동적으로 할당된 모든 노드들을
     * 정리한다.
     */
    ~List() noexcept { Clear(); }

    /** @brief 리스트의 초기 크기와 초기 값을 지정하는 생성자
     *  @param[in] size 생성할 리스트의 크기
     *  @param[in] init_val 생성할 리스트의 초기값.
     *  @details `size` 가 0이면, `init_val`에 상관없이 아무 동작도 하지 않는다.
     */
    List(Size_t size, const Value_t& init_val = Value_t())
        : List()
    {
        for (Size_t i = 0; i < size; ++i)
            PushBack(init_val);
    }

    /** @brief 초기화 리스트를 받는 생성자
     *  @param[in] ilist 초기화 리스트
     */
    List(const std::initializer_list<Value_t>& ilist)
        : List()
    {
        for (const auto& e: ilist)
            PushBack(e);
    }

    /** @brief 초기화 리스트를 받는 대입 연산자
     *  @param[in] ilist 초기화 리스트
     *  @return 연산 이후의 이 리스트에 대한 참조
     */
    auto operator=(const std::initializer_list<Value_t>& ilist) -> List&
    {
        Clear();

        for (const auto& e: ilist)
            PushBack(e);
        return *this;
    }

    template <class __InputIterator_t>
    auto Assign(__InputIterator_t it_first, __InputIterator_t it_last)
        -> void;                                                      // TODO
    auto Assign(Size_t count, const Value_t& val) -> void;            // TODO
    auto Assign(const std::initializer_list<Value_t>& ilist) -> void; // TODO

    /// @{  @name Node Management

private:
    /** @brief 센티넬 노드의 두 링크를 자기 자신을 가리키도록 초기화한다. */
    inline auto __InitializeSentinelNode() -> void
    {
        m_sentinel_node.next = &m_sentinel_node;
        m_sentinel_node.prev = &m_sentinel_node;
    }

public:
    // TODO  Node_D의 복사 생성자를 호출하는지 확인해야함
    /** @brief 새로운 노드를 생성하고 그 노드의 주소를 반환한다.
     *  @param[in] val 새로 생성될 노드에 들어갈 값
     *  @return 새로 생성된 노드의 주소
     */
    static auto CreateNode(const Value_t& val) -> Node_D_t*
    {
        Node_D_t* ptr = AllocatorTraits<Allocator_t>::Allocate(1);
        AllocatorTraits<Allocator_t>::Construct(ptr, 1, val);

        return ptr;
    }

    /** @copybrief CreateNode(const Value_t&)
     *  @tparam __CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     * 인자들의 자료형 목록
     *  @param[in] ctor_args 노드가 보유한 값의 자료형의 생성자에 전달할 인자들
     *  @return 새로 생성된 노드의 주소
     *
     *  @note \ref Node_D 의 연관된 생성자를 호출한다.
     */
    template <class... __CtorArgs_t>
    static auto CreateNode(__CtorArgs_t&&... ctor_args) -> Node_D_t*
    {
        Node_D_t* ptr = AllocatorTraits<Allocator_t>::Allocate(1);
        AllocatorTraits<Allocator_t>::Construct(
            ptr, 1, std::forward<__CtorArgs_t>(ctor_args)...);

        return ptr;
    }

    /** @brief 전달된 포인터에 있는 노드를 삭제한다.
     *  @param[in] node_ptr 삭제할 노드의 주소
     */
    static auto DeleteNode(const Node_D_t* node_ptr) -> void
    {
        AllocatorTraits<Allocator_t>::Deconstruct(node_ptr, 1);
        AllocatorTraits<Allocator_t>::Deallocate(node_ptr);
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
        RDS_Assert(GetSentinelPointer()->next != GetSentinelPointer() &&
                   GetSentinelPointer()->prev != GetSentinelPointer() &&
                   "Cannot access front in empty list.");
        return m_sentinel_node.next->val;
    }

    /** @copydoc Front() const
     *
     */
    auto Front() -> Value_t&
    {
        return const_cast<Value_t&>(static_cast<const List&>(*this).Front());
    }

    /** @brief 마지막 원소에 대한 참조를 반환한다.
     *  @return 마지막 원소에 대한 참조
     *
     *  @warning Debug 구성에서 리스트가 비어있는 경우 비정상 종료하고, Release
     *  구성에서는 정의되지 않은 행동이다.
     */
    auto Back() const -> const Value_t&
    {
        RDS_Assert(static_cast<int>(m_size) > 0 &&
                   "Cannot access back in empty list.");
        return m_sentinel_node.prev->val;
    }

    /** @copydoc Back() const
     *
     */
    auto Back() -> Value_t&
    {
        return const_cast<Value_t&>(static_cast<const List&>(*this).Back());
    }

    /** @brief 센티넬 노드에 대한 상수 포인터를 반환한다.
     *  @return 센티넬 노드에 대한 상수 포인터
     *
     *  @warning 센티넬 노드의 값은 아무런 의미가 없으며, 이에 접근하거나
     *  변경하려는 시도는 모두 정의되지 않은 행동이다.
     */
    auto GetSentinelPointer() const -> const Node_D_t*
    {
        return &m_sentinel_node;
    }

    /// @}

    /// @{ @name Iterators

public:
    /** @brief 첫 번째 원소를 가리키는 반복자를 반환한다.
     *  @return 첫 번째 원소를 가리키는 반복자
     *
     *  @warning 비어 있는 리스트에 대해서도 호출할 수 있지만, 이렇게 얻어진
     *  반복자는 역참조하면 안된다. 역참조시 Debug 구성에서는 비정상 종료하며,
     *  Release 구성에서는 정의되지 않은 행동이다.
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
    /** @brief 리스트의 크기를 반환한다.
     *  @return 리스트의 크기
     *  @details O(1) 이다.
     */
    auto Size() const -> Size_t { return m_size; }

    auto MaxSize() const -> Size_t; // TODO

    /** @brief 리스트가 비어있는지 확인한다.
     *  @return 리스트가 비어있으면 `true`, 그렇지 않으면 `false`이다.
     */
    auto Empty() const -> bool { return m_size == 0; }

    /// @} // Capacity

    ///@{ @name Modifiers

public:
    /** @brief 리스트의 모든 원소(노드)를 삭제하고, 센티넬 노드를 초기화한다.
     *  @details 리스트가 현재 보유하고 있는 모든 노드들을 삭제한다. 그리고,
     *  센티넬 노드를 초기화한다. 만일 리스트가 비어있다면, 아무런 동작도 하지
     *  않는다.
     */
    auto Clear() -> void
    {
        // 첫 번째 노드의 주소를 가져온다.
        auto* ptr = m_sentinel_node.next;

        // 센티넬 노드 다음부터 시작하여 센티넬 노드까지 순회하며 메모리 해제
        // 이 리스트가 비어 있다면 첫 번째 노드의 주소가 센티넬 노드의 주소와
        // 동일하므로 while 문으로 진입하지 않는다.
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
    /** @brief 주어진 리스트의 위치 이전에 입력 반복자로 전달된 컨테이너의
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
    //                   __InputIterator_t other_it_last) -> Iterator_t;

    // TODO Release 구성에서 예외를 던지도록 구현하는 것이 나을 수도 있다.
    /** @brief 반복자가 가리키는 위치 이전에 새 원소들을 삽입한다.
     *  @param[in] it_pos 삽입할 위치를 나타내는 반복자로, 이 반복자가 가리키는
        노드 이전에 새 노드가 삽입된다.
     *  @param[in] count 삽입할 원소의 갯수
     *  @param[in] val 삽입할 원소들이 가질 값
     *  @return 삽입된 노드들 중 첫 번째 노드를 가리키는 반복자
     *
     *  @note 호출 후 기존의 반복자들이 무효화되지 않으며, `it_pos`가 역참조
     가능할 필요는 없다.
     *  @warning Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로 호출하는
        경우 비정상 종료하고, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto InsertBefore(ConstIterator_t it_pos, Size_t count, const Value_t& val)
        -> Iterator_t
    {
        RDS_Assert(it_pos.IsValid() && "Invalid iterator.");
        RDS_Assert(it_pos.IsCompatible(*this) && "List is not compatible.");

        // 삽입할 원소의 갯수가 1 미만이면 아무런 동작도 하지 않고 it_pos를
        // 그대로 반환한다.
        if (count < 1)
            return Iterator_t(this, it_pos.GetDataPointer());

        /*
        ------------------------------------------------------------------------
         * Before InsertBefore(it_pos, count, val)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                               it_pos.m_data_ptr
                                 ↓
         <-p[ ]n-> <-p[ ]n-> <-p[ ]n-> <-p[ ]n->
                       ↑         ↑
                   prev_node_ptr next_node_ptr
        ------------------------------------------------------------------------
         * After InsertBefore(it_pos, count, val)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                        [return] nn_head   nn_tail     it_pos.m_data_ptr
                                   ↓         ↓           ↓
         <-p[ ]n-> <-p[ ]n->> <<-p[N]n-> <-p[N]n->> <<-p[ ]n->
                       ↑                                 ↑
                   prev_node_ptr                     next_node_ptr
        ------------------------------------------------------------------------
          4 Links to be updated:
        */

        auto* next_node_ptr = const_cast<Node_D_t*>(it_pos.GetDataPointer());
        auto* prev_node_ptr = next_node_ptr->prev;

        /*
         새로 삽입될 노드들을 위한 포인터
         여러 개 삽입되기 때문에 가장 선두(head)에 있는 노드의 주소와
         가장 마지막(tail)에 있는 노드의 주소를 따로 저장한다.
        */
        Node_D_t* new_node_ptr_head = CreateNode(val);
        auto*     new_node_ptr_tail = new_node_ptr_head;

        // 새로운 노드들을 생성하고 연결한다.
        for (Size_t i = 1; i < count; ++i)
        {
            Node_D_t* new_node_ptr = CreateNode(val);

            new_node_ptr_tail->next = new_node_ptr;
            new_node_ptr->prev      = new_node_ptr_tail;

            new_node_ptr_tail = new_node_ptr;
        }

        // 연결된 새 노드들을 이제 리스트의 올바른 위치에 연결한다.
        new_node_ptr_tail->next = next_node_ptr;
        next_node_ptr->prev     = new_node_ptr_tail;

        prev_node_ptr->next     = new_node_ptr_head;
        new_node_ptr_head->prev = prev_node_ptr;

        m_size += count;

        return Iterator_t(this, new_node_ptr_head);
    }

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
                      const std::initializer_list<Value_t>& ilist) -> Iterator_t
    {
        for (const auto& e: ilist)
            InsertBefore(it_pos, e);
        return Iterator_t(this, it_pos.GetDataPointer());
    }

    /** @brief 인자로 전달된 값을 리스트의 맨 앞에 추가한다.
     *  @param[in] val 추가할 원소의 값
     *
     *  @note 비어 있는 리스트에서 이 연산을 수행해도 안전하다.
     *  @see \ref InsertBefore(ConstIterator_t,const Value_t&)
     */
    auto PushFront(const Value_t& val) -> void { InsertBefore(CBegin(), val); }

    /** @brief 인자로 전달된 값을 리스트의 맨 뒤에 삽입한다.
     *  @param[in] val 삽입할 원소의 값
     *
     *  @note `InsertBefore` 메서드를 내부에서 \ref CEnd 를 인자로 호출하므로,
     *  항상 안전하게 수행된다.
     *  @see \ref InsertBefore(ConstIterator_t,const Value_t&)
     */
    auto PushBack(const Value_t& val) -> void { InsertBefore(CEnd(), val); }

    // TODO Release 구성에서 예외를 던지도록 구현하는 것이 나을 수도 있다.
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
    auto EmplaceBefore(ConstIterator_t it_pos, __CtorArgs_t&&... ctor_args)
        -> Iterator_t
    {
        RDS_Assert(it_pos.IsValid() && "Invalid iterator.");
        RDS_Assert(it_pos.IsCompatible(*this) && "List is not compatible.");

        Node_D_t* new_node_ptr =
            CreateNode(std::forward<__CtorArgs_t>(ctor_args)...);

        auto* ins_node_ptr = const_cast<Node_D_t*>(it_pos.GetDataPointer());

        auto* prev_node_ptr =
            const_cast<Node_D_t*>(it_pos.GetDataPointer())->prev;
        auto* next_node_ptr = ins_node_ptr;

        new_node_ptr->next = next_node_ptr;
        new_node_ptr->prev = prev_node_ptr;

        prev_node_ptr->next = new_node_ptr;
        next_node_ptr->prev = new_node_ptr;

        ++m_size;

        return Iterator_t(this, new_node_ptr);
    }

    /** @brief 전달된 생성자 인자들로 새 원소를 생성해 리스트의 맨 앞에
     * 추가한다.
     *  @tparam __CtorArgs_t 새로 생성될 원소의 생성자에 전달할 인자들의 자료형
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 원소를 가리키는 반복자. \ref Begin 과 같다.
     *
     *  @note 비어 있는 리스트에서 이 연산을 수행해도 안전하다.
     *  @see \ref EmplaceBefore
     */
    template <class... __CtorArgs_t>
    auto EmplaceFront(__CtorArgs_t&&... ctor_args) -> Iterator_t
    {
        return EmplaceBefore(CBegin(),
                             std::forward<__CtorArgs_t>(ctor_args)...);
    }

    /** @brief 전달된 생성자 인자들로 새 원소를 생성해 리스트의 맨 뒤에
     * 추가한다.
     *  @tparam __CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     *  인자들의 자료형
     *  @param[in] ctor_args 새로 생성될 원소의 생성자에 전달할 인자들
     *  @return 새로 생성된 노드를 가리키는 반복자. \ref End 의 이전과 같다.
     *
     *  @note 비어 있는 리스트에서 이 연산을 수행해도 안전하다.
     *  @see \ref EmplaceBefore
     */
    template <class... __CtorArgs_t>
    auto EmplaceBack(__CtorArgs_t&&... ctor_args) -> Iterator_t
    {
        return EmplaceBefore(CEnd(), std::forward<__CtorArgs_t>(ctor_args)...);
    }

    // TODO 삭제 순회 중에 센티넬 노드를 만날 가능성을 완전히 배제할 수 없다는
    // 점
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
    auto Erase(ConstIterator_t it_first, ConstIterator_t it_last) -> Iterator_t
    {
        // it_first 가 역참조 불가능하다는 것은 센티넬 노드임을 포함
        RDS_Assert(it_first.IsDereferencible() &&
                   "Start of range is not dereferencible.");
        RDS_Assert(it_last.IsValid() && "End of range is not valid.");
        RDS_Assert(it_first.IsCompatible(*this) &&
                   "List is not compatible with given iterator.");
        RDS_Assert(it_last.IsCompatible(*this) &&
                   "List is not compatible with given iterator.");

        // TODO 이게 없어도 되는지 확인
        if (it_first.operator==(it_last))
            return Iterator_t(this, it_last.GetDataPointer());

        /*
        ------------------------------------------------------------------------
         * Before Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                   range_start(it_first)
                        ↓
         ... ←p[B]n→ ←p[X]n→ ←p[X]n→ ←p[X]n→ ←p[A]n→ ...
                ↑                               ↑
           range_before                    range_after(it_last)
        ------------------------------------------------------------------------
         * After Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

         ... ←p[B]n->>                     <<-p[A]n→ ...
                ↑                               ↑
           range_before                    range_after(it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            2 links to be updated:
        ------------------------------------------------------------------------
        */

        auto* range_start_ptr =
            const_cast<Node_D_t*>(it_first.GetDataPointer());
        auto* range_before_ptr = range_start_ptr->prev;

        auto* range_after_ptr = const_cast<Node_D_t*>(it_last.GetDataPointer());

        // 삭제 범위 전후 노드에 대한 재연결
        range_before_ptr->next = range_after_ptr;
        range_after_ptr->prev  = range_before_ptr;

        // 삭제 범위 순회하며 노드 삭제
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
     *  @brief 반복자가 가리키는 위치에 있는 원소를 제거한다.
     *  @param[in] it_pos 제거할 원소의 위치를 가리키는 반복자
     *  @return 제거된 원소의 다음 위치를 가리키는 반복자
     *
     *  @warning Debug 구성에서 전달된 반복자가 더이상 증가시킬 수 없는 반복자인
     *  경우 비정상 종료하며, Release 구성에서는 정의되지 않은 행동이다.
     */
    auto Erase(ConstIterator_t it_pos) -> Iterator_t
    {
        auto it_last = it_pos;
        it_last.operator++();
        return Erase(it_pos, it_last);
    }

    /** @brief 리스트의 맨 뒤에서 원소를 제거한다.
     *
     *  @warning Debug 구성에서 비어있는 리스트에 대해 호출되는 경우 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     *  @see \ref Erase(ConstIterator_t)
     */
    auto PopBack() -> void { Erase(CEnd().operator--()); }

    /** @brief 리스트의 맨 앞에서 원소를 제거한다.
     *
     *  @warning Debug 구성에서 비어있는 리스트에 대해 호출되는 경우 비정상
     *  종료하고, Release 구성에서는 정의되지 않은 행동이다.
     *  @see \ref Erase(ConstIterator_t)
     */
    auto PopFront() -> void { Erase(CBegin()); }

    /** @brief 인자로 전달된 리스트와 이 리스트의 내용을 서로 바꾼다.
     *  @param[in] other 바꿀 대상이 되는 다른 리스트
     *  @details 한쪽이 비어있는 경우에도 정상 작동한다.
     */
    auto Swap(List& other) -> void
    {
        /*
        ------------------------------------------------------------------------
        * Before Swap(List&)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        - this:
            [st]n->   <-p[At]n->   <-p[Bt]n->   <-p[st]
        - other:
            [so]n->   <-p[Ao]n->                <-p[so]
        ------------------------------------------------------------------------
        * After Swap(List&)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        - this:
            [st]n->> <<-p[Ao]n->>              <<-p[st]
        - other:
            [so]n->> <<-p[At]n->   <-p[Bt]n->> <<-p[so]
        ------------------------------------------------------------------------
         8 Links to be updated:
        */

        // 각각이 비어있는경우 상대의 센티넬 노드로 초기화 해줘야 말이 됨
        auto* this_nodes_head_ptr =
            !Empty() ? m_sentinel_node.next : &other.m_sentinel_node;
        auto* this_nodes_tail_ptr =
            !Empty() ? m_sentinel_node.prev : &other.m_sentinel_node;

        auto other_nodes_head_ptr =
            !other.Empty() ? other.m_sentinel_node.next : &m_sentinel_node;
        auto other_nodes_tail_ptr =
            !other.Empty() ? other.m_sentinel_node.prev : &m_sentinel_node;

        // 8개의 링크를 업데이트 한다
        other.m_sentinel_node.next = this_nodes_head_ptr;
        other.m_sentinel_node.prev = this_nodes_tail_ptr;
        this_nodes_head_ptr->prev  = &other.m_sentinel_node;
        this_nodes_tail_ptr->next  = &other.m_sentinel_node;

        m_sentinel_node.next       = other_nodes_head_ptr;
        m_sentinel_node.prev       = other_nodes_tail_ptr;
        other_nodes_head_ptr->prev = &m_sentinel_node;
        other_nodes_tail_ptr->next = &m_sentinel_node;

        // 크기도 바꿔준다
        auto temp_size = m_size;
        m_size         = other.m_size;
        other.m_size   = temp_size;
    }

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

    ///@}

    /// @{ @name Operations

public:
    /** @brief 조건에 맞는 원소를 제거한다.
     *  @tparam __UnaryPredicate_t 조건자의 자료형
     *  @param[in] unary_pred 조건자
     *  @return 제거된 원소의 갯수
     */
    template <class __UnaryPredicate_t>
    auto RemoveIf(__UnaryPredicate_t unary_pred) -> Size_t
    {
        Size_t remove_count = 0;
        for (auto it = CBegin(); it != CEnd();)
        {
            if (!unary_pred(it.operator*()))
            {
                it.operator++();
                continue;
            }

            it = Erase(it);
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

    /** @brief 다른 리스트의 범위 내 원소들을 잘라내어, 이 리스트의 특정 위치에
     *  이전에 삽입한다.
     *  @param[in] this_it_pos 삽입할 이 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 리스트
     *  @param[in] other_it_first 다른 리스트에서 잘라낼 원소들의 시작 위치
     *  @param[in] other_it_last 다른 리스트에서 잘라낼 원소들의 마지막 위치
     *  @details
     *  잘리는 범위는 `[other_it_first, other_it_last)` 이다.\n
     *  크기 변경 연산이 포함되어 있고, 이때문에 O(1)이 아니다. 복잡도는
     *  `[other_it_first, other_it_last)`사이 원소의 갯수에 선형으로 비례한다.\n
     *  반복자들은 다음과 같은 조건을 만족해야 한다.
     *  - `this_it_pos`는 유효해야 한다.
     *  - `this_it_pos`가 이 리스트와 호환되어야 한다.
     *  - `other_it_first`는 `other`와 호환되어야 한다.
     *  - `other_it_first`는 역참조 가능해야 한다.
     *  - `other_it_last`는 유효해야 한다.
     *  - `other_it_last`는 `other`와 호환되어야 한다.
     *
     *  @warning 다른 리스트가 비어 있는 경우 정상적으로 범위를 전달할 방법이
     *  없으며, 전달하는 경우 Debug 구성에서는 비정상 종료하고 Release
     * 구성에서는 정의되지 않은 행동이다.
     */
    auto SpliceAndInsertBefore(ConstIterator_t this_it_pos, List& other,
                               ConstIterator_t other_it_first,
                               ConstIterator_t other_it_last) -> void
    {
        // 1) this_it_pos 검사
        // - 유효해야함
        // - 이 리스트와 호환되어야 함
        RDS_Assert(this_it_pos.IsValid() && "Invalid iterator.");
        RDS_Assert(this_it_pos.IsCompatible(*this) &&
                   "List is not compatible.");
        // 2) other_it_first 검사
        // - 다른 리스트와 호환되어야 함
        // - 역참조 가능해야 함
        RDS_Assert(other_it_first.IsCompatible(other) &&
                   "List is not compatible.");
        RDS_Assert(other_it_first.IsDereferencible() && "Start of range is not "
                                                        "dereferencible.");
        // 3) other_it_last 검사
        // - 유효해야함
        // - 다른 리스트와 호환되어야 함
        RDS_Assert(other_it_last.IsValid() && "End of range is not valid.");
        RDS_Assert(other_it_last.IsCompatible(other) &&
                   "List is not compatible.");
        // clang-format off
/*
--------------------------------------------------------------------------------
* Before SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t, ConstIterator_t)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
this:
                       this_it_pos
                           ↓
[st]n->   <-p[At]n->   <-p[Bt]n->   <-p[st]
              ↑            ↑
         range_before range_after
other:
            it_first                  it_last
              ↓                         ↓
[so]n->   <-p[Ao]n->   <-p[Bo]n->   <-p[Co]n->   <-p[so]
 ↑            ↑            ↑            ↑
 |       range_start  range_end         |
range_before                       range_after
--------------------------------------------------------------------------------
* After SpliceAndInsertBefore(ConstIterator_t, List&, ConstIterator_t, ConstIterator_t)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
this:
                                                 this_it_pos
                                                     ↓
[st]n->   <-p[At]n->> <<-p[Ao]n->   <-p[Bo]n->> <<-p[Bt]n->   <-p[st]
              ↑                                      ↑
         range_before                           range_after
other:


[so]n->>              <<-p[Co]n->   <-p[so]
 ↑                         ↑
 |                         |
range_before          range_after
--------------------------------------------------------------------------------
*/
        // clang-format on

        // 잘라낼 범위가 비어있으면 아무런 동작도 하지 않는다.
        if (other_it_first == other_it_last)
            return;

        // 범위 설정
        auto* other_range_start_ptr =
            const_cast<Node_D_t*>(other_it_first.GetDataPointer());
        auto* other_range_before_ptr = other_range_start_ptr->prev;

        auto* other_range_after_ptr =
            const_cast<Node_D_t*>(other_it_last.GetDataPointer());
        auto* other_range_end_ptr = other_range_after_ptr->prev;

        // 이 부분 때문에 O(1) 이 아니다.
        Size_t other_range_node_count{0};
        for (auto it = other_range_start_ptr; it != other_range_after_ptr;
             it      = it->next)
        {
            ++other_range_node_count;
        }

        auto* this_range_before_ptr =
            const_cast<Node_D_t*>(this_it_pos.GetDataPointer())->prev;
        auto* this_range_after_ptr = this_range_before_ptr->next;

        other_range_before_ptr->next = other_range_after_ptr;
        other_range_after_ptr->prev  = other_range_before_ptr;

        this_range_before_ptr->next = other_range_start_ptr;
        other_range_start_ptr->prev = this_range_before_ptr;

        this_range_after_ptr->prev = other_range_end_ptr;
        other_range_end_ptr->next  = this_range_after_ptr;

        // 크기 업데이트
        m_size       += other_range_node_count;
        other.m_size -= other_range_node_count;
    }

    /** @overload
     *  @param[in] this_it_pos 삽입할 이 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 리스트
     *  @param[in] other_it_pos 다른 리스트에서 잘라낼 원소들의 시작 위치
     */
    inline auto SpliceAndInsertBefore(ConstIterator_t this_it_pos, List& other,
                                      ConstIterator_t other_it_pos) -> void
    {
        SpliceAndInsertBefore(this_it_pos, other, other_it_pos, other.CEnd());
    }

    /** @overload
     *  @param[in] this_it_pos 삽입할 이 리스트의 위치
     *  @param[in] other 원소들을 잘라낼 다른 리스트
     */
    inline auto SpliceAndInsertBefore(ConstIterator_t this_it_pos, List& other)
        -> void
    {
        SpliceAndInsertBefore(this_it_pos, other, other.CBegin());
    }

    template <class __Compare_t>
    auto Sort(__Compare_t comp) -> void; // TODO
    /** @brief 정렬된 리스트끼리 병합하여 정렬된 리스트를 만든다.
     */
    template <class __Compare_t>
    auto Merge(List& other, __Compare_t comp) -> void; // TODO
    auto Merge(List& other) -> void;                   // TODO
    template <class __Compare_t>
    auto Merge(List&& other, __Compare_t comp) -> void; // TODO
    auto Merge(List&& other) -> void;                   // TODO

    /** @brief 리스트의 원소의 체결방식을 역순으로 바꾼다.
     *  @details 리스트의 크기가 2 미만이면 아무런 동작도 하지 않는다.
     */
    auto Reverse() -> void
    {
        if (m_size < 2)
            return;

        auto* prev_node_ptr = &m_sentinel_node;
        auto* curr_node_ptr = m_sentinel_node.next;
        auto* next_node_ptr = curr_node_ptr->next;

        while (curr_node_ptr != &m_sentinel_node)
        {
            curr_node_ptr->prev = next_node_ptr;
            curr_node_ptr->next = prev_node_ptr;

            prev_node_ptr = curr_node_ptr;
            curr_node_ptr = next_node_ptr;
            next_node_ptr = next_node_ptr->next;
        }

        m_sentinel_node.next = prev_node_ptr;
        m_sentinel_node.prev = curr_node_ptr;
    }

    // TODO Unique 계열 함수 구현
    template <class __BinaryPredicate_t>
    auto Unique(__BinaryPredicate_t pred) -> Size_t; // TODO
    auto Unique() -> Size_t;                         // TODO

    /// @}

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
    auto operator==(const List& other) const -> bool; // TODO

    /** @brief 두 컨테이너의 비동등성을 비교한다.
     *  @see \ref operator==(const List&) const
     */
    auto operator!=(const List& other) const -> bool; // TODO

    /// @} // Comparators

private:
    /** @brief 리스트의 센티넬 노드 */
    Node_D_t m_sentinel_node{};
    /** @brief 리스트의 크기 */
    Size_t   m_size{0};
};

} // namespace rds

#endif // RDS_LIST_HPP