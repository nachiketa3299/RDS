#ifndef RDS_LIST_ITERATOR_HPP
#define RDS_LIST_ITERATOR_HPP

#include "RDS_CoreDefs.h"

#include "List_ConstIterator.hpp"

RDS_BEGIN

template <class _List>
class List_Iterator: public List_ConstIterator<_List>
{
    friend _List;

public:
    using Super    = List_ConstIterator<_List>;
    using Val_t    = List_ConstIterator<_List>::Val_t;
    using Size_t   = List_ConstIterator<_List>::Size_t;
    using Node_D_t = List_ConstIterator<_List>::Node_D_t;

public:
    List_Iterator(Node_D_t* pnode, const _List* plist) noexcept
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

// IMPLEMENTATIONS //

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
