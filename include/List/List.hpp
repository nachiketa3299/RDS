#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"

RDS_BEGIN

/// @brief 동적 이중 연결 리스트에 대한 템플릿 클래스
/// @tparam T_t 리스트 내 원소에 대한 자료형
template <class T_t>
class List
{
    friend List_ConstIterator<T_t>;

public: // Type Aliases
    using Val_t    = T_t;
    using Size_t   = std::size_t;
    using Node_D_t = Node_D<Val_t>;

public:
    using Iterator      = List_Iterator<List>;
    using ConstIterator = List_ConstIterator<List>;

public: // Ctor Dtor
    List();
    List(Size_t size, const Val_t& init_val);
    List(const std::initializer_list<Val_t>& init_list);
    ~List();

public: // Element Access
    Val_t&       Front();
    const Val_t& Front() const;
    Val_t&       Back();
    const Val_t& Back() const;

public: // Iterators
    Iterator      Begin();
    ConstIterator Begin() const;

    Iterator      End();
    ConstIterator End() const;

    ConstIterator CBegin() const;
    ConstIterator CEnd() const;

public: // Capacity
    Size_t Size() const;
    Size_t MaxSize() const;
    bool   Empty() const;

public: // Modifiers
    void Clear();

    /// @brief 반복자 @p it_pos 가 가리키는 위치에 @p val 을 삽입한다.
    void InsertBefore(Iterator it_pos, const Val_t& val);

    /// @brief 반복자 @p it_pos 가 가리키는 위치에 @p val 을 @p count 개 삽입한다.
    void InsertBefore(Iterator it_pos, Size_t count, const Val_t& val);

    void Erase();

    /// @brief Push @p val in back of this list.
    void PushBack(const Val_t& val);

    /// @brief Pop @p val from back of this list.
    /// @warning Do not pop from empty list.
    void PopBack();

    /// @brief Push @p val in front of this list.
    void PushFront(const Val_t& val);

    /// @brief Pop @p val from front of this list.
    /// @warning Do not pop from empty list.
    void PopFront();

    void Resize();
    void Swap();

public: // Operations
    void Merge();
    void Splice();
    void Remove();
    void RemoveIf();
    void Reverse();
    void Unique();
    void Sort();

private:
    /// @brief Sentinel node as ghost head node.
    Node_D_t m_sentinel_node;
    /// @brief Size of list
    Size_t   m_size{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t>
List<T_t>::List()
{
    m_sentinel_node.next = std::addressof(m_sentinel_node);
    m_sentinel_node.prev = std::addressof(m_sentinel_node);
}

template <class T_t>
List<T_t>::List(std::size_t size, const T_t& init_val)
{
    m_sentinel_node.next = std::addressof(m_sentinel_node);
    m_sentinel_node.prev = std::addressof(m_sentinel_node);

    for (std::size_t i = 0; i < size; ++i)
        PushBack(init_val);
}

template <class T_t>
List<T_t>::List(const std::initializer_list<T_t>& init_list)
{
    m_sentinel_node.next = std::addressof(m_sentinel_node);
    m_sentinel_node.prev = std::addressof(m_sentinel_node);

    for (const auto& e: init_list)
        PushBack(e);
}

template <class T_t>
List<T_t>::~List()
{
    auto* ptr = m_sentinel_node.next;
    // 센티넬 노드 다음부터 시작하여 센티넬 노드까지 순회하며 메모리 해제
    while (ptr != std::addressof(m_sentinel_node))
    {
        auto* to_delete = ptr;
        ptr             = ptr->next;

        delete to_delete;
    }
}

template <class T_t>
void List<T_t>::PushBack(const T_t& val)
{
    auto& new_back_node = *(new Node_D_t(val));
    auto& cur_back_node = *(m_sentinel_node.prev);

    new_back_node.prev = std::addressof(cur_back_node);
    new_back_node.next = std::addressof(m_sentinel_node);

    cur_back_node.next   = std::addressof(new_back_node);
    m_sentinel_node.prev = std::addressof(new_back_node);

    ++m_size;
}

template <class T_t>
void List<T_t>::PopBack()
{
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 && "Cannot pop back empty list.");

    auto* cur_back_node_ptr = m_sentinel_node.prev;
    auto& new_back_node     = *(cur_back_node_ptr->prev);

    m_sentinel_node.prev = std::addressof(new_back_node);
    new_back_node.next   = std::addressof(m_sentinel_node);

    delete cur_back_node_ptr;

    --m_size;
}

template <class T_t>
void List<T_t>::PushFront(const Val_t& val)
{
    auto& new_front_node = *(new Node_D_t(val));
    auto& cur_front_node = *(m_sentinel_node.next);

    new_front_node.next = std::addressof(cur_front_node);
    new_front_node.prev = std::addressof(m_sentinel_node);

    m_sentinel_node.next = std::addressof(new_front_node);
    cur_front_node.prev  = std::addressof(new_front_node);

    ++m_size;
}

template <class T_t>
void List<T_t>::PopFront()
{
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 && "Cannot pop front empty list.");

    auto* cur_front_node_ptr = m_sentinel_node.next;
    auto& new_front_node     = *(cur_front_node_ptr->next);

    m_sentinel_node.next = std::addressof(new_front_node);
    new_front_node.prev  = std::addressof(m_sentinel_node);

    delete cur_front_node_ptr;

    --m_size;
}

template <class T_t>
auto List<T_t>::Front() -> T_t&
{
    return const_cast<T_t&>(static_cast<const List&>(*this).Front());
}

template <class T_t>
auto List<T_t>::Front() const -> const T_t&
{
    RDS_Assert(static_cast<int>(m_size) > 0 && "Cannot access front in empty list.");
    return m_sentinel_node.next->val;
}

template <class T_t>
auto List<T_t>::Back() -> T_t&
{
    return const_cast<T_t&>(static_cast<const List&>(*this).Back());
}

template <class T_t>
auto List<T_t>::Back() const -> const T_t&
{
    RDS_Assert(static_cast<int>(m_size) > 0 && "Cannot access back in empty list.");
    return m_sentinel_node.prev->val;
}

template <class T_t>
auto List<T_t>::Begin() -> Iterator
{
    return Iterator(this, m_sentinel_node.next);
}

template <class T_t>
auto List<T_t>::Begin() const -> ConstIterator
{
    return ConstIterator(this, m_sentinel_node.next);
}

template <class T_t>
auto List<T_t>::End() -> Iterator
{
    return Iterator(this, std::addressof(m_sentinel_node));
}

template <class T_t>
auto List<T_t>::End() const -> ConstIterator
{
    return ConstIterator(this, std::addressof(m_sentinel_node));
}

template <class T_t>
auto List<T_t>::CBegin() const -> ConstIterator
{
    return Begin();
}

template <class T_t>
auto List<T_t>::CEnd() const -> ConstIterator
{
    return End();
}

template <class T_t>
auto List<T_t>::Size() const -> Size_t
{
    return m_size;
}

template <class T_t>
auto List<T_t>::InsertBefore(Iterator it_pos, const Val_t& val) -> void
{
    RDS_Assert(it_pos.m_proxy == this && "List is not compatible.");

    /*
     * >> Before Inserting:
                                it_pos.node_ptr
                                    ↓
    ...<-p-[prev_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...

     * >> After Inserting:
                                                it_pos.node_ptr
                                                    ↓
    ...<-p-[prev_node]-n-><-p-[new_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...
    */

    auto* new_node_ptr = new Node_D_t(val);

    /// @todo List_ConstIterator 를 friend 선언하고 멤버에 직접 접근하는게 맞나?
    auto* ins_node_ptr  = it_pos.node_ptr;
    auto* prev_node_ptr = ins_node_ptr->prev;

    new_node_ptr->prev = prev_node_ptr;
    new_node_ptr->next = ins_node_ptr;

    prev_node_ptr->next = new_node_ptr;
    ins_node_ptr->prev  = new_node_ptr;

    ++m_size;
}

RDS_END;

#endif // RDS_LIST_HPP
