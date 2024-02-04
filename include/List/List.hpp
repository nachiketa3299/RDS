#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include <cstddef>
#include <iterator>
#include <list>

#include "RDS_CoreDefs.h"

template <typename T>
class List_ConstIterator
{
    T*          sn;
    std::size_t offset;
};

template <typename T>
class List_Iterator
{
};

template <typename T>
class List
{
public:
    using Val_t  = T;
    using Size_t = std::size_t;
    using It_t   = List_Iterator<Val_t>;
    using CIt_t  = List_ConstIterator<Val_t>;

public:
    List() = default;

public: // Modifiers
    void Clear();
    void Insert();
    void Erase();
    void PushBack();
    void PopBack();
    void PushFront();
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
    T sn;
};

#endif // RDS_LIST_HPP