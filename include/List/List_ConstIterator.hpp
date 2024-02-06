#ifndef RDS_LIST_CONSTITERATOR_HPP
#define RDS_LIST_CONSTITERATOR_HPP

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 양방향 반복자
template <typename T>
class List_ConstIterator
{
public:
    using Val_t  = T;
    using Size_t = std::size_t;

public:
    T&       operator*();
    const T& operator*() const;
    T*       operator->();
    const T* operator->() const;

public:
    List_ConstIterator& operator++();
    List_ConstIterator  operator++(int);
    List_ConstIterator& operator--();
    List_ConstIterator  operator--(int);

private:
    Val_t* m_head;
    Size_t m_offset;
};

RDS_END

#endif // RDS_LIST_CONSTITERATOR_HPP