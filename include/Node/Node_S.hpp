#ifndef RDS_NODE_S_HPP
#define RDS_NODE_S_HPP

#include <utility> // std::forward

#include "RDS_CoreDefs.h"

namespace rds
{
/** @brief 하나의 링크를 가지는 노드 구조체
 *  @tparam T_t 노드가 가지는 값에 대한 자료형
 */
template <class T_t>
struct Node_S
{
public:
    /** @brief 노드가 가지는 값에 대한 자료형 */
    using Value_t = T_t;

public:
    /** @brief 기본 생성자 */
    Node_S()  = default;
    /** @brief 기본 소멸자 */
    ~Node_S() = default;

    /** @brief 노드의 값을 초기화하는 생성자
     *  @param value 초기화할 값
     */
    Node_S(const Value_t& val)
        : val(val)
    {}

    /** @brief 노드의 다음 노드를 가리키는 포인터를 받는 생성자
     *  @param next 노드가 가리킬 다음 노드에 대한 포인터
     */
    Node_S(Node_S* next)
        : next(next)
    {}

    /** @brief 노드가 보유한 값의 자료형의 생성자를 호출하는 생성자
     *  @tparam CtorArgs_t 노드가 보유한 값의 자료형의 생성자에 전달할
     * 인자들의 자료형 목록
     *  @param[in] ctor_args 노드가 보유한 값의 자료형의 생성자에
     * 전달할 인자들
     */
    template <class... __CtorArgs_t>
    Node_S(__CtorArgs_t&&... ctor_args)
        : val(std::forward<__CtorArgs_t>(ctor_args)...)
    {}

public:
    /** @brief 노드가 가지는 값 */
    Value_t val{};
    /** @brief 이 노드의 다음 노드를 가리키는 포인터. */
    Node_S* next{nullptr};
};

} // namespace rds

#endif // RDS_NODE_S_HPP