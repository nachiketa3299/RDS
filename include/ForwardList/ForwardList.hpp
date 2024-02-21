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

RDS_BEGIN

template <class T_t, class Alloc_t = Mallocator<Node_S<T_t>>>
class ForwardList
{
public: // Type Aliases
    using Value_t     = T_t;
    using Size_t      = std::size_t;
    using Node_S_t    = Node_S<Value_t>;
    using Allocator_t = Alloc_t;

public: // Iterator Type Aliases
    using Const_Iterator_t = ForwardList_Const_Iterator_t<ForwardList<Value_t>>;
    using Iterator_t       = ForwardList_Iterator<ForwardList<Value_t>>;

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
    auto BeforeBegin() const -> Const_Iterator_t;
    auto BeforeBegin() -> Iterator_t;
    auto Begin() const -> Const_Iterator_t;
    auto Begin() -> Iterator_t;
    auto End() const -> Const_Iterator_t;
    auto End() -> Iterator_t;

public: // Const Iterators
    auto CBeforeBegin() const -> Const_Iterator_t;
    auto CBegin() const -> Const_Iterator_t;
    auto CEnd() const -> Const_Iterator_t;

public: // Modifiers
    auto Assign();
    auto EmplaceFront();
    auto PushFront();
    auto PopFront();
    auto EmplaceAfter();
    auto InsertAfter();
    auto EraseAfter();
    auto Swap();
    auto Resize();

public: // Operations
    auto SpliceAfter();
    auto Remove();
    auto RemoveIf();
    auto Unique();
    auto Merge();
    auto Sort();
    auto Reverse();

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

#endif // RDS_FORWARDLIST_HPP