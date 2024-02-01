#ifndef RDS_ILIST_H
#define RDS_ILIST_H

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Interface of list classes
/// @tparam T list element's type
/// @tparam Iter_t list's iterator type
template <typename T, typename Iter_t>
class IList
{
public: // Iterators
    virtual Iter_t Begin() const = 0;
    virtual Iter_t CBegin() const = 0;
    virtual Iter_t End() const = 0;
    virtual Iter_t CEnd() const = 0;

public: // Capacity
    virtual bool Empty() const = 0;
    virtual std::size_t Size() const = 0;
    virtual std::size_t MaxSize() const = 0;

public: // Element Access
    virtual T& Front() = 0;
    virtual const T& Front() const = 0;
    virtual T& Back() = 0;
    virtual const T& Back() const = 0;

public: // Modifiers
    virtual void PushFront(T val) = 0;
    virtual void PopFront() = 0;
    virtual void PushBack(T val) = 0;
    virtual void PopBack() = 0;
    virtual void Insert(Iter_t pit, T val) = 0;
    virtual void Erase(Iter_t pit) = 0;
    virtual void Erase(Iter_t first, Iter_t last) = 0;
    virtual void Swap(IList& other) = 0;
    virtual void Clear() = 0;

public: // Operations
    virtual void Splice(Iter_t pit, IList& other) = 0;
    virtual void Splice(Iter_t pit, IList& other, Iter_t ofirst) = 0;
    virtual void Splice(Iter_t pit, IList& other, Iter_t ofisrt, Iter_t olast) = 0;
    virtual void Remove(const T& val) = 0;
    /// @todo templated pure virtual? "overrided" method can have different signiture?
    virtual void RemoveIf() = 0;
    /// @brief Remove duplicated values in this list.
    virtual void Unique() = 0;
    /// @brief Merge @p other into this list by transffering all of its elements at
    /// their respected ordered positions into the container (both containers shall
    /// already be ordered). Removes all the elements in @p other (which becomes empty)
    /// and inserts them into their ordered position within container.
    virtual void Merge(IList& other) = 0;
    virtual void Sort() = 0;
    virtual void Reverse() = 0;
};

RDS_END

#endif // RDS_ILIST_H