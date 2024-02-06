#include "FVector2.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;
using Val_t     = FVector2::Val_t;
using VE_pred_t = FVector2::VE_pred_t;

FVector2::FVector2()
{}

FVector2::FVector2(Val_t xy)
    : X(xy)
    , Y(xy)
{}

FVector2::FVector2(Val_t x, Val_t y)
    : X(x)
    , Y(y)
{}

FVector2::FVector2(const FVector2& other)
    : X(other.X)
    , Y(other.Y)
{}

FVector2::~FVector2()
{}

const FVector2 FVector2::XAxisVector()
{
    return FVector2(1.f, 0.f);
}

const FVector2 FVector2::YAxisVector()
{
    return FVector2(0.f, 1.f);
}

const FVector2 FVector2::ZeroVector()
{
    return FVector2(0.f, 0.f);
}

FVector2 FVector2::GetAbs() const
{
    return FVector2(abs(X), abs(Y));
}

void FVector2::Set(const FVector2& other)
{
    operator=(other);
}

void FVector2::Set(Val_t x, Val_t y)
{
    operator=(FVector2(x, y));
}

inline void FVector2::Clear()
{
    operator=(FVector2(0, 0));
}

float FVector2::LengthSquared() const
{
    return pow(X, 2) + pow(Y, 2);
}

float FVector2::Length() const
{
    return sqrt(LengthSquared());
}

float FVector2::DistanceSquared(const FVector2& s, const FVector2& e)
{
    return pow(s.X - e.X, 2) + pow(s.Y - e.Y, 2);
}

float FVector2::Distance(const FVector2& start, const FVector2& end)
{
    return sqrt(DistanceSquared(start, end));
}

FVector2 FVector2::GetSafeNormal(float tolerance) const
{
    const auto len = Length();
    if (len <= tolerance)
        return ZeroVector();
    return operator/(len);
}

FVector2 FVector2::GetUnsafeNormal() const
{
    return operator/(Length());
}

float FVector2::GetDotProduct(const FVector2& other) const
{
    const auto& [x1, y1] = *this;
    const auto& [x2, y2] = other;
    return (x1 * x2) + (y1 * y2);
}

FVector2& FVector2::operator=(const FVector2& other)
{
    X = other.X;
    Y = other.Y;
    return *this;
}

FVector2 FVector2::operator+(const FVector2& other) const
{
    return FVector2(X + other.X, Y + other.Y);
}

FVector2 FVector2::operator+(float bias) const
{
    return FVector2(X + bias, Y + bias);
}

FVector2 FVector2::operator-() const
{
    return FVector2(-X, -Y);
}

FVector2 FVector2::operator-(const FVector2& other) const
{
    return operator+(other.operator-());
}

FVector2 FVector2::operator-(float bias) const
{
    return operator+(-bias);
}

FVector2 FVector2::operator*(float coeff) const
{
    return FVector2(X * coeff, Y * coeff);
}

FVector2 FVector2::operator*(const FVector2& other) const
{
    return FVector2(X * other.X, Y * other.Y);
}

FVector2 FVector2::operator/(float coeff) const
{
    return operator*(1.f / coeff);
}

FVector2 FVector2::operator/(const FVector2& other) const
{
    return operator*(FVector2(1.f / other.X, 1.f / other.Y));
}

FVector2& FVector2::operator+=(const FVector2& other)
{
    return operator=(operator+(other));
}

FVector2& FVector2::operator-=(const FVector2& other)
{
    return operator=(operator-(other));
}

FVector2& FVector2::operator*=(float coeff)
{
    return operator=(operator*(coeff));
}

FVector2& FVector2::operator*=(const FVector2& other)
{
    return operator=(operator*(other));
}

FVector2& FVector2::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

FVector2& FVector2::operator/=(const FVector2& other)
{
    return operator=(operator/(other));
}

bool FVector2::operator==(const FVector2& other)
{
    return X == other.X && Y == other.Y;
}

bool FVector2::operator!=(const FVector2& other)
{
    return !operator==(other);
}

Val_t& FVector2::operator[](int index)
{
    switch (static_cast<V2Idx>(index))
    {
    default:
    case V2Idx::X:
        return X;
    case V2Idx::Y:
        return Y;
    }
    return Y;
}

const Val_t& FVector2::operator[](int index) const
{
    switch (static_cast<V2Idx>(index))
    {
    default:
    case V2Idx::X:
        return X;
    case V2Idx::Y:
        return Y;
    }
    return X;
}

void FVector2::Map(VE_pred_t pred)
{
    operator=(FVector2(pred(X), pred(Y)));
}

FVector2 operator*(float coeff, const FVector2& ref)
{
    return ref.operator*(coeff);
}

string FVector2::GetAsString() const
{
    return "(" + to_string(X) + ", " + to_string(Y) + ")";
}

RDS_END
