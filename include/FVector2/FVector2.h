/// @file FVector2.h

#ifndef RDS_FVECTOR2_H
#define RDS_FVECTOR2_H

#include <string>

#include "RDS_CoreDefs.h"
#include "RDS_FVectors.h"

RDS_BEGIN

/// @brief 2개의 실수형 값을 가지는 벡터 클래스
class FVector2
{
public:
    /// @enum EIdx
    /// @brief 벡터의 각 원소에 대한 인덱스
    enum class EIdx
    {
        X   = 0, ///< `X` 원소에 대한 인덱스
        Y   = 1, ///< `Y` 원소에 대한 인덱스
        MAX = 2  ///< 원소의 갯수
    };

public:
    /// @brief 벡터의 각 원소의 자료형
    using Val_t  = FVector::Val_t;
    /// @brief 벡터의 각 원소에 적용할 수 있는 함수 객체의 자료형
    using Pred_t = FVector::Pred_t;

public:
    /// @brief 기본 생성자
    FVector2()                      = default;
    /// @brief 기본 복사 생성자
    FVector2(const FVector2& other) = default;
    /// @brief 기본 소멸자
    ~FVector2()                     = default;

public:
    /// @brief 하나의 초기화 값을 받는 생성자.
    /// @param[in] xy 초기화할 값
    FVector2(Val_t xy);

    /// @brief 벡터의 각 원소를 초기화하는 생성자.
    /// @param[in] x 초기화할 `x` 값
    /// @param[in] y 초기화할 `y` 값
    FVector2(Val_t x, Val_t y);

public:
    /// @brief (1.0, 0.0) 벡터를 반환한다.
    static auto XAxis() -> const FVector2;
    /// @brief (0.0, 1.0) 벡터를 반환한다.
    static auto YAxis() -> const FVector2;
    /// @brief (0.0, 0.0) 벡터를 반환한다.
    static auto Zero() -> const FVector2;

public:
    /// @brief 이 벡터의 각 원소에 절대값을 취한 벡터의 사본을 반환한다.
    /// @return 이 벡터의 각 원소에 절대값을 취한 벡터의 사본.
    auto GetAbs() const -> FVector2;

public:
    /// @brief 벡터의 각 원소를 인자로 전달된 다른 벡터로 설정한다.
    /// @param[in] other 설정할 벡터
    auto Set(const FVector2& other) -> void;
    /// @brief 벡터의 각 원소를 인자로 전달된 각 실수로 설정한다.
    /// @param[in] x `x` 원소로 설정할 값
    /// @param[in] y `y` 원소로 설정할 값
    auto Set(Val_t x, Val_t y) -> void;
    /// @brief 이 벡터를 (0.0, 0.0, 0.0) 벡터로 만든다.
    auto Clear() -> void;

public:
    /// @brief 이 벡터의 정규화된 사본을 반환한다. 벡터의 길이가 너무 작아 정규화할 수
    /// 없는지 확인한다.
    /// @param tolerance 정규화할 수 있는 벡터의 길이 제곱의 최소값
    /// @return 정규화할 수 있는 경우 정규화된 벡터의 사본, 그렇지 않은 경우 (0.0, 0.0,
    /// 0.0)
    auto GetSafeNormal(float tolerance) const -> FVector2;
    /// @brief 이 벡터의 정규화된 사본을 반환한다. 벡터의 길이에 따른 정규화 가능 여부를
    /// 확인하지 않는다.
    auto GetUnsafeNormal() const -> FVector2;

public:
    /// @brief 이 벡터의 길이의 제곱을 반환한다.
    /// @return 벡터 길이의 제곱
    auto        LengthSquared() const -> float;
    /// @brief 이 벡터의 길이를 반환한다.
    /// @return 벡터의 길이
    auto        Length() const -> float;
    /// @brief 두 벡터 사이의 길이의 제곱을 반환한다.
    /// @param[in] start 시작 벡터
    /// @param[in] end 끝 벡터
    /// @return 두 벡터 사이의 길이의 제곱
    static auto DistanceSquared(const FVector2& start, const FVector2& end) -> float;
    /// @brief 두 벡터 사이의 길이를 반환한다.
    /// @param[in] start 시작 벡터
    /// @param[in] end 끝 벡터
    /// @return 두 벡터 사이의 길이
    static auto Distance(const FVector2& start, const FVector2& end) -> float;

public:
    /// @brief 인자로 전달된 벡터와 이 벡터의 점곱을 반환한다.
    /// @param[in] other 점곱을 계산할 다른 벡터
    /// @return 점곱
    auto GetDotProduct(const FVector2& other) const -> float;

public:
    /// @brief 이 벡터의 각 원소의 값을 인자로 전달된 벡터의 각 원소의 값으로 설정한 후,
    /// 자신에 대한 lvalue 참조를 반환한다.
    /// @param other 원소의 값들을 가져올 다른 벡터
    /// @return 자신에 대한 lvalue 참조
    auto operator=(const FVector2& other) -> FVector2&;
    /// @brief 인자로 전달된 다른 벡터와 이 벡터를 각 원소별로 더한 값을 원소로 하는 새
    /// 벡터를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 연산 결과에 대한 사본 벡터
    auto operator+(const FVector2& other) const -> FVector2;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 더한 값을 원소로 하는 새 벡터를
    /// 반환한다.
    /// @param[in] bias 각 원소에 더할 실수 값
    /// @return 연산 결과에 대한 사본 벡터
    auto operator+(float bias) const -> FVector2;
    /// @brief 이 벡터의 각 원소에 -1을 곱한 값을 원소로 하는 새 벡터를 반환한다.
    /// @return 연산 결과에 대한 사본 벡터
    auto operator-() const -> FVector2;
    /// @brief 인자로 전달된 다른 벡터와 이 벡터를 각 원소별로 뺀 값을 원소로 하는 새
    /// 벡터를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 연산 결과에 대한 사본 벡터
    auto operator-(const FVector2& other) const -> FVector2;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 뺀 값을 원소로 하는 새 벡터를
    /// 반환한다.
    /// @param[in] bias 각 원소에 더할 실수 값
    /// @return 연산 결과에 대한 사본 벡터
    auto operator-(float bias) const -> FVector2;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 곱한 값을 원소로 하는 새 벡터를
    /// 반환한다.
    /// @param[in] coeff 각 원소에 더할 실수 값
    /// @return 연산 결과에 대한 사본 벡터
    auto operator*(float coeff) const -> FVector2;
    /// @brief 인자로 전달된 다른 벡터와 이 벡터를 각 원소별로 곱한 값을 원소로 하는 새
    /// 벡터를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 연산 결과에 대한 사본 벡터
    auto operator*(const FVector2& other) const -> FVector2;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 나눈 값을 원소로 하는 새 벡터를
    /// 반환한다.
    /// @param[in] coeff 각 원소에 더할 실수 값
    /// @return 연산 결과에 대한 사본 벡터
    /// @todo 0 divide case
    auto operator/(float coeff) const -> FVector2;
    /// @brief 인자로 전달된 다른 벡터와 이 벡터를 각 원소별로 나눈 값을 원소로 하는 새
    /// 벡터를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 연산 결과에 대한 사본 벡터
    /// @todo 0 divide case
    auto operator/(const FVector2& other) const -> FVector2;
    /// @brief 인자로 전달된 벡터의 각 원소를 이 벡터의 각 원소에 더한 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 자신에 대한 lvalue 참조
    auto operator+=(const FVector2& other) -> FVector2&;
    /// @brief 인자로 전달된 벡터의 각 원소를 이 벡터의 각 원소에 뺀 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 자신에 대한 lvalue 참조
    auto operator-=(const FVector2& other) -> FVector2&;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 곱한 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] coeff 연산을 수행할 실수
    /// @return 자신에 대한 lvalue 참조
    auto operator*=(float coeff) -> FVector2&;
    /// @brief 인자로 전달된 벡터의 각 원소를 이 벡터의 각 원소에 곱한 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 자신에 대한 lvalue 참조
    auto operator*=(const FVector2& other) -> FVector2&;
    /// @brief 인자로 전달된 실수를 이 벡터의 각 원소에 나눈 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] coeff 연산을 수행할 실수
    /// @return 자신에 대한 lvalue 참조
    /// @todo 0-divide case
    auto operator/=(float coeff) -> FVector2&;
    /// @brief 인자로 전달된 벡터의 각 원소를 이 벡터의 각 원소에 나눈 후, 자신에 대한
    /// lvalue 참조를 반환한다.
    /// @param[in] other 연산을 수행할 다른 벡터
    /// @return 자신에 대한 lvalue 참조
    /// @todo 0-divide case
    auto operator/=(const FVector2& other) -> FVector2&;

public:
    /// @brief 인자로 전달된 다른 벡터와 이 벡터가 같은지 비교한다. 벡터가 같다는 것은
    /// 각 원소가 모두 같은 값이라는 것을 의미한다.
    /// @param[in] other 비교할 다른 벡터
    /// @return 같은 경우 true, 다를 경우 false
    auto operator==(const FVector2& other) -> bool;
    /// @brief 인자로 전달된 다른 벡터와 이 벡터가 다른지 비교한다. 벡터가 다르다는 것은
    /// 적어도 하나의 원소가 다른 값이라는 것을 의미한다.
    /// @param[in] other 비교할 다른 벡터
    /// @return 다를 경우 true, 같을 경우 false
    auto operator!=(const FVector2& other) -> bool;

public:
    /// @brief 인자로 전달된 인덱스에 맞는 벡터의 원소에 대한 lvalue 참조를 반환한다.
    /// @details 인덱스는 @ref EIdx에 정의되어 있으며, 범위는 [0-2)이다. 범위를 벗어나는
    /// 경우 범위와 가장 가까운 인덱스로 처리된다.
    /// @todo 음수인 경우 어떻게 되지?
    /// @return 인덱스에 해당하는 벡터 원소의 lvalue 참조
    auto operator[](int index) -> Val_t&;
    /// @brief 인자로 전달된 인덱스에 맞는 벡터의 원소에 대한 const-lvalue 참조를
    /// 반환한다.
    /// @details 인덱스는 @ref EIdx에 정의되어 있으며, 범위는 [0-2)이다. 범위를 벗어나는
    /// 경우 범위와 가장 가까운 인덱스로 처리된다.
    /// @todo 음수인 경우 어떻게 되지?
    /// @return 인덱스에 해당하는 벡터 원소의 const-lvalue 참조
    auto operator[](int index) const -> const Val_t&;
    /// @brief 인자로 전달된 함수 객체를 벡터의 모든 원소에 적용한다.
    /// @param[in] pred 적용할 함수 객체
    auto Map(Pred_t pred) -> void;

public:
    /// @brief 인자로 전달된 벡터의 각 원소에 인자로 전달된 실수를 곱한 벡터의 사본을
    /// 반환한다.
    /// @param coeff 연산을 수행할 실수
    /// @param vec  연산을 수행할 벡터
    /// @return 연산 결과에 대한 사본 벡터
    friend auto operator*(float coeff, const FVector2& ref) -> FVector2;

public:
    std::string GetAsString() const;

private:
    /// @brief 벡터의 `X` 에 해당하는 원소. 인덱스는 0이다.
    Val_t X{};
    /// @brief 벡터의 `Y` 에 해당하는 원소. 인덱스는 1이다.
    Val_t Y{};
};

RDS_END

#endif // RDS_VECTOR2_H