#ifndef NODE_D_HPP
#define NODE_D_HPP

#include <concepts>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief 두 개의 링크(자신을 향한 포인터, @p next, @p pref ) 를 소유한 구조체
/// @tparam _T 기본 생성자가 정의되어 있는 형식
/// @note 기본적으로 @p next 와 @p prev 는 @p nullptr 로 초기화된다.
template <class _T>
    requires std::default_initializable<_T>
struct Node_D
{
public:
    using Val_t = _T;

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