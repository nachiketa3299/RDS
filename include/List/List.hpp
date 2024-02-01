#ifndef RDS_LIST_HPP
#define RDS_LIST_HPP

#include "IList.h"
#include "ListNodes.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN

template <typename T>
class List_Iterator
{
};

template <typename T, typename Iter_t>
class List: IList<T, Iter_t>
{
public:
    List() = default;
    ~LIst() = default;
    List& operator==(const List& other);

public: // Iterators
    Iter_t Begin() const override
    {}
    Iter_t CBegin() const override
    {}
    Iter_t End() const override
    {}
    Iter_t CEnd() const override
    {}

public: // Capacity
    bool Empty() const override
    {}
    std::size_t Size() const override
    {}
    std::size_t MaxSize() const override
    {}

public: // Element Access
    T& Front() override
    {}
    const T& Front() const override
    {}
    T& Back() override
    {}
    const T& Back() const override
    {}

public: // Modifiers
    void PushFront(T val) override
    {}
    void PopFront() override
    {}
    void PushBack(T val) override
    {}
    void PopBack() override
    {}
    void Insert(Iter_t pit, T val) override
    {}
    void Erase(Iter_t pit) override
    {}
    void Erase(Iter_t first, Iter_t last) override
    {}
    void Swap(IList& other) override
    {}
    void Clear() override
    {}

public: // Operations
    void Splice(Iter_t pit, IList& other) override
    {}
    void Splice(Iter_t pit, IList& other, Iter_t ofirst) override
    {}
    void Splice(Iter_t pit, IList& other, Iter_t ofisrt, Iter_t olast) override
    {}
    void Remove(const T& val) override
    {}
    void RemoveIf() override
    {}
    void Unique() override
    {}
    void Merge(IList& other) override
    {}
    void Sort() override
    {}
    void Reverse() override
    {}
};

RDS_END

#endif // RDS_LIST_HPP