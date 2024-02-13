/// @file FVector3.cpp

#include "FVector3.h"

#include <cmath>

RDS_BEGIN

using namespace std;

using Val_t  = FVector3::Val_t;
using Pred_t = FVector3::Pred_t;

FVector3::FVector3(Val_t xyz)
    : X(xyz)
    , Y(xyz)
    , Z(xyz)
{}

FVector3::FVector3(Val_t x, Val_t y, Val_t z)
    : X(x)
    , Y(y)
    , Z(z)
{}

auto FVector3::XAxis() -> const FVector3
{
    return FVector3(1.f, 0.f, 0.f);
}

auto FVector3::YAxis() -> const FVector3
{
    return FVector3(0.f, 1.f, 0.f);
}

auto FVector3::ZAxis() -> const FVector3
{
    return FVector3(0.f, 0.f, 0.f);
}

auto FVector3::Zero() -> const FVector3
{
    return FVector3(0.f);
}

auto FVector3::Forward() -> const FVector3
{
    return FVector3(1.f, 0.f, 0.f);
}

auto FVector3::Backward() -> const FVector3
{
    return Forward().operator-();
}

auto FVector3::Left() -> const FVector3
{
    return Right().operator-();
}

auto FVector3::Right() -> const FVector3
{
    return FVector3(0.f, 1.f, 0.f);
}

auto FVector3::Up() -> const FVector3
{
    return FVector3(0.f, 0.f, 1.f);
}

auto FVector3::Down() -> const FVector3
{
    return Up().operator-();
}

auto FVector3::GetAbs() const -> FVector3
{
    return FVector3(abs(X), abs(Y), abs(Z));
}

auto FVector3::Set(const FVector3& other) -> void
{
    operator=(other);
}

auto FVector3::Set(Val_t x, Val_t y, Val_t z) -> void
{
    operator=(FVector3(x, y, z));
}

auto FVector3::Clear() -> void
{
    operator=(Zero());
}

auto FVector3::GetSafeNormal(float tolerance) const -> FVector3
{
    const auto len = Length();
    if (len <= tolerance)
        return Zero();
    return operator/(len);
}

auto FVector3::GetUnsafeNormal() const -> FVector3
{
    return operator/(Length());
}

auto FVector3::LengthSquared() const -> float
{
    return pow(X, 2) + pow(Y, 2) + pow(Z, 2);
}

auto FVector3::Length() const -> float
{
    return sqrt(LengthSquared());
}

auto FVector3::DistanceSquared(const FVector3& s, const FVector3& e) -> float
{
    return s.operator-(e).Length();
}

auto FVector3::Distance(const FVector3& s, const FVector3& e) -> float
{
    return sqrt(DistanceSquared(s, e));
}

auto FVector3::GetCrossProduct(const FVector3& other) const -> FVector3
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return FVector3((y1 * z2 - z1 * y2), (z1 * x2 - x1 * z2), (x1 * y2 - y1 * x2));
}

auto FVector3::GetDotProduct(const FVector3& other) const -> float
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return x1 * x2 + y1 * y2 + z1 * z2;
}

auto FVector3::operator=(const FVector3& other) -> FVector3&
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return *this;
}

auto FVector3::operator+(const FVector3& other) const -> FVector3
{
    return FVector3(X + other.X, Y + other.Y, Z + other.Z);
}

auto FVector3::operator+(float bias) const -> FVector3
{
    return FVector3(X + bias, Y + bias, Z + bias);
}

auto FVector3::operator-() const -> FVector3
{
    return FVector3(-X, -Y, -Z);
}

auto FVector3::operator-(const FVector3& other) const -> FVector3
{
    return operator+(other.operator-());
}

auto FVector3::operator-(float bias) const -> FVector3
{
    return operator+(-bias);
}

auto FVector3::operator*(float coeff) const -> FVector3
{
    return FVector3(X * coeff, Y * coeff, Z * coeff);
}

auto FVector3::operator*(const FVector3& other) const -> FVector3
{
    return FVector3(X * other.X, Y * other.Y, Z * other.Z);
}

auto FVector3::operator/(float coeff) const -> FVector3
{
    return operator*(1.f / coeff);
}

auto FVector3::operator/(const FVector3& other) const -> FVector3
{
    return operator*(FVector3(1.f / other.X, 1.f / other.Y, 1.f / other.Z));
}

auto FVector3::operator+=(const FVector3& other) -> FVector3&
{
    return operator=(operator+(other));
}

auto FVector3::operator-=(const FVector3& other) -> FVector3&
{
    return operator=(operator-(other));
}

auto FVector3::operator*=(float coeff) -> FVector3&
{
    return operator=(operator*(coeff));
}

auto FVector3::operator*=(const FVector3& other) -> FVector3&
{
    return operator=(operator*(other));
}

auto FVector3::operator/=(float coeff) -> FVector3&
{
    return operator=(operator/(coeff));
}

auto FVector3::operator/=(const FVector3& other) -> FVector3&
{
    return operator=(operator/(other));
}

auto FVector3::operator==(const FVector3& other) const -> bool
{
    return X == other.X && Y == other.Y && Z == other.Z;
}

auto FVector3::operator!=(const FVector3& other) const -> bool
{
    return !operator==(other);
}

auto FVector3::operator[](int index) -> Val_t&
{
    switch (static_cast<EIdx>(index))
    {
    default:
    case EIdx::X: return X;
    case EIdx::Y: return Y;
    case EIdx::Z: return Z;
    }
    return X;
}

auto FVector3::operator[](int index) const -> const Val_t&
{
    switch (static_cast<EIdx>(index))
    {
    default:
    case EIdx::X: return X;
    case EIdx::Y: return Y;
    case EIdx::Z: return Z;
    }
    return X;
}

auto FVector3::Map(Pred_t pred) -> void
{
    operator=(FVector3(pred(X), pred(Y), pred(Z)));
}

auto operator*(float coeff, const FVector3& ref) -> FVector3
{
    return ref.operator*(coeff);
}

string FVector3::GetAsString() const
{
    return "(" + to_string(X) + ", " + to_string(Y) + ", " + to_string(Z) + ")";
}

RDS_END