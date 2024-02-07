#ifndef NODE_D_HPP
#define NODE_D_HPP

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 두 개의 링크를 소유한 구조체 (Double Link Node)
template <class T>
struct Node_D
{
public:
    using Val_t = T;

public:
    Node_D() = default;

    Node_D(const Val_t& value)
        : val(value)
    {}

    ~Node_D() = default;

public:
    /// @todo 이 초기화에 대해서 조금 더 조사할 것
    Val_t   val{};
    Node_D* next{nullptr};
    Node_D* prev{nullptr};
};

RDS_END

#endif // NODE_D_HPP