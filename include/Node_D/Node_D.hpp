#ifndef NODE_D_HPP
#define NODE_D_HPP

#include <concepts>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 두 개의 링크를 소유한 구조체 (Double Link Node)
template <class T>
    requires std::default_initializable<T>
struct Node_D
{
public:
    using Val_t = T;

public:
    Node_D()
        : val()
        , next{nullptr}
        , prev{nullptr}
    {}

    Node_D(const Val_t& value)
        : val(value)
    {}

    ~Node_D() = default;

public:
    Val_t   val;
    Node_D* next;
    Node_D* prev;
};

RDS_END

#endif // NODE_D_HPP