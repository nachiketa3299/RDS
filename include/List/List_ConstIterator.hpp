#ifndef RDS_LIST_CONSTITERATOR_HPP
#define RDS_LIST_CONSTITERATOR_HPP

#include <list>
#include <memory>

#include "RDS_CoreDefs.h"

#include "Assertion.h"

RDS_BEGIN

/// @brief Bidirectional iterator template class for @ref List class.
template <class _List>
class List_ConstIterator
{
public:
    using Val_t    = _List::Val_t;
    using Size_t   = _List::Size_t;
    using Node_D_t = _List::Node_D_t;

public:
    List_ConstIterator() noexcept
        : m_ptr(nullptr)
        , m_proxy(nullptr)
    {}

    List_ConstIterator(Node_D_t* pnode, const _List* plist) noexcept
        : m_ptr(pnode)
        , m_proxy(plist)
    {}

public:
    const Val_t* operator->() const noexcept;
    const Val_t& operator*() const noexcept;

public:
    /// @todo (2) process sentinel_node
    List_ConstIterator& operator++() noexcept;
    List_ConstIterator  operator++(int) noexcept;
    List_ConstIterator& operator--() noexcept;
    List_ConstIterator  operator--(int) noexcept;

private:
    Node_D_t*    m_ptr;
    const _List* m_proxy;
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <typename _List>
inline auto List_ConstIterator<_List>::operator*() const noexcept -> const Val_t&
{
    return m_ptr->val;
}

template <typename _List>
inline auto List_ConstIterator<_List>::operator->() const noexcept -> const Val_t*
{
    return std::pointer_traits<const _List::Val_t*>((*this).operator*());
}

template <typename _List>
inline auto List_ConstIterator<_List>::operator++() noexcept
    -> List_ConstIterator<_List>&
{
    m_ptr = m_ptr->next;
    return *this;
}

template <typename _List>
inline auto List_ConstIterator<_List>::operator++(int) noexcept
    -> List_ConstIterator<_List>
{
    auto temp = *this;
    m_ptr     = m_ptr->next;
    return temp;
}

template <typename _List>
inline auto List_ConstIterator<_List>::operator--() noexcept
    -> List_ConstIterator<_List>&
{
    m_ptr = m_ptr->prev;
    return *this;
}

template <typename _List>
inline auto List_ConstIterator<_List>::operator--(int) noexcept
    -> List_ConstIterator<_List>
{
    auto temp = *this;
    m_ptr     = m_ptr->prev;
    return temp;
}

RDS_END

#endif // RDS_LIST_CONSTITERATOR_HPP
