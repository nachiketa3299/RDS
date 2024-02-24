/// @file ForwardList_ConstIterator.hpp

#ifndef RDS_FORWARDLIST_CONSTITERATOR_HPP
#define RDS_FORWARDLIST_CONSTITERATOR_HPP

#include <memory>

#include "RDS_CoreDefs.h"

RDS_BEGIN

template <class ForwardList_t>
class ForwardList_ConstIterator
{
public:
    using Value_t  = typename ForwardList_t::Value_t;
    using Size_t   = typename ForwardList_t::Size_t;
    using Node_S_t = typename ForwardList_t::Node_S_t;

public:
    ForwardList_ConstIterator()                                 = default;
    ForwardList_ConstIterator(const ForwardList_ConstIterator&) = default;

public:
    auto operator=(const ForwardList_ConstIterator&)
        -> ForwardList_ConstIterator& = default;
    auto operator=(ForwardList_ConstIterator&&)
        -> ForwardList_ConstIterator& = default;

public:
    ~ForwardList_ConstIterator() = default;

public:
    explicit ForwardList_ConstIterator(const ForwardList_t* list,
                                       const Node_S_t*      node);

public:
    auto operator*() const -> const Value_t&;
    auto operator->() const -> const Value_t*;

public:
    auto operator++() -> ForwardList_ConstIterator&;
    auto operator++(int) -> ForwardList_ConstIterator;

public:
    auto operator==(const ForwardList_ConstIterator& other) const -> bool;
    auto operator!=(const ForwardList_ConstIterator& other) const -> bool;

public:
    auto IsValid() const -> bool;
    auto IsDereferencible() const -> bool;
    auto IsCompatible(const ForwardList_t& list) const -> bool;

public:
    auto GetDataPointer() const -> const Node_S_t*;

public:
    const ForwardList_t* m_cont_ptr{nullptr};
    const Node_S_t*      m_data_ptr{nullptr};

public:
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator*() const
    -> const Value_t&
{
    RDS_Assert(IsDereferencible() && "Cannot dereference invalid iterator.");
    return m_data_ptr->val;
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator->() const
    -> const Value_t*
{
    return std::pointer_traits<
        const typename ForwardList_t::Value_t*>::pointer_to(operator*());
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator++()
    -> ForwardList_ConstIterator&
{
    RDS_Assert(m_data_ptr != m_cont_ptr->GetSentinelPointer() &&
               "Cannot increment end iterator.");
    m_data_ptr = m_data_ptr->next;
    return *this;
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator++(int)
    -> ForwardList_ConstIterator
{
    const auto temp = *this;
    operator++();
    return temp;
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator==(
    const ForwardList_ConstIterator& other) const -> bool
{
    return IsCompatible(*other.m_cont_ptr) && (m_data_ptr == other.m_data_ptr);
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::operator!=(
    const ForwardList_ConstIterator& other) const -> bool
{
    return !operator==(other);
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::IsValid() const -> bool
{
    return m_cont_ptr != nullptr && m_data_ptr != nullptr;
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::IsDereferencible() const
    -> bool
{
    // 유효하지 않은 반복자는 역참조할 수 없다.
    if (!IsValid())
        return false;
    return m_data_ptr != m_cont_ptr->GetSentinelPointer();
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::IsCompatible(
    const ForwardList_t& list) const -> bool
{
    // 컨테이너에 대한 포인터에 저장된 값이 전달된 리스트의 주소값과 같은지
    // 확인한다.
    return m_cont_ptr == std::addressof(list);
}

template <class ForwardList_t>
inline auto ForwardList_ConstIterator<ForwardList_t>::GetDataPointer() const
    -> const Node_S_t*
{
    return m_data_ptr;
}

RDS_END

#endif // RDS_FORWARDLIST_CONSTITERATOR_HPP
