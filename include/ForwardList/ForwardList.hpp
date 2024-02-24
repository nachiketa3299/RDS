/// @file ForwardList.hpp

#ifndef RDS_FORWARDLIST_HPP
#define RDS_FORWARDLIST_HPP

#include <initializer_list>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "Allocator_Trait.hpp"
#include "Mallocator.hpp"
#include "Node_S.hpp"

#include "ForwardList_ConstIterator.hpp"
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

RDS_BEGIN

template <class T_t, class Alloc_t = Mallocator<Node_S<T_t>>>
class ForwardList
{
public: // Type Aliases
    using Allocator_t = Alloc_t;

public:
    using Value_t  = T_t;
    using Size_t   = std::size_t;
    using Node_S_t = Node_S<Value_t>;

public: // Iterator Type Aliases
    using ConstIterator_t = ForwardList_ConstIterator<ForwardList<Value_t>>;
    using Iterator_t      = ForwardList_Iterator<ForwardList<Value_t>>;

public: // Custom Ctors
    ForwardList();
    ForwardList(Size_t size, const Value_t& init_val);
    ForwardList(const std::initializer_list<Value_t>& init_list);
    auto operator=(const ForwardList& other) -> ForwardList&;
    auto operator=(ForwardList&& other) -> ForwardList&;
    auto operator=(std::initializer_list<Value_t>& init_list) -> ForwardList&;

public: // Custom Dtor
    ~ForwardList();

public: // Node
    auto CreateNode(const Value_t& value) const -> Node_S_t*;
    auto DeleteNode(const Node_S_t* node) const -> void;

public: // Access
    auto Front() const -> const Value_t&;
    auto Front() -> Value_t&;

public: // Iterators
    auto BeforeBegin() const -> ConstIterator_t;
    auto BeforeBegin() -> Iterator_t;
    auto Begin() const -> ConstIterator_t;
    auto Begin() -> Iterator_t;
    auto End() const -> ConstIterator_t;
    auto End() -> Iterator_t;

public: // Const Iterators
    auto CBeforeBegin() const -> ConstIterator_t;
    auto CBegin() const -> ConstIterator_t;
    auto CEnd() const -> ConstIterator_t;

public: // Modifiers
    auto Assign();
    auto InsertAfter(ConstIterator_t it_pos, const Value_t& value) -> void;
    auto PushFront(const Value_t& value) -> void;
    auto PopFront() -> void;

public:
    template <class... CtorArgs_t>
    auto EmplaceFront(CtorArgs_t&&... ctor_args) -> Iterator_t;
    template <class... CtorArgs_t>
    auto EmplaceAfter(ConstIterator_t it_pos, CtorArgs_t&&... ctor_args)
        -> Iterator_t;

public:
    auto EraseAfter(ConstIterator_t it_first, ConstIterator_t it_last)
        -> Iterator_t;
    auto EraseAfter(ConstIterator_t it_pos) -> Iterator_t;
    auto Swap();
    auto Resize();

public: // Operations
    template <class UnaryPredicate_t>
    auto RemoveIf(UnaryPredicate_t unary_pred) -> Size_t;
    auto Remove(const Value_t& value) -> Size_t;

public:
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other,
                     ConstIterator_t other_it_first,
                     ConstIterator_t other_it_last) -> void;
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other,
                     ConstIterator_t other_it_pos) -> void;
    auto SpliceAfter(ConstIterator_t this_it_pos, ForwardList& other) -> void;

public:
    auto Unique();
    auto Merge();
    auto Sort();
    auto Reverse() -> void;

public: // Capacity
    auto Size() const -> Size_t;
    auto MaxSize() const -> Size_t;
    auto Empty() const -> bool;

public: // Helpers
    auto GetSentinePointer() const -> const Node_S_t*;

private:
    Node_S_t m_sentinel_node;
    Size_t   m_size{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t, class Alloc_t>
inline ForwardList<T_t, Alloc_t>::ForwardList()
    : m_sentinel_node(std::address_of(m_sentinel_node))
{}

template <class T_t, class Alloc_t>
inline ForwardList<T_t, Alloc_t>::ForwardList(Size_t         size,
                                              const Value_t& init_val)
    : m_sentinel_node(std::address_of(m_sentinel_node))
{
    for (Size_t i = 0; i < size; ++i)
    {
        InsertAfter(CBeforeBegin(), init_val);
    }
}

template <class T_t, class Alloc_t>
inline ForwardList<T_t, Alloc_t>::ForwardList(
    const std::initializer_list<Value_t>& init_list)
{}

template <class T_t, class Alloc_t>
inline ForwardList<T_t, Alloc_t>::~ForwardList()
{
    auto* ptr = m_sentinel_node.next;
    while (ptr != std::address_of(m_sentinel_node))
    {
        auto* to_delete = ptr;
        ptr             = ptr->next;

        DeleteNode(to_delete);
    }
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::CreateNode(const Value_t& value) const
    -> Node_S_t*
{
    Node_S_t* ptr = Allocator_Trait<Allocator_t>::Allocate(1);
    Allocator_Trait<Allocator_t>::Construct(ptr, 1, value);
    return ptr;
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::DeleteNode(const Node_S_t* node) const
    -> void
{
    Allocator_Trait<Allocator_t>::Deconstruct(node, 1);
    Allocator_Trait<Allocator_t>::Deallocate(node);
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Front() const -> const Value_t&
{
    RDS_Assert(static_cast<int>(m_size) > 0 &&
               "Cannot access front of empty list.");
    return m_sentinel_node.next->val;
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Front() -> Value_t&
{
    return const_cast<T_t&>(static_cast<const ForwardList&>(*this).Front());
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::BeforeBegin() const -> ConstIterator_t
{
    return ConstIterator_t(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::BeforeBegin() -> Iterator_t
{
    return Iterator_t(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Begin() const -> ConstIterator_t
{
    return ConstIterator_t(this, m_sentinel_node.next);
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Begin() -> Iterator_t
{
    return Iterator_t(this, std::addressof(m_sentinel_node.next));
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::End() const -> ConstIterator_t
{
    return ConstIterator_t(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::End() -> Iterator_t
{
    return Iterator_t(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::CBeforeBegin() const -> ConstIterator_t
{
    return BeforeBegin();
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::CBegin() const -> ConstIterator_t
{
    return Begin();
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::CEnd() const -> ConstIterator_t
{
    return End();
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Reverse() -> void
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

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Size() const -> Size_t
{
    return m_size;
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Empty() const -> bool
{
    return m_size == 0;
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::GetSentinePointer() const
    -> const Node_S_t*
{
    return std::addressof(m_sentinel_node);
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::PushFront(const Value_t& value) -> void
{
    InsertAfter(CBeforeBegin(), value);
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::PopFront() -> void
{
    EraseAfter(CBeforeBegin());
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::InsertAfter(ConstIterator_t it_pos,
                                                   const Value_t& value) -> void
{
    RDS_Assert(it_pos.IsCompatible(*this) && "ForwardList is not compatible.");

    /*
    ----------------------------------------------------------------------------
     * Before Insert(it_pos, value)
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                             it_pos.m_data_ptr
                               ↓
     ... n→ [prev_node]n→ [ins_node]n→ [next_node]n→ ...
    ----------------------------------------------------------------------------
     * After Insert(it_pos, value)
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                             it_pos.m_data_ptr
                               ↓
     ... n→ [prev_node]n→ [ins_node]n=>[new_node]n=>[next_node]n→ ...
    ----------------------------------------------------------------------------
     * 2 links to be updated:
    */

    Node_S_t* new_node = CreateNode(value);

    auto* ins_node_ptr  = const_cast<Node_S_t*>(it_pos.GetDataPointer());
    auto* next_node_ptr = ins_node_ptr->next;

    new_node->next = next_node_ptr;
    ins_node->next = new_node;

    ++m_size;
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::EraseAfter(ConstIterator_t it_first,
                                                  ConstIterator_t it_last)
    -> Iterator_t
{
    /*
     * (it_first, it_last) 범위에 있는 노드들을 삭제한다.
    ----------------------------------------------------------------------------
     * Before Erase(it_first, it_last)
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
           range_start(it_first->next)
                ↓
     ... [B]n→ [X]n→ [X]n→ [X]n→ [A]n→ ...
          ↑                       ↑
     range_before(it_first)  range_after(it_last)
    ----------------------------------------------------------------------------
     * After Erase(it_first, it_last)
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     ... [B]n==================> [A]n→ ...
          ↑                       ↑
     range_before(it_first)  range_after(it_last)
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       1 link to be updated:
    ----------------------------------------------------------------------------
     */
    RDS_Assert(it_first.IsCompatible(*this) &&
               "ForwardList is not compatible with given iterator.");
    RDS_Assert(it_last.IsCompatible(*this) &&
               "ForwardList is not compatible with given iterator.");
    RDS_Assert(it_last.IsValid() && "End of range is not valid.");

    // 상수 반복자로부터 노드 포인터를 받아와서 const를 떼버린다!
    auto* range_before_ptr = const_cast<Node_S_t*>(it_first.GetDataPointer());
    auto* range_start_ptr  = range_before->next;

    auto* range_after_ptr = const_cast<Node_S_t*>(it_last.GetDataPointer());

    // 삭제 범위 전후 노드에 대한 재연결
    range_before_ptr->next = range_after_ptr;

    // 삭제 범위를 순회하며 노드 삭제
    /// @todo 순회 중에 End() 노드를 만나는 경우 비정상 종료하도록 수정하는 것이
    /// 어떨까?
    /// @todo Edge case 에 대해서 조금 더 생각해 보아야 한다.
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

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::EraseAfter(ConstIterator_t it_pos)
    -> Iterator_t
{
    auto it_last = it_pos;
    it_last.operator++();
    it_last.operator++();
    return Erase(it_pos, it_last);
}

template <class T_t, class Alloc_t>
template <class... CtorArgs_t>
inline auto ForwardList<T_t, Alloc_t>::EmplaceFront(CtorArgs_t&&... ctor_args)
    -> Iterator_t
{
    Node_S_t* new_node_ptr = Allocator_Trait<Allocator_t>::Allocate(1);
    Allocator_Trait<Allocator_t>::Construct(
        new_node_ptr, 1, std::forward<CtorArgs_t>(ctor_args)...);

    auto* prev_node_ptr = std::addressof(m_sentinel_node);
    auto* next_node_ptr = m_sentinel_node.next;

    prev_node_ptr->next = new_node_ptr;
    new_node_ptr->next  = next_node_ptr;

    ++m_size;

    return Iterator_t(this, new_node_ptr);
}

template <class T_t, class Alloc_t>
template <class... CtorArgs_t>
inline auto ForwardList<T_t, Alloc_t>::EmplaceAfter(ConstIterator_t it_pos,
                                                    CtorArgs_t&&... ctor_args)
    -> Iterator_t
{
    auto it_last = it_pos;

    it_last.operator++();
    it_last.operator++();

    Node_S_t* new_node_ptr = Allocator_Trait<Allocator_t>::Allocate(1);
    Allocator_Trait<Allocator_t>::Construct(
        new_node_ptr, 1, std::forward<CtorArgs_t>(ctor_args)...);

    auto* prev_node_ptr = const_cast<Node_S_t*>(it_pos.GetDataPointer());
    auto* next_node_ptr = const_cast<Node_S_t*>(it_last.GetDataPointer());

    prev_node_ptr->next = new_node_ptr;
    new_node_ptr->next  = next_node_ptr;

    ++m_size;

    return Iterator_t(this, new_node_ptr);
}

template <class T_t, class Alloc_t>
template <class UnaryPredicate_t>
inline auto ForwardList<T_t, Alloc_t>::RemoveIf(UnaryPredicate_t unary_pred)
    -> Size_t
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

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::Remove(const Value_t& value) -> Size_t
{
    return RemoveIf([&value](const Value_t& val) { return val == value; });
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::SpliceAfter(
    ConstIterator_t this_it_pos, ForwardList& other,
    ConstIterator_t other_it_first, ConstIterator_t other_it_last) -> void
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

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::SpliceAfter(ConstIterator_t this_it_pos,
                                                   ForwardList&    other,
                                                   ConstIterator_t other_it_pos)
    -> void
{
    SpliceAfter(this_it_pos, other, other_it_pos, other.CEnd());
}

template <class T_t, class Alloc_t>
inline auto ForwardList<T_t, Alloc_t>::SpliceAfter(ConstIterator_t this_it_pos,
                                                   ForwardList& other) -> void
{
    SpliceAfter(this_it_pos, other, other.CBeforeBegin(), other.CEnd());
}

RDS_END

#endif // RDS_FORWARDLIST_HPP
