/// @file Node_S.hpp

#ifndef RDS_NODE_S_HPP
#define RDS_NODE_S_HPP

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 하나의 링크를 가지는 노드 구조체
/// @tparam T_t 노드가 가지는 값에 대한 자료형
template <class T_t>
struct Node_S
{
public: // Type Aliases
    /// @brief 노드가 가지는 값에 대한 자료형
    using Value_t = T_t;

public: // Default CDtors
    /// @brief 기본 생성자
    Node_S()  = default;
    /// @brief 기본 소멸자
    ~Node_D() = default;

public: // Custom Ctors
    /// @brief 노드의 값을 초기화하는 생성자
    /// @param value 초기화할 값
    Node_S(const Value_t& value);
    /// @brief 노드의 다음 노드를 가리키는 포인터를 받는 생성자
    /// @param next 노드가 가리킬 다음 노드에 대한 포인터
    Node_S(Node_S* next);

public: // Member Variables
    /// @brief 노드가 가지는 값
    Value_t val{};
    /// @brief 이 노드의 다음 노드를 가리키는 포인터. 기본적으로 `nullptr`로
    /// 초기화된다.
    Node_S* next{nullptr};
};

RDS_END

// IMPLEMENTATIONS //

RDS_BEGIN

template <class T_t>
inline Node_S<T_t>::Node_S(const Value_t& value)
    : val(value)
{}

template <class T_t>
inline Node_S<T_t>::Node_S(Node_S* next)
    : next(next)
{}

RDS_END

#endif // RDS_NODE_S_HPP
