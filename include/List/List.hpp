#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <memory>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"

RDS_BEGIN

/// @brief Template class of doubly-linked list
/// @tparam T Type of element in list.
/// @todo Examine @p T 's initialization method. What if it does not have default ctor?
/// (deleted default ctor)
template <class T>
class List
{
public:
    using Val_t   = T;
    using Size_t  = std::size_t;
    using DNode_t = Node_D<Val_t>;

public:
    using Iterator      = List_Iterator<List>;
    using ConstIterator = List_ConstIterator<List>;

public:
    List();
    List(Size_t size, const Val_t& init_val);
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
    void Insert();
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
    DNode_t m_sentinel_node;
    /// @brief Size of list
    Size_t  m_size{0};
};

RDS_END

// IMPLEMNTATIONS //

RDS_BEGIN

template <typename T>
inline List<T>::List()
{
    m_sentinel_node.next = std::addressof(m_sentinel_node);
    m_sentinel_node.prev = std::addressof(m_sentinel_node);
}

template <class T>
inline List<T>::List(std::size_t size, const T& init_val)
{
    m_sentinel_node.next = std::addressof(m_sentinel_node);
    m_sentinel_node.prev = std::addressof(m_sentinel_node);

    for (std::size_t i = 0; i < size; ++i)
        PushBack(init_val);
}

template <typename T>
inline List<T>::~List()
{
    auto* c = m_sentinel_node.next;

    // `delete` allocated nodes while iterate all nodes after sentinel node
    while (c != std::addressof(m_sentinel_node))
    {
        auto* ct = c;
        c        = c->next;

        delete ct;
    }
}

template <typename T>
inline void List<T>::PushBack(const T& val)
{
    auto& new_back_node = *(new DNode_t(val));
    auto& cur_back_node = *(m_sentinel_node.prev);

    new_back_node.prev = std::addressof(cur_back_node);
    new_back_node.next = std::addressof(m_sentinel_node);

    cur_back_node.next   = std::addressof(new_back_node);
    m_sentinel_node.prev = std::addressof(new_back_node);

    ++m_size;
}

template <typename T>
inline void List<T>::PopBack()
{
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 && "Cannot pop back empty list.");

    auto* cur_back_node_ptr = m_sentinel_node.prev;
    auto& new_back_node     = *(cur_back_node_ptr->prev);

    m_sentinel_node.prev = std::addressof(new_back_node);
    new_back_node.next   = std::addressof(m_sentinel_node);

    delete cur_back_node_ptr;

    --m_size;
}

template <typename T>
inline void List<T>::PushFront(const Val_t& val)
{
    auto& new_front_node = *(new DNode_t(val));
    auto& cur_front_node = *(m_sentinel_node.next);

    new_front_node.next = std::addressof(cur_front_node);
    new_front_node.prev = std::addressof(m_sentinel_node);

    m_sentinel_node.next = std::addressof(new_front_node);
    cur_front_node.prev  = std::addressof(new_front_node);

    ++m_size;
}

template <typename T>
inline void List<T>::PopFront()
{
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 && "Cannot pop front empty list.");

    auto* cur_front_node_ptr = m_sentinel_node.next;
    auto& new_front_node     = *(cur_front_node_ptr->next);

    m_sentinel_node.next = std::addressof(new_front_node);
    new_front_node.prev  = std::addressof(m_sentinel_node);

    delete cur_front_node_ptr;

    --m_size;
}

template <typename T>
inline T& List<T>::Front()
{
    RDS_Assert(static_cast<int>(m_size) >= 0 && "Cannot access front in empty list.");

    return m_sentinel_node.next->val;
}

template <typename T>
inline const T& List<T>::Front() const
{
    return const_cast<T&>(static_cast<const List&>(*this).Front());
}

template <typename T>
inline T& List<T>::Back()
{
    RDS_Assert(static_cast<int>(m_size) >= 0 && "Cannot access back in empty list.");

    return m_sentinel_node.prev->val;
}

template <typename T>
inline const T& List<T>::Back() const
{
    return const_cast<T&>(static_cast<const List&>(*this).Back());
}

template <typename T>
inline auto List<T>::Begin() -> Iterator
{
    return Iterator(m_sentinel_node.next, this);
}

template <typename T>
inline auto List<T>::Begin() const -> ConstIterator
{
    return ConstIterator(m_sentinel_node.next, this);
}

template <typename T>
inline auto List<T>::End() -> Iterator
{
    return Iterator(m_sentinel_node.prev, this);
}

template <typename T>
inline auto List<T>::End() const -> ConstIterator
{
    return ConstIterator(m_sentinel_node.prev, this);
}

template <typename T>
inline auto List<T>::CBegin() const -> ConstIterator
{
    return Begin();
}

template <typename T>
inline auto List<T>::CEnd() const -> ConstIterator
{
    return End();
}

template <typename T>
inline auto List<T>::Size() const -> Size_t
{
    return m_size;
}

RDS_END;

#endif // RDS_LIST_HPP
