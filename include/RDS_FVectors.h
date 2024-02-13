/// @file RDS_FVectors.h

#ifndef RDS_FVECTORS_H
#define RDS_FVECTORS_H

#include <functional>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief \ref FVector2 클래스와 \ref FVector3 클래스에서 공통적으로 사용하는 타입에
/// 대한 정의를 위한 구조체
struct FVector
{
    /// @brief 벡터의 각 원소의 자료형
    using Val_t  = float;
    /// @brief 벡터의 각 원소에 적용할 수 있는 함수 객체의 자료형
    using Pred_t = std::function<Val_t(Val_t)>;
};

RDS_END

#endif // RDS_FVECTORS_H