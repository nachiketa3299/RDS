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

/// @class List
/// @brief 동적 이중 연결 리스트에 대한 템플릿 클래스
/// @tparam T_t 리스트 내 원소에 대한 자료형
/// @details 리스트의 최전방에 비어 있는 노드를 두어 구현하였다.
template <class T_t>
class List
{
public: // Type Aliases
    /// @brief 리스트 내 원소에 대한 자료형
    using Val_t    = T_t;
    /// @brief 리스트의 크기를 나타내는 자료형
    using Size_t   = std::size_t;
    /// @brief 리스트 내 노드에 대한 자료형
    using Node_D_t = Node_D<Val_t>;

public:
    /// @brief  이 리스트의 반복자에 대한 자료형
    using Iterator      = List_Iterator<List>;
    /// @brief  이 리스트의 상수 반복자에 대한 자료형
    using ConstIterator = List_ConstIterator<List>;

public: // Ctor Dtor
    /// @brief 기본 생성자
    /// @details 리스트의 초기 크기를 0으로, 센티넬 노드의 다음 노드와 이전 노드를 자기
    /// 자신으로 초기화한다.
    List();
    /// @brief 리스트의 초기 크기와 초기값을 지정하는 생성자
    /// @param[in] size 생성할 리스트의 크기
    /// @param[in] init_val 생성할 리스트의 초기값. 모든 원소가 이 값으로 초기화된다.
    List(Size_t size, const Val_t& init_val);
    /// @brief \p std::initializer_list 를 통해 초기화하는 생성자
    /// @param init_list 초기화 리스트
    /// @details 다음처럼 초기화한다.\n
    /// ```cpp
    /// rds::List<int> int_list_empty = {};
    /// rds::List<int> int_list_0 = {1, 2, 3};
    /// rds::List<int> int_list_1 {1, 2, 3, 4};
    /// ```
    List(const std::initializer_list<Val_t>& init_list);
    /// @brief 동적 할당된 리스트의 노드들을 해제하는 소멸자
    /// @details 센티넬 노드 다음부터 시작하여 리스트에 동적으로 할당된 노드들을
    /// 해제한다.
    ~List();

public: // Element Access
    /// @brief 리스트의 첫 번째 원소에 대한 lvalue 참조를 반환한다.
    /// @return 리스트의 첫 번째 원소에 대한 lvalue 참조
    Val_t&          Front();
    /// @brief 리스트의 첫 번째 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 첫 번째 원소에 대한 const-lvalue 참조
    const Val_t&    Front() const;
    /// @brief 리스트의 마지막 원소에 대한 lvalue 참조를 반환한다.
    /// @return 리스트의 마지막 원소에 대한 lvalue 참조
    Val_t&          Back();
    /// @brief 리스트의 마지막 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 마지막 원소에 대한 const-lvalue 참조
    const Val_t&    Back() const;
    /// @brief 리스트의 센티넬 노드에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 센티넬 노드에 대한 const-lvalue 참조
    const Node_D_t& GetSentinel() const;

public: // Iterators
    /// @brief 리스트의 첫 번째 원소를 가리키는 반복자를 반환한다.
    Iterator      Begin();
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator Begin() const;
    /// @brief 리스트의 마지막 원소를 가리키는 반복자를 반환한다.
    Iterator      End();
    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator End() const;
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    ConstIterator CBegin() const;
    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환하낟.
    ConstIterator CEnd() const;

public: // Capacity
    /// @brief 리스트의 크기를 반환한다.
    /// @return 리스트의 크기
    Size_t Size() const;
    /// @brief 리스트의 최대 크기를 반환한다.
    /// @return 리스트의 최대 크기
    Size_t MaxSize() const;
    /// @brief 리스트가 비어있는지 여부를 반환한다.
    /// @return 리스트가 비어있으면 `true`, 그렇지 않으면 `false`이다.
    bool   Empty() const;

public: // Modifiers
    void Clear();

    /// @brief 인자로 전달된 반복자가 가리키는 위치 이전에 새 원소를 삽입한다.
    /// @param[in] it_pos 삽입할 위치를 가리키는 반복자. 이 위치 이전에 새 원소가
    /// 삽입된다.
    /// @param[in] val 삽입할 원소의 값
    void InsertBefore(Iterator it_pos, const Val_t& val);

    /// @brief 인자로 전달된 반복자가 가리키는 위치 이전에 새 원소를 전달받은 갯수만큼
    /// 삽입한다.
    /// @param[in] it_pos 삽입할 위치를 가리키는 반복자. 이 위치 이전에 새 원소가
    /// 삽입된다.
    /// @param[in] val 삽입할 원소의 값
    /// @param[in] count 삽입할 원소의 갯수
    void InsertBefore(Iterator it_pos, Size_t count, const Val_t& val);

    /// @brief 인자로 전달된 반복자가 가리키는 위치에 있는 원소를 제거한다.
    /// @param[in] it_pos 삭제할 위치를 가리키는 반복자. 정확히 이 위치에 있는 원소가
    /// 삭제된다.
    /// @test @ref List_Erase_gtest.cpp 에서 테스트한다.\n
    /// (1) 비어 있는 리스트에서 시작, 끝 반복자를 통해 Erase 메서드를 호출하는 경우
    /// 비정상 종료함을 확인\n 
    /// (2) 비어 있지 않은 리스트에서 센티널 노드 위치의 반복자를 통해 Erase 메서드를 호출하는 경우 비정상 종료함을 확인\n 
    /// (3) 호환되지 않는 리스트의 반복자로 Erase 메서드를 호출하는 경우 비정상 종료
    void Erase(Iterator it_pos);

    /// @brief 인자로 전달된 값을 리스트의 뒤에 추가한다.
    /// @param[in] val 추가할 원소의 값
    void PushBack(const Val_t& val);

    /// @brief 리스트의 끝에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
    void PopBack();

    /// @brief 인자로 전달된 값을 리스트의 맨 앞에 추가한다.
    /// @param[in] val 추가할 원소의 값
    void PushFront(const Val_t& val);

    /// @brief 리스트의 맨 앞에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
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
    /// @brief 리스트의 센티넬 노드이다.
    Node_D_t m_sentinel_node;
    /// @brief 리스트의 크기이다.
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
    InsertBefore(End(), val);
}

template <class T_t>
auto List<T_t>::Erase(Iterator it_pos) -> void
{
    RDS_Assert(it_pos.IsCompatible(*this) && "List is not compatible.");
    RDS_Assert(m_size > 0 && "Cannot erase from empty list."); // this?
    RDS_Assert(it_pos.GetNodePointer() != std::addressof(m_sentinel_node) &&
               "Cannot erase end iterator.");

    auto* erase_node_ptr = it_pos.GetNodePointer();

    auto* prev_node_ptr = erase_node_ptr->prev;
    auto* next_node_ptr = erase_node_ptr->next;

    erase_node_ptr->next = nullptr;
    erase_node_ptr->prev = nullptr;

    prev_node_ptr->next = next_node_ptr;
    next_node_ptr->prev = prev_node_ptr;

    delete erase_node_ptr;
    --m_size;
}

template <class T_t>
void List<T_t>::PopBack()
{
    Erase(End().operator--());
}

template <class T_t>
void List<T_t>::PushFront(const Val_t& val)
{
    InsertBefore(Begin(), val);
}

template <class T_t>
void List<T_t>::PopFront()
{
    Erase(Begin());
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
auto List<T_t>::GetSentinel() const -> const Node_D_t&
{
    return m_sentinel_node;
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
    RDS_Assert(it_pos.IsCompatible(*this) && "List is not compatible.");

    /*
     * >> Before Inserting:
                                it_pos.m_node_ptr
                                    ↓
    ...<-p-[prev_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...

     * >> After Inserting:
                                                it_pos.m_node_ptr
                                                    ↓
    ...<-p-[prev_node]-n-><-p-[new_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...
    */

    auto* new_node_ptr = new Node_D_t(val);

    auto* ins_node_ptr  = it_pos.GetNodePointer();
    auto* prev_node_ptr = ins_node_ptr->prev;

    new_node_ptr->prev = prev_node_ptr;
    new_node_ptr->next = ins_node_ptr;

    prev_node_ptr->next = new_node_ptr;
    ins_node_ptr->prev  = new_node_ptr;

    ++m_size;
}

RDS_END;

#endif // RDS_LIST_HPP
