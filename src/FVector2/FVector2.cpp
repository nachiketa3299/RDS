#include "FVector2.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;

using Val_t  = FVector2::Val_t;
using Pred_t = FVector2::Pred_t;

FVector2::FVector2(Val_t xy)
    : X(xy)
    , Y(xy)
{}

FVector2::FVector2(Val_t x, Val_t y)
    : X(x)
    , Y(y)
{}

auto FVector2::XAxis() -> const FVector2
{
    return FVector2(1.f, 0.f);
}

auto FVector2::YAxis() -> const FVector2
{
    return FVector2(0.f, 1.f);
}

auto FVector2::Zero() -> const FVector2
{
    return FVector2(0.f, 0.f);
}

auto FVector2::GetAbs() const -> FVector2
{
    return FVector2(abs(X), abs(Y));
}

auto FVector2::Set(const FVector2& other) -> void
{
    operator=(other);
}

auto FVector2::Set(Val_t x, Val_t y) -> void
{
    operator=(FVector2(x, y));
}

auto FVector2::Clear() -> void
{
    operator=(FVector2(0, 0));
}

auto FVector2::LengthSquared() const -> float
{
    return pow(X, 2) + pow(Y, 2);
}

auto FVector2::Length() const -> float
{
    return sqrt(LengthSquared());
}

auto FVector2::DistanceSquared(const FVector2& s, const FVector2& e) -> float
{
    return pow(s.X - e.X, 2) + pow(s.Y - e.Y, 2);
}

auto FVector2::Distance(const FVector2& start, const FVector2& end) -> float
{
    return sqrt(DistanceSquared(start, end));
}

auto FVector2::GetSafeNormal(float tolerance) const -> FVector2
{
    const auto len = Length();
    if (len <= tolerance)
        return Zero();
    return operator/(len);
}

auto FVector2::GetUnsafeNormal() const -> FVector2
{
    return operator/(Length());
}

auto FVector2::GetDotProduct(const FVector2& other) const -> float
{
    const auto& [x1, y1] = *this;
    const auto& [x2, y2] = other;
    return (x1 * x2) + (y1 * y2);
}

auto FVector2::operator=(const FVector2& other) -> FVector2&
{
    X = other.X;
    Y = other.Y;
    return *this;
}

auto FVector2::operator+(const FVector2& other) const -> FVector2
{
    return FVector2(X + other.X, Y + other.Y);
}

auto FVector2::operator+(float bias) const -> FVector2
{
    return FVector2(X + bias, Y + bias);
}

auto FVector2::operator-() const -> FVector2
{
    return FVector2(-X, -Y);
}

auto FVector2::operator-(const FVector2& other) const -> FVector2
{
    return operator+(other.operator-());
}

auto FVector2::operator-(float bias) const -> FVector2
{
    return operator+(-bias);
}

auto FVector2::operator*(float coeff) const -> FVector2
{
    return FVector2(X * coeff, Y * coeff);
}

auto FVector2::operator*(const FVector2& other) const -> FVector2
{
    return FVector2(X * other.X, Y * other.Y);
}

auto FVector2::operator/(float coeff) const -> FVector2
{
    return operator*(1.f / coeff);
}

auto FVector2::operator/(const FVector2& other) const -> FVector2
{
    return operator*(FVector2(1.f / other.X, 1.f / other.Y));
}

auto FVector2::operator+=(const FVector2& other) -> FVector2&
{
    return operator=(operator+(other));
}

auto FVector2::operator-=(const FVector2& other) -> FVector2&
{
    return operator=(operator-(other));
}

auto FVector2::operator*=(float coeff) -> FVector2&
{
    return operator=(operator*(coeff));
}

auto FVector2::operator*=(const FVector2& other) -> FVector2&
{
    return operator=(operator*(other));
}

auto FVector2::operator/=(float coeff) -> FVector2&
{
    return operator=(operator/(coeff));
}

auto FVector2::operator/=(const FVector2& other) -> FVector2&
{
    return operator=(operator/(other));
}

auto FVector2::operator==(const FVector2& other) -> bool
{
    return X == other.X && Y == other.Y;
}

auto FVector2::operator!=(const FVector2& other) -> bool
{
    return !operator==(other);
}

auto FVector2::operator[](int index) -> Val_t&
{
    switch (static_cast<EIdx>(index))
    {
    default:
    case EIdx::X: return X;
    case EIdx::Y: return Y;
    }
    return Y;
}

auto FVector2::operator[](int index) const -> const Val_t&
{
    switch (static_cast<EIdx>(index))
    {
    default:
    case EIdx::X: return X;
    case EIdx::Y: return Y;
    }
    return X;
}

auto FVector2::Map(Pred_t pred) -> void
{
    operator=(FVector2(pred(X), pred(Y)));
}

FVector2 operator*(float coeff, const FVector2& ref)
{
    return ref.operator*(coeff);
}

auto FVector2::GetAsString() const -> string
{
    return "(" + to_string(X) + ", " + to_string(Y) + ")";
}

RDS_END
