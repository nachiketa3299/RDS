/// @file Node_D.hpp

#ifndef RDS_NODE_D_HPP
#define RDS_NODE_D_HPP

#include <concepts>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 두 개의 링크를 가지는 노드 구조체
/// @tparam T_t 노드가 가지는 값에 대한 자료형
template <class T_t>
    requires std::default_initializable<T_t>
struct Node_D
{
public:
    /// @brief 노드가 가지는 값에 대한 자료형
    using Value_t = T_t;

public: // Default CDtors
    /// @brief 기본 생성자
    /// @details
    /// 멤버 \ref val 이 원시 자료형인 경우 value-initialization이
    /// 이루어진다.\n
    /// 멤버 \ref val 이 사용자 정의 자료형이 아닌 경우,
    /// default-initialization이 이루어지기 때문에, \ref Value_t 는 반드시
    /// `std::default_initializable`을 만족해야 한다.
    /// @test \ref Node_D_Ctor_gtest.cpp 에서 테스트한다.
    /// @test 템플릿 인자가 원시 자료형일 때 기본 생성자가 제대로 동작하는지
    /// 확인한다.
    /// @test 템플릿 인자가 사용자 정의 자료형일 때 기본 생성자가 제대로
    /// 동작하는지 확인한다.
    Node_D()  = default;
    /// @brief 기본 소멸자
    ~Node_D() = default;

public: // Custom Ctors
    /// @brief 초기화 값으로 노드의 값을 초기화하는 생성자
    /// @param[in] value 초기화할 값
    Node_D(const Value_t& value);
    /// @brief 이전 노드와 다음 노드를 가리키는 포인터를 받는 생성자
    Node_D(Node_D* prev, Node_D* next);

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

RDS_BEGIN

template <class T_t>
    requires std::default_initializable<T_t>
Node_D<T_t>::Node_D(const Value_t& value)
    : val(value)
{}

template <class T_t>
    requires std::default_initializable<T_t>
Node_D<T_t>::Node_D(Node_D* prev, Node_D* next)
    : prev(prev)
    , next(next)
{}

RDS_END

#endif // RDS_NODE_D_HPP
