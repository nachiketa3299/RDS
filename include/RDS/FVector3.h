#ifndef RDS_FVECTOR3_H
#define RDS_FVECTOR3_H

namespace rds
{

struct FVector3
{
    FVector3()                                   = default;
    FVector3(const FVector3&)                    = default;
    FVector3(FVector3&&)                         = default;
    auto operator=(const FVector3&) -> FVector3& = default;
    auto operator=(FVector3&&) -> FVector3&      = default;
    ~FVector3()                                  = default;

    FVector3(const float& x, const float& y, const float& z);
    FVector3(const float& xyz);

    auto operator-() const -> FVector3;

    auto operator+(const FVector3& other) const -> FVector3;
    auto operator+(const float& bias) const -> FVector3;

    auto operator-(const FVector3& other) const -> FVector3;
    auto operator-(const float& bias) const -> FVector3;

    friend auto operator*(const FVector3& vec, const float& coeff) -> FVector3;
    friend auto operator*(const float& coeff, const FVector3& vec) -> FVector3;

    auto operator/(const float& coeff) const -> FVector3;

    auto operator==(const FVector3& other) const -> bool;
    auto operator!=(const FVector3& other) const -> bool;

    auto operator+=(const FVector3& other) -> FVector3&;
    auto operator-=(const FVector3& other) -> FVector3&;
    auto operator*=(const float& coeff) -> FVector3&;
    auto operator/=(const float& coeff) -> FVector3&;

    auto operator[](const int& index) const -> const float&;
    auto operator[](const int& index) -> float&;

    auto Clear() -> void;

    auto Absolute() -> FVector3&;
    auto GetAbsoluted() const -> FVector3;

    auto Dot(const FVector3& other) const -> float;
    auto Cross(const FVector3& other) const -> FVector3;

    auto LengthSquared() const -> float;
    auto Length() const -> float;

    auto DistanceSquared(const FVector3& other) const -> float;
    auto Distance(const FVector3& other) const -> float;

    auto Normalize_Unsafe() -> void;
    auto Normalize() -> void;

    auto GetNormalized_Unsafe() const -> FVector3;
    auto GetNormalized() const -> FVector3;

    auto IsNormalized() const -> bool;

    float& x = _data[0];
    float& y = _data[1];
    float& z = _data[2];

private:
    float _data[3]{0.f, 0.f, 0.f};
};

static const FVector3 FVector3_Zero(0.0f, 0.0f, 0.0f);

} // namespace rds
#endif // RDS_FVECTOR3_H