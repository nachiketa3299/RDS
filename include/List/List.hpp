#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <memory>

#include "Assertion.h"
#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 이중 연결 리스트 템플릿 클래스
/// @tparam T Default-constructible 해야한다.
template <typename T>
class List
{
public:
    using Val_t  = T;
    using Size_t = std::size_t;
    using It_t   = List_Iterator<Val_t>;
    using CIt_t  = List_ConstIterator<Val_t>;

private:
    struct DNode_t
    {
        DNode_t() = default;

        DNode_t(const Val_t& value)
            : val(value)
        {}

        ~DNode_t() = default;

        Val_t    val;
        DNode_t* next{nullptr};
        DNode_t* prev{nullptr};
    };

public:
    List();

public: // Modifiers
    void Clear();
    void Insert();
    void Erase();
    void PushBack(const Val_t& val);
    void PopBack();
    void PushFront(const Val_t& val);
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

public: // Element Access
    Val_t&       Front();
    const Val_t& Front() const;
    Val_t&       Back();
    const Val_t& Back() const;

public: // Iterators
    It_t  Begin();
    CIt_t Begin() const;
    It_t  End();
    CIt_t End() const;
    CIt_t CBegin() const;
    CIt_t CEnd() const;

public: // Capacity
    Size_t Size() const;
    Size_t MaxSize() const;
    bool   Empty() const;

public:
    /// @brief 센티넬 노드
    DNode_t m_sentinel_node;
    Size_t  m_size{0};
};

template <typename T>
inline List<T>::List()
{
    m_sentinel_node.next = addressof(m_sentinel_node);
    m_sentinel_node.prev = addressof(m_sentinel_node);
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
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 &&
               "List 에 아무것도 존재하지 않으므로 Pop 할 수 없습니다.");

    auto& cur_back_node = *(m_sentinel_node.prev);
    auto& new_back_node = *(cur_back_node.prev);

    m_sentinel_node.prev = std::addressof(new_back_node);
    new_back_node.next   = std::addressof(m_sentinel_node);

    delete std::addressof(cur_back_node);

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
    RDS_Assert(static_cast<int>(m_size) - 1 >= 0 &&
               "List 에 아무것도 존재하지 않으므로 Pop 할 수 없습니다.");

    auto& cur_front_node = *(m_sentinel_node.next);
    auto& new_front_node = *(cur_front_node.next);

    m_sentinel_node.next = std::addressof(new_front_node);
    new_front_node.prev  = std::addressof(m_sentinel_node);

    delete std::addressof(cur_front_node);

    --m_size;
}

RDS_END;

#endif // RDS_LIST_HPP
