/// @file Node_D.hpp

#ifndef RDS_NODE_D_HPP
#define RDS_NODE_D_HPP

#include "RDS_CoreDefs.h"

RDS_BEGIN

/** @brief 두 개의 링크를 가지는 노드 구조체
 *  @tparam __T_t 노드가 가지는 값에 대한 자료형
 */
template <class __T_t>
struct Node_D
{
public:
    /// @brief 노드가 가지는 값에 대한 자료형
    using Value_t = __T_t;

public: // Default CDtors
    /// @brief 기본 생성자
    Node_D() = default;

    /// @brief 초기화 값으로 노드의 값을 초기화하는 생성자
    /// @param[in] value 초기화할 값
    Node_D(const Value_t& val)
        : val(val)
    {}

    /// @brief 이전 노드와 다음 노드를 가리키는 포인터를 받는 생성자
    Node_D(Node_D* prev, Node_D* next)
        : prev(prev)
        , next(next)
    {}

    /// @brief 기본 복사 생성자
    Node_D(const Node_D&) = default;
    /// @brief 기본 이동 생성자
    Node_D(Node_D&&)      = default;

    /// @brief 기본 소멸자
    ~Node_D() = default;

    /// @brief 기본 복사 대입 연산자
    auto operator=(const Node_D&) -> Node_D& = default;
    /// @brief 기본 이동 대입 연산자
    auto operator=(Node_D&&) -> Node_D&      = default;

public:
    /// @brief 노드가 가지는 값
    Value_t val{};
    /// @brief 이 노드의 다음 노드를 가리키는 포인터. 기본적으로 `nullptr`로
    /// 초기화된다.
    Node_D* next{nullptr};
    /// @brief 이 노드의 이전 노드를 가리키는 포인터. 기본적으로 `nullptr`로
    /// 초기화된다.
    Node_D* prev{nullptr};
};

RDS_END

#endif // RDS_NODE_D_HPP
