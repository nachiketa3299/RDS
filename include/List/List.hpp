/// @file List.hpp

#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

#include "Allocator_Trait.hpp"
#include "Mallocator.hpp"

#include "List_ConstIterator.hpp"
#include "List_Iterator.hpp"
#include "Node_D.hpp"

RDS_BEGIN

/// @brief 동적 이중 연결 리스트에 대한 템플릿 클래스
/// @tparam T_t 리스트 내 원소에 대한 자료형
/// @details 리스트의 최전방에 비어 있는 노드를 두어 구현하였다.
template <class T_t, class Alloc_t = Mallocator<Node_D<T_t>>>
class List
{
public: // Type Aliases
    /// @brief 리스트 내 원소에 대한 자료형
    using Val_t    = T_t;
    /// @brief 리스트의 크기를 나타내는 자료형
    using Size_t   = std::size_t;
    /// @brief 리스트 내 노드에 대한 자료형
    using Node_D_t = Node_D<Val_t>;

public: // Iterator Type Aliases
    /// @brief  이 리스트의 반복자에 대한 자료형
    using Iterator      = List_Iterator<List>;
    /// @brief  이 리스트의 상수 반복자에 대한 자료형
    using ConstIterator = List_ConstIterator<List>;

public: // Custom Ctors
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
    List(const std::initializer_list<Val_t>& init_list);

public: // Custom Dtor
    /// @brief 동적 할당된 리스트의 노드들을 해제하는 소멸자
    /// @details 센티넬 노드 다음부터 시작하여 리스트에 동적으로 할당된 노드들을
    /// 해제한다.
    ~List();

public:
    /// @brief 새로운 노드위한 메모리를 할당하고, 그 위치에 노드를 생성한 후 주소를
    /// 반환한다.
    /// @param val 노드에 들어갈 값
    /// @return 동적으로 생성된 노드의 주소
    auto CreateNode(const Val_t& val) const -> Node_D_t*;
    /// @brief 동적으로 할당된 노드의 주소를 받아 그 노드를 소멸시키고 할당된 메모리를
    /// 해제한다.
    /// @param node 소멸시킬 노드의 주소
    auto DeleteNode(const Node_D_t* node) const -> void;

public: // Element Access - Front & Back
    /// @brief 리스트의 첫 번째 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 첫 번째 원소에 대한 const-lvalue 참조
    auto Front() const -> const Val_t&;
    /// @brief 리스트의 첫 번째 원소에 대한 lvalue 참조를 반환한다.
    /// @return 리스트의 첫 번째 원소에 대한 lvalue 참조
    auto Front() -> Val_t&;
    /// @brief 리스트의 마지막 원소에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 마지막 원소에 대한 const-lvalue 참조
    auto Back() const -> const Val_t&;
    /// @brief 리스트의 마지막 원소에 대한 lvalue 참조를 반환한다.
    /// @return 리스트의 마지막 원소에 대한 lvalue 참조
    auto Back() -> Val_t&;

public: // Element Access - Special
    /// @brief 리스트의 센티넬 노드에 대한 const-lvalue 참조를 반환한다.
    /// @return 리스트의 센티넬 노드에 대한 const-lvalue 참조
    auto GetSentinelPointer() const -> const Node_D_t*;

public: // Iterators
    /// @brief 리스트의 첫 번째 원소를 가리키는 반복자를 반환한다.
    auto Begin() -> Iterator;
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    auto Begin() const -> ConstIterator;
    /// @brief 리스트의 마지막 원소를 가리키는 반복자를 반환한다.
    auto End() -> Iterator;
    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환한다.
    auto End() const -> ConstIterator;

public: // Const Iterators
    /// @brief 리스트의 첫 번째 원소를 가리키는 상수 반복자를 반환한다.
    auto CBegin() const -> ConstIterator;
    /// @brief 리스트의 마지막 원소를 가리키는 상수 반복자를 반환하낟.
    auto CEnd() const -> ConstIterator;

public: // Capacity
    /// @brief 리스트의 크기를 반환한다.
    /// @return 리스트의 크기
    auto Size() const -> Size_t;
    /// @brief 리스트의 최대 크기를 반환한다.
    /// @return 리스트의 최대 크기
    auto MaxSize() const -> Size_t;
    /// @brief 리스트가 비어있는지 여부를 반환한다.
    /// @return 리스트가 비어있으면 `true`, 그렇지 않으면 `false`이다.
    auto Empty() const -> bool;

public: // Modifiers
    auto Resize() -> void;
    auto Swap() -> void;
    auto Clear() -> void;
    /// @brief 인자로 전달된 반복자가 가리키는 위치 이전에 새 원소를 삽입한다.
    /// @param[in] it_pos 삽입할 위치를 가리키는 반복자. 이 위치 이전에 새 원소가
    /// 삽입된다.
    /// @param[in] val 삽입할 원소의 값
    auto InsertBefore(ConstIterator it_pos, const Val_t& val) -> void;
    /// @brief 인자로 전달된 반복자가 가리키는 위치 이전에 새 원소를 전달받은 갯수만큼
    /// 삽입한다.
    /// @param[in] it_pos 삽입할 위치를 가리키는 반복자. 이 위치 이전에 새 원소가
    /// 삽입된다.
    /// @param[in] val 삽입할 원소의 값
    /// @param[in] count 삽입할 원소의 갯수
    auto InsertBefore(ConstIterator it_pos, Size_t count, const Val_t& val) -> void;
    /// @brief 인자로 전달된 반복자가 가리키는 위치에 있는 원소를 제거한다.
    /// @param[in] it_pos 삭제할 위치를 가리키는 반복자. 정확히 이 위치에 있는 원소가
    /// 삭제된다.
    /// @test @ref List_Erase_gtest.cpp 에서 테스트한다.\n
    /// (1) 비어 있는 리스트에서 시작, 끝 반복자를 통해 Erase 메서드를 호출하는 경우
    /// 비정상 종료함을 확인\n
    /// (2) 비어 있지 않은 리스트에서 센티널 노드 위치의 반복자를 통해 Erase 메서드를
    /// 호출하는 경우 비정상 종료함을 확인\n (3) 호환되지 않는 리스트의 반복자로 Erase
    /// 메서드를 호출하는 경우 비정상 종료
    /// @todo 반복자를 리턴하도록 해야함
    /// @todo ConstIterator도 받을 수 있음
    /// @todo 시작과 끝 반복자를 받는 버전도 작성해야 함
    auto Erase(ConstIterator it_pos) -> Iterator;
    /// @brief 반복자로 주어진 범위의 원소들을 제거한다. 제거되는 범위는 `[it_first,
    /// it_last)` 이다.
    /// @param it_first 제거할 원소들의 시작 위치를 가리키는 반복자
    /// @param it_last 제거할 원소들의 끝 위치를 가리키는 반복자
    /// @return 제거된 범위의 다음 위치를 가리키는 반복자
    /// @warning `it_first` 와 `it_last`가 유효하지 않은 범위라면, Undefined Behavior
    /// 이다.\n 예를 들어, `it_last`가 `it_first` 보다 이전을 가리키는 경우가 그렇다.
    /// @details
    /// - `it_first` 는 역참조 가능해야 하고, `it_last`는 유효해야 한다. 그렇지 않으면
    /// 비정상 종료한다.\n
    /// - `it_first`와 `it_last`가 리스트와 호환되지 않는 경우 비정상 종료한다.\n
    /// - `it_first`와 `it_last`가 같은 경우, 아무런 동작을 하지 않고 `it_last`를
    /// 반환한다.
    auto Erase(ConstIterator it_first, ConstIterator it_last) -> Iterator;
    /// @brief 인자로 전달된 값을 리스트의 뒤에 추가한다.
    /// @param[in] val 추가할 원소의 값
    auto PushBack(const Val_t& val) -> void;
    /// @brief 리스트의 끝에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
    auto PopBack() -> void;
    /// @brief 인자로 전달된 값을 리스트의 맨 앞에 추가한다.
    /// @param[in] val 추가할 원소의 값
    auto PushFront(const Val_t& val) -> void;
    /// @brief 리스트의 맨 앞에서 원소를 제거한다.
    /// @warning 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료한다.
    /// @test 비어 있는 리스트에서 이 연산을 수행할 시 비정상 종료하는지 확인.
    auto PopFront() -> void;

public: // Operations
    auto Merge() -> void;
    auto Splice() -> void;
    auto Remove() -> void;
    auto RemoveIf() -> void;
    auto Reverse() -> void;
    auto Unique() -> void;
    auto Sort() -> void;

public: // Comparators
    /// @brief 두 리스트가 같은지 비교한다.
    /// @param other 비교할 리스트
    /// @return 두 리스트가 같으면 `true`, 그렇지 않으면 `false`
    /// @note \ref Val_t 가 사용자 정의 자료형인 경우, 연산자 `==`이 정의되어 있어야
    /// 한다.
    /// @details 동등 비교 순서는 다음과 같다.\n
    /// 1. *두 리스트의 크기가 다르면*, 항상 같은 리스트가 아니다.
    /// 2. *두 리스트의 크기가 같고 크기가 0이라면*,항상 같은 리스트이다.
    /// 3. *두 리스트의 크기가 같고 크기가 0이 아니라면*, 두 리스트의 각 원소를 순회하며
    /// 모든 원소가 같은 경우 같은 리스트이고, 그렇지 않으면 다른 리스트이다.
    /// @test \ref List_Compare_Equality_gtest.cpp 에서 테스트한다.
    /// @test 두 리스트의 크기가 다를 때, 항상 `false` 를 반환하는지 확인
    /// @test 두 리스트의 크기가 같고 크기가 0일 때, 항상 `true`를 반환하는지 확인
    /// @test 두 리스트의 크기가 같고 크기가 0이 아닐 때, `true` 를 반환하는 경우
    /// @test 두 리스트의 크기가 같고 크기가 0이 아닐 때, `false` 를 반환하는 경우
    template <class Other_Alloc_t>
    auto operator==(const List<Val_t, Other_Alloc_t>& other) const -> bool;

private: // Members
    /// @brief 리스트의 센티넬 노드이다.
    Node_D_t m_sentinel_node;
    /// @brief 리스트의 크기이다.
    Size_t   m_size{0};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t, class Alloc_t>
List<T_t, Alloc_t>::List()
    : m_sentinel_node(std::addressof(m_sentinel_node), std::addressof(m_sentinel_node))
{}

template <class T_t, class Alloc_t>
List<T_t, Alloc_t>::List(std::size_t size, const T_t& init_val)
    : m_sentinel_node(std::addressof(m_sentinel_node), std::addressof(m_sentinel_node))
{
    for (std::size_t i = 0; i < size; ++i)
        PushBack(init_val);
}

template <class T_t, class Alloc_t>
List<T_t, Alloc_t>::List(const std::initializer_list<T_t>& init_list)
    : m_sentinel_node(std::addressof(m_sentinel_node), std::addressof(m_sentinel_node))
{
    for (const auto& e: init_list)
        PushBack(e);
}

template <class T_t, class Alloc_t>
List<T_t, Alloc_t>::~List()
{
    auto* ptr = m_sentinel_node.next;
    // 센티넬 노드 다음부터 시작하여 센티넬 노드까지 순회하며 메모리 해제
    while (ptr != std::addressof(m_sentinel_node))
    {
        auto* to_delete = ptr;
        ptr             = ptr->next;

        DeleteNode(to_delete);
    }
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::CreateNode(const Val_t& val) const -> Node_D_t*
{
    Node_D_t* ptr = Allocator_Trait<Alloc_t>::Allocate(1);
    Allocator_Trait<Alloc_t>::Construct(ptr, 1, val);

    return ptr;
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::DeleteNode(const Node_D_t* node) const -> void
{
    Allocator_Trait<Alloc_t>::Deconstruct(node, 1);
    Allocator_Trait<Alloc_t>::Deallocate(node);
}

template <class T_t, class Alloc_t>
void List<T_t, Alloc_t>::PushBack(const T_t& val)
{
    InsertBefore(End(), val);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Erase(ConstIterator it_pos) -> Iterator
{
    auto it_last = it_pos;
    it_last.operator++();
    return Erase(it_pos, it_last);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Erase(ConstIterator it_first, ConstIterator it_last)
    -> Iterator
{
    RDS_Assert(it_first.IsDereferencible() && "Start of range is not dereferencible.");
    RDS_Assert(it_last.IsValid() && "End of range is not valid.");
    RDS_Assert(it_first.IsCompatible(*this) &&
               "List is not compatible with given iterator.");
    RDS_Assert(it_last.IsCompatible(*this) &&
               "List is not compatible with given iterator.");

    if (it_first.operator==(it_last))
        return Iterator(this, it_last.GetDataPointer());

    /*
    >> === Before Erase:
              range_start(it_first)
                   ↓
     ...<p[B]n> <p[X]n> <p[X]n> <p[X]n> <p[A]n>...
           ↑                               ↑
      range_before                    range_after(it_last)

    >> === After Erase:

     ...<p[B]------------n>  <p-----------[A]n>...
           ↑                               ↑
      range_before           [return] range_after(it_last)
    */

    // ConsIterator 로부터 노드 포인터를 받아와서 Const 를 떼버린다!
    auto* range_start  = const_cast<Node_D_t*>(it_first.GetDataPointer());
    auto* range_before = range_start->prev;

    auto* range_after = const_cast<Node_D_t*>(it_last.GetDataPointer());

    // 삭제 범위 전후 노드에 대한 재연결
    range_before->next = range_after;
    range_after->prev  = range_before;

    // 삭제 범위를 순회하며 노드 삭제
    const auto* p = range_start;
    while (p != range_after)
    {
        const auto* to_delete = p;
        p                     = p->next;

        DeleteNode(to_delete);

        --m_size;
    }

    return Iterator(this, range_after);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::PopBack() -> void
{
    Erase(End().operator--());
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::PushFront(const Val_t& val) -> void
{
    InsertBefore(Begin(), val);
}

template <class T_t, class Alloc_t>
void List<T_t, Alloc_t>::PopFront()
{
    Erase(Begin());
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Front() -> T_t&
{
    return const_cast<T_t&>(static_cast<const List&>(*this).Front());
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Front() const -> const T_t&
{
    RDS_Assert(static_cast<int>(m_size) > 0 && "Cannot access front in empty list.");
    return m_sentinel_node.next->val;
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Back() -> T_t&
{
    return const_cast<T_t&>(static_cast<const List&>(*this).Back());
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Back() const -> const T_t&
{
    RDS_Assert(static_cast<int>(m_size) > 0 && "Cannot access back in empty list.");
    return m_sentinel_node.prev->val;
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::GetSentinelPointer() const -> const Node_D_t*
{
    return std::addressof(m_sentinel_node);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Begin() -> Iterator
{
    return Iterator(this, m_sentinel_node.next);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Begin() const -> ConstIterator
{
    return ConstIterator(this, m_sentinel_node.next);
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::End() -> Iterator
{
    return Iterator(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::End() const -> ConstIterator
{
    return ConstIterator(this, std::addressof(m_sentinel_node));
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::CBegin() const -> ConstIterator
{
    return Begin();
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::CEnd() const -> ConstIterator
{
    return End();
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Size() const -> Size_t
{
    return m_size;
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::Empty() const -> bool
{
    return m_size == 0;
}

template <class T_t, class Alloc_t>
inline auto List<T_t, Alloc_t>::InsertBefore(ConstIterator it_pos, const Val_t& val)
    -> void
{
    RDS_Assert(it_pos.IsCompatible(*this) && "List is not compatible.");

    /*
     * >> Before Inserting:
                                it_pos.m_data_ptr
                                    ↓
    ...<-p-[prev_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...

     * >> After Inserting:
                                                it_pos.m_data_ptr
                                                    ↓
    ...<-p-[prev_node]-n-><-p-[new_node]-n-><-p-[ins_node]-n-><-p-[next_node]-n->...
    */

    Node_D_t* new_node_ptr = CreateNode(val);

    auto* ins_node_ptr  = const_cast<Node_D_t*>(it_pos.GetDataPointer());
    auto* prev_node_ptr = ins_node_ptr->prev;

    new_node_ptr->prev = prev_node_ptr;
    new_node_ptr->next = ins_node_ptr;

    prev_node_ptr->next = new_node_ptr;
    ins_node_ptr->prev  = new_node_ptr;

    ++m_size;
}

template <class T_t, class Alloc_t>
template <class Other_Alloc_t>
inline auto
List<T_t, Alloc_t>::operator==(const List<Val_t, Other_Alloc_t>& other) const -> bool
{
    if (m_size != other.m_size)
        return false;

    if (m_size == 0 && other.m_size == 0)
        return true;

    auto* this_ptr  = m_sentinel_node.next;
    auto* other_ptr = other.m_sentinel_node.next;

    while (this_ptr != std::addressof(m_sentinel_node))
    {
        if (this_ptr->val != other_ptr->val)
            return false;

        this_ptr  = this_ptr->next;
        other_ptr = other_ptr->next;
    }

    return true;
}

RDS_END;

#endif // RDS_LIST_HPP