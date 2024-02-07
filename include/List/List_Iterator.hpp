#ifndef RDS_LIST_ITERATOR_HPP
#define RDS_LIST_ITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "List_ConstIterator.hpp"

RDS_BEGIN

template <class _List>
class List_Iterator: public List_ConstIterator<_List>
{
public:
    using Super   = List_ConstIterator<_List>;
    using Size_t  = typename List_ConstIterator<_List>::Size_t;
    using Val_t   = typename List_ConstIterator<_List>::Val_t;
    using DNode_t = typename List_ConstIterator<_List>::DNode_t;

public:
    List_Iterator(DNode_t* pnode, const _List* plist) noexcept
        : Super(pnode, plist)
    {}

public:
    Val_t& operator*() const noexcept;
    Val_t* operator->() const noexcept;

public:
    List_Iterator& operator++() noexcept;
    List_Iterator  operator++(int) noexcept;
    List_Iterator& operator--() noexcept;
    List_Iterator  operator--(int) noexcept;
};

RDS_END

// IMPLEMTATIONS //

RDS_BEGIN

template <typename _List>
inline auto List_Iterator<_List>::operator*() const noexcept -> Val_t&
{
    return const_cast<Val_t&>(Super::operator*());
}

template <typename _List>
inline auto List_Iterator<_List>::operator->() const noexcept -> Val_t*
{
    return const_cast<Val_t*>(Super::operator->());
}

template <typename _List>
inline auto List_Iterator<_List>::operator++() noexcept -> List_Iterator&
{
    Super::operator++();
    return *this;
}

template <typename _List>
inline auto List_Iterator<_List>::operator++(int) noexcept -> List_Iterator
{
    auto temp = *this;
    operator++();
    return temp;
}

template <typename _List>
inline auto List_Iterator<_List>::operator--() noexcept -> List_Iterator&
{
    Super::operator--();
    return *this;
}

template <typename _List>
inline auto List_Iterator<_List>::operator--(int) noexcept -> List_Iterator
{
    auto temp = *this;
    operator--();
    return temp;
}

RDS_END

#endif // RDS_LIST_ITERATOR_HPP
