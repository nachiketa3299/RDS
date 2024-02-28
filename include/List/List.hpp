/// @file List.hpp

#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "Allocator_Trait.hpp"

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

RDS_BEGIN

/// @todo 예를 들어 List<int&> 같은게 컴파일되면 안된다. 뭔 일이 일어나는지
/// 확인할 것

/** @brief 동적 이중 연결 리스트에 대한 템플릿 클래스
 *  @tparam __T_t 리스트 내 원소에 대한 자료형. 리스트 노드에 의해 래핑되어
 * 있다.
 *  @tparam __Alloc_t 리스트의 원소에 대한 메모리 할당자 자료형 (기본값은 \ref
 *  Nallocator)
 *  @details
 *  \ref Node_D 노드를 내부에서 사용한다.\n
 *  리스트의 최전방에는 센티넬 노드가 항상 존재한다.
 */
template <class __T_t, template <class> class __Alloc_t = Nallocator>
class List
{
public:
    /** @brief 이 리스트의 원소의 생성과 소멸을 관리하는 할당자 자료형이다.
     *  @note 할당자는 `__T_t`를 생성하는 것이 아니라, `Node_D<__T_t>`
     *  를 생성한다.
     */
    using Allocator_t = __Alloc_t<Node_D<__T_t>>;

public:
    using Value_t      = __T_t;
    using Pointer_t    = __T_t*;
    using Reference_t  = __T_t&;
    using Difference_t = std::ptrdiff_t;

public:
    using Size_t   = std::size_t;
    using Node_D_t = Node_D<__T_t>;

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

    /** @brief 리스트의 초기 크기와 초기 값을 지정하는 생성자
     *  @param[in] size 생성할 리스트의 크기
     *  @param[in] init_val 생성할 리스트의 초기값. 모든 원소가 이 값으로
     *  초기화된다.
     *  @details `size` 가 0이면, `init_val`에 상관없이 아무 동작도 하지 않는다.
     */
    List(Size_t size, const Value_t& init_val)
        : List()
    {
        for (Size_t i = 0; i < size; ++i)
            PushBack(init_val);
    }

    /** @brief 리스트의 초기 크기를 지정하는 생성자.
     *  @details 전달된 크기만큼의 리스트를 생성하며, 각 원소는 기본 초기화된다.
     */
    List(Size_t size)
        : List(size, Value_t())
    {}

    /** @brief `std::initializer_list` 를 통해 초기화하는 생성자
     *  @param[in] ilist 초기화에 사용할 `std::initializer_list`
     */
    List(const std::initializer_list<Value_t>& ilist)
        : List()
    {
        for (const auto& e: ilist)
            PushBack(e);
    }

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
     *  @details 이 리스트의 모든 노드들을 `Clear`를 이용해 삭제하고, 다른
     *  리스트의 값을 순회하며 이 리스트에 `PushBack`으로 복사하여 넣는다.\n
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
     *  @details 우선 이 리스트의 모든 노드들을 `Clear`를 이용해 삭제한다.
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

    /** @brief 초기화 리스트를 받는 대입 연산자
     *  @param[in] ilist 이 리스트에 대입할 값들을 가지고 있는 초기화 리스트
     *  @return 연산 이후의 이 리스트에 대한 참조
     */
    auto operator=(const std::initializer_list<Value_t>& ilist) -> List&
    {
        Clear();

        for (const auto& e: ilist)
            PushBack(e);
        return *this;
    }

    /** @brief 소멸자. 리스트가 보유한 노드들을 정리한다.
     *  @details `Clear` 메서드를 호출하여 동적으로 할당된 모든 노드들을
     * 정리한다.
     */
    ~List() noexcept { Clear(); }

    /// @{  @name Node Management
    ///     @details 노드의 생성과 삭제는 리스트의 할당자에 의해 수행된다.
    ///     @warning `Emplace` 계열 메서드와 `Splice` 계열 메서드는 노드의
    ///     갯수가 바뀜에도 불구하고 아래 메서드들이 관여하지 않으므로 주의한다.
private:
    /** @brief 센티넬 노드의 두 링크를 자기 자신을 가리키도록 초기화한다.
     */
    inline auto __InitializeSentinelNode() -> void
    {
        m_sentinel_node.next = &m_sentinel_node;
        m_sentinel_node.prev = &m_sentinel_node;
    }

public:
    /**
     * @brief 새로운 노드를 생성하고 그 노드의 주소를 반환한다.
     * @param[in] val 새로 생성될 노드에 들어갈 값
     * @return 새로 생성된 노드의 주소
     */
    static auto CreateNode(const Value_t& val) -> Node_D_t*
    {
        Node_D_t* ptr = Allocator_Trait<Allocator_t>::Allocate(1);
        Allocator_Trait<Allocator_t>::Construct(ptr, 1, val);

        return ptr;
    }

    /**
     * @brief 전달된 포인터에 있는 노드를 삭제한다.
     * @param[in] node_ptr 삭제할 노드의 주소
     */
    static auto DeleteNode(const Node_D_t* node_ptr) -> void
    {
        Allocator_Trait<Allocator_t>::Deconstruct(node_ptr, 1);
        Allocator_Trait<Allocator_t>::Deallocate(node_ptr);
    }

    /// @}

    /// @{  @name Access
public:
    /** @brief 첫번째 원소에 대한 참조를 반환한다.
     *  @return 첫번째 원소에 대한 참조
     */
    auto Front() const -> const Value_t&
    {
        RDS_Assert(static_cast<int>(m_size) > 0 &&
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

public:
    /** @brief 센티넬 노드에 대한 상수 포인터를 반환한다.
     *  @return 센티넬 노드에 대한 상수 포인터
     *  @note 센티넬 노드의 값은 아무런 의미가 없으며, 변경하는 것은 Undefined
     *  Behavior 이다.
     */
    auto GetSentinelPointer() const -> const Node_D_t*
    {
        return &m_sentinel_node;
    }

    /// @}

    /// @{ @name Iterators
public:
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    auto Begin() const -> ConstIterator_t
    {
        return ConstIterator_t(this, m_sentinel_node.next);
    }

    /// @brief 리스트의 첫 번째 원소를 가리키는 반복자를 반환한다.
    auto Begin() -> Iterator_t
    {
        return Iterator_t(this, m_sentinel_node.next);
    }

    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환한다.
    auto End() const -> ConstIterator_t
    {
        return ConstIterator_t(this, std::addressof(m_sentinel_node));
    }

    /// @brief 리스트의 마지막 원소를 가리키는 반복자를 반환한다.
    auto End() -> Iterator_t
    {
        return Iterator_t(this, std::addressof(m_sentinel_node));
    }

public:
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    auto CBegin() const -> ConstIterator_t { return Begin(); }

    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환하낟.
    auto CEnd() const -> ConstIterator_t { return End(); }

    /// @}

    /// @{ @name Capacity
public:
    /**
     * @brief 리스트의 크기를 반환한다.
     * @return 리스트의 크기
     * @details O(1) 이다.
    /// @todo 크기를 변경시키는 모든 메서드에 대해서 테스트를 수행할 것
     */
    auto Size() const -> Size_t { return m_size; }

    /// @todo MaxSize() 메서드 구현하기
    auto MaxSize() const -> Size_t;

    /**
     * @brief 리스트가 비어있는지 확인한다.
     * @return 리스트가 비어있으면 `true`, 그렇지 않으면 `false`이다.
    /// @todo 크기를 변경시키는 모든 메서드에 대해서 테스트를 수행할 것
     */
    auto Empty() const -> bool { return m_size == 0; }

    /// @}

public:
    ///@{ @name Modifiers
    /// 아래 메서드들은 모두 리스트의 크기(`m_size`)를 변경시키므로, 주의한다.
    /**
     * @brief 리스트의 모든 원소(노드)를 삭제하고, 센티넬 노드를 초기화한다.
     * @details 리스트가 현재 보유하고 있는 모든 노드들을 삭제한다. 그리고,
     * 센티넬 노드를 초기화한다.\n
     * 만일 리스트가 비어있다면, 아무런 동작도 하지 않는다.
     * @note 비어 있는 리스트에 대해서도 안전하게 작동한다.
     */
    auto Clear() -> void
    {
        // 첫 번째 노드의 주소를 가져온다.
        auto* ptr = m_sentinel_node.next;

        // 센티넬 노드 다음부터 시작하여 센티넬 노드까지 순회하며 메모리 해제
        // 리스트가 비어 있다면 첫 번째 노드의 주소가 센티넬 노드의 주소와
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

public:
    /** @brief 반복자가 가리키는 위치 이전에 새 원소들을 삽입한다.
     *  @param[in] it_pos 삽입할 위치의 이후 노드를 가리키는 반복자. 이 반복자가
     *  가리키는 노드 *이전(Before)*에 새 노드가 생성되어 삽입된다.
     *  @param[in] count 삽입할 원소의 갯수
     *  @param[in] val 삽입할 원소들이 가질 값
     *  @return 삽입된 노드들 중 첫 번째 노드를 가리키는 반복자
     *  @note 호출 후 기존의 반복자들이 무효화되지 않으며, `it_pos`가 역참조
     가능할 필요는 없다.
     *  @exception
     *  - Debug 구성에서 유효하지 않거나 호환되지 않는 반복자로 호출되는 경우
     *    비정상 종료한다.
     *  - Release 구성에서 유효하지 않거나 호환되지 않는 반복자로 호출되는 경우
     *    Undefined Behavior 이다.
     ///@todo Release 구성에서 예외를 던지도록 구현하는 것이 나을 수도 있다.
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

        auto* prev_node_ptr =
            const_cast<Node_D_t*>(it_pos.GetDataPointer())->prev;
        auto* next_node_ptr = prev_node_ptr->next;

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
            Node_D_t* new_node_ptr  = CreateNode(val);
            new_node_ptr_tail->next = new_node_ptr;

            new_node_ptr->prev = new_node_ptr_tail;
            new_node_ptr_tail  = new_node_ptr;
        }

        // 연결된 새 노드들을 이제 리스트의 올바른 위치에 연결한다.
        new_node_ptr_tail->next = next_node_ptr;
        next_node_ptr->prev     = new_node_ptr_tail;

        prev_node_ptr->next     = new_node_ptr_head;
        new_node_ptr_head->prev = prev_node_ptr;

        m_size += count;

        return Iterator_t(this, new_node_ptr_head);
    }

    /** @brief 반복자가 가리키는 위치 이전에 새 원소를 하나 삽입한다.
     *  @param[in] it_pos 삽입할 위치의 이후 노드를 가리키는 반복자. 이 반복자가
     *  가리키는 노드 *이전(Before)*에 새 노드가 생성되어 삽입된다.
     *  @param[in] val 삽입할 원소의 값
     *  @details `InsertBefore(ConstIterator_t, Size_t, const Value_t&)` 를
     *  내부에서 호출한다.
     */
    auto InsertBefore(ConstIterator_t it_pos, const Value_t& val) -> Iterator_t
    {
        return InsertBefore(it_pos, 1, val);
    }

    /** @brief 반복자가 가리키는 위치 이전에 초기화 리스트에 있는 원소들을
     *  삽입한다.
     *  @param[in] it_pos 삽입할 위치의 이후 노드를 가리키는 반복자. 이 반복자가
     *  가리키는 노드 *이전(Before)*에 새 노드가 생성되어 삽입된다.
     *  @param[in] ilist 삽입할 원소들의 초기화 리스트
     *  @return 삽입된 마지막 노드의 다음 위치를 가리키는 반복자
     *  @note 호출 후 기존의 반복자들이 무효화되지 않는다.
     */
    auto InsertBefore(ConstIterator_t                       it_pos,
                      const std::initializer_list<Value_t>& ilist) -> Iterator_t
    {
        for (const auto& e: ilist)
            InsertBefore(it_pos, e);
        return Iterator_t(this, it_pos.GetDataPointer());
    }

    /** @brief 반복자로 주어진 범위의 원소들을 제거한다. 제거되는 범위는
     *  `[it_first, it_last)` 이다.
     *  @param[in] it_fisrt 제거 범위의 시작 위치를 가리키는 반복자
     *  @param[out] it_last 제거 범위의 끝 위치를 가리키는 반복자
     *  @return 제거된 범위의 다음 위치를 가리키는 반복자
     *  @note
     *  - 호출 후 제거 범위에 속한 원소를 가리키는 반복자가 아니라면 무효화되지
     * 않는다.\n
     *  - `it_first == it_last`인 경우 아무 동작도 하지 않고 `it_last`와 동일한
     *    반복자를 반환한다.\n
     *  - 리스트가 비어 있는 경우 주의할 것
     *  @exception
     *  - 올바르지 않은 범위에 대한 반복자 쌍으로 호출되는 경우 Undefined
     * Behavior,
     *  - Debug 구성에서 범위를 나타내는 반복자 쌍이 이 리스트와 호환되지 않는
     *    경우 비정상 종료. Release 구성에서는 Undefined Behavior.
     *  - Debug 구성에서 `it_first`가 역참조 불가능하거나 `it_last`가 유효하지
     *    않으면 비정상 종료. Release 구성에서는 Undefined Behavior.
    /// @todo 삭제 순회 중에 센티넬 노드를 만날 가능성을 완전히 배제할 수 없다는
    점
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

        if (it_first.operator==(it_last))
            return Iterator_t(this, it_last.GetDataPointer());

        /*
        ------------------------------------------------------------------------
         * Before Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        - - range_start(it_first) ↓
         ... ←p[B]n→ ←p[X]n→ ←p[X]n→ ←p[X]n→ ←p[A]n→ ...
                ↑                               ↑
           range_before                    range_after(it_last)
        ------------------------------------------------------------------------
         * After Erase(it_first, it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        - -
         ... ←p[B]n============> <============p[A]n→ ...
                ↑                               ↑
           range_before                    range_after(it_last)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        - - 2 links to be updated:
        ------------------------------------------------------------------------
        */

        // 상수 반복자로부터 노드 포인터를 받아와서 const를 떼버린다!
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

    /** @brief 인자로 전달된 반복자가 가리키는 위치에 있는 원소를 제거한다.
     *  @param[in] it_pos 삭제할 원소의 위치를 가리키는 반복자
     *  @return 삭제된 원소의 다음 위치를 가리키는 반복자
     *  @details
     *  `it_pos`의 다음 반복자로 범위를 만든 후 `Erase(ConstIterator_t,
     *  ConstIterator_t)` 를 내부에서 호출한다.
     *  @exception
     *  - Debug 구성에서 `it_pos`의 다음 반복자를 만들 때, `it_pos`가 더이상
     *  증가시킬 수 없는 반복자라면 비정상 종료한다. Release 구성에서는
     *  Undefined Behavior.
     */
    auto Erase(ConstIterator_t it_pos) -> Iterator_t
    {
        auto it_last = it_pos;
        it_last.operator++();
        return Erase(it_pos, it_last);
    }

    /// @brief 인자로 전달된 값을 리스트의 뒤에 추가한다.
    /// @param[in] val 추가할 원소의 값
    auto PushBack(const Value_t& val) -> void { InsertBefore(CEnd(), val); }

    /// @brief 리스트의 끝에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
    auto PopBack() -> void { Erase(End().operator--()); }

    /// @brief 인자로 전달된 값을 리스트의 맨 앞에 추가한다.
    /// @param[in] val 추가할 원소의 값
    auto PushFront(const Value_t& val) -> void { InsertBefore(Begin(), val); }

    /// @brief 리스트의 맨 앞에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
    auto PopFront() -> void { Erase(CBegin()); }

    auto Resize() -> void;

    auto Swap(List& other) -> void
    {
        auto* this_sn_prev = m_sentinel_node.prev;
        auto* this_sn_next = m_sentinel_node.next;

        auto* temp_this_sn_prev = this_sn_prev;
        auto* temp_this_sn_next = this_sn_next;

        auto* other_sn_prev = &other.m_sentinel_node.prev;
        auto* other_sn_next = &other.m_sentinel_node.next;

        this_sn_prev = other_sn_prev;
        this_sn_next = other_sn_next;

        other_sn_prev = temp_this_sn_prev;
        other_sn_next = temp_this_sn_next;
    }

public:
    template <class... CtorArgs_t>
    auto EmplaceBefore(ConstIterator_t it_pos, CtorArgs_t&&... ctor_args)
        -> Iterator_t
    {
        Node_D_t* new_node_ptr = Allocator_Trait<Allocator_t>::Allocate(1);
        Allocator_Trait<Allocator_t>::Construct(
            new_node_ptr, 1, std::forward<CtorArgs_t>(ctor_args)...);

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

    template <class... CtorArgs_t>
    auto EmplaceFront(CtorArgs_t&&... ctor_args) -> Iterator_t
    {
        return EmplaceBefore(CBegin(), std::forward<CtorArgs_t>(ctor_args)...);
    }

    template <class... CtorArgs_t>
    auto EmplaceBack(CtorArgs_t&&... ctor_args) -> Iterator_t
    {
        return EmplaceBefore(CEnd(), std::forward<CtorArgs_t>(ctor_args)...);
    }

    ///@}

public: // Operations
    /// @{ @name Operations
    auto Remove(const Value_t& value) -> Size_t
    {
        return RemoveIf([&value](const Value_t& val) { return val == value; });
    }

    template <class UnaryPredicate_t>
    auto RemoveIf(UnaryPredicate_t unary_pred) -> Size_t
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

public:
    auto Splice(ConstIterator_t this_it_pos, List& other,
                ConstIterator_t other_it_first, ConstIterator_t other_it_last)
        -> void
    {
        auto* other_range_start_ptr =
            const_cast<Node_D_t*>(other_it_first.GetDataPointer());
        auto* other_range_before_ptr = other_range_start_ptr->prev;
        auto* other_range_after_ptr =
            const_cast<Node_D_t*>(other_it_last.GetDataPointer());
        auto* other_range_end_ptr = other_range_after_ptr->prev;

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

        m_size       += other_range_node_count;
        other.m_size -= other_range_node_count;
    }

    auto Splice(ConstIterator_t this_it_pos, List& other,
                ConstIterator_t other_it_pos) -> void
    {
        Splice(this_it_pos, other, other_it_pos, other.CEnd());
    }

    auto Splice(ConstIterator_t this_it_pos, List& other) -> void
    {
        Splice(this_it_pos, other, other.CBegin(), other.CEnd());
    }

public:
    auto Merge() -> void;

    auto Reverse() -> void
    {
        if (m_size < 2)
            return;

        auto* prev_node_ptr = std::addressof(m_sentinel_node);
        auto* curr_node_ptr = m_sentinel_node.next;
        auto* next_node_ptr = curr_node_ptr->next;

        while (curr_node_ptr != std::addressof(m_sentinel_node))
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

    auto Unique() -> void;
    auto Sort() -> void;
    /// @}

public: // Comparators
        /// @brief 두 리스트가 같은지 비교한다.
        /// @param other 비교할 리스트
        /// @return 두 리스트가 같으면 `true`, 그렇지 않으면 `false`
        /// @note \ref Value_t 가 사용자 정의 자료형인 경우, 연산자 `==`이
        /// 정의되어 있어야 한다.
        /// @details 동등 비교 순서는 다음과 같다.\n
        /// 1. *두 리스트의 크기가 다르면*, 항상 같은 리스트가 아니다.
        /// 2. *두 리스트의 크기가 같고 크기가 0이라면*,항상 같은 리스트이다.
        /// 3. *두 리스트의 크기가 같고 크기가 0이 아니라면*, 두 리스트의 각
        /// 원소를 순회하며 모든 원소가 같은 경우 같은 리스트이고, 그렇지 않으면
        /// 다른 리스트이다.
        /// @test \ref List_Compare_Equality_gtest.cpp 에서 테스트한다.
        /// @test 두 리스트의 크기가 다를 때, 항상 `false` 를 반환하는지 확인
        /// @test 두 리스트의 크기가 같고 크기가 0일 때, 항상 `true`를
        /// 반환하는지 확인
        /// @test 두 리스트의 크기가 같고 크기가 0이 아닐 때, `true` 를 반환하는
        /// 경우
        /// @test 두 리스트의 크기가 같고 크기가 0이 아닐 때, `false` 를
        /// 반환하는 경우
        /// @todo operator== 구현할 것
private: // Members
    /// @brief 리스트의 센티넬 노드이다.
    Node_D_t m_sentinel_node{};
    /// @brief 리스트의 크기이다.
    Size_t   m_size{0};
};

RDS_END

#endif // RDS_LIST_HPP
