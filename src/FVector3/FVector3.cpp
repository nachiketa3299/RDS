#include "FFVector3.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;
using Val_t     = FVector3::Val_t;
using VE_pred_t = FVector3::VE_pred_t;

FVector3::FVector3()
{}

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

FVector3::FVector3(const FVector3& other)
    : X(other.X)
    , Y(other.Y)
    , Z(other.Z)
{}

FVector3::~FVector3()
{}

const FVector3 FVector3::XAxisVector()
{
    return FVector3(1.f, 0.f, 0.f);
}

const FVector3 FVector3::YAxisVector()
{
    return FVector3(0.f, 1.f, 0.f);
}

const FVector3 FVector3::ZAxisVector()
{
    return FVector3(0.f, 0.f, 0.f);
}

const FVector3 FVector3::ZeroVector()
{
    return FVector3(0.f);
}

const FVector3 FVector3::ForwardVector()
{
    return FVector3(1.f, 0.f, 0.f);
}

const FVector3 FVector3::BackwardVector()
{
    return ForwardVector().operator-();
}

const FVector3 FVector3::LeftVector()
{
    return RightVector().operator-();
}

const FVector3 FVector3::RightVector()
{
    return FVector3(0.f, 1.f, 0.f);
}

const FVector3 FVector3::UpVector()
{
    return FVector3(0.f, 0.f, 1.f);
}

const FVector3 FVector3::DownVector()
{
    return UpVector().operator-();
}

FVector3 FVector3::GetAbs() const
{
    return FVector3(abs(X), abs(Y), abs(Z));
}

void FVector3::Set(const FVector3& other)
{
    operator=(other);
}

void FVector3::Set(Val_t x, Val_t y, Val_t z)
{
    operator=(FVector3(x, y, z));
}

void FVector3::Clear()
{
    operator=(ZeroVector());
}

FVector3 FVector3::GetSafeNormal(float tolerance) const
{
    const auto len = Length();
    if (len <= tolerance)
        return ZeroVector();
    return operator/(len);
}

FVector3 FVector3::GetUnsafeNormal() const
{
    return operator/(Length());
}

float FVector3::LengthSquared() const
{
    return pow(X, 2) + pow(Y, 2) + pow(Z, 2);
}

float FVector3::Length() const
{
    return sqrt(LengthSquared());
}

float FVector3::DistanceSquared(const FVector3& s, const FVector3& e)
{
    return s.operator-(e).Length();
}

float FVector3::Distance(const FVector3& s, const FVector3& e)
{
    return sqrt(DistanceSquared(s, e));
}

FVector3 FVector3::GetCrossProduct(const FVector3& other) const
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return FVector3((y1 * z2 - z1 * y2), (z1 * x2 - x1 * z2), (x1 * y2 - y1 * x2));
}

float FVector3::GetDotProduct(const FVector3& other) const
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return x1 * x2 + y1 * y2 + z1 * z2;
}

FVector3& FVector3::operator=(const FVector3& other)
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return *this;
}

FVector3 FVector3::operator+(const FVector3& other) const
{
    return FVector3(X + other.X, Y + other.Y, Z + other.Z);
}

FVector3 FVector3::operator+(float bias) const
{
    return FVector3(X + bias, Y + bias, Z + bias);
}

FVector3 FVector3::operator-() const
{
    return FVector3(-X, -Y, -Z);
}

FVector3 FVector3::operator-(const FVector3& other) const
{
    return operator+(other.operator-());
}

FVector3 FVector3::operator-(float bias) const
{
    return operator+(-bias);
}

FVector3 FVector3::operator*(float coeff) const
{
    return FVector3(X * coeff, Y * coeff, Z * coeff);
}

FVector3 FVector3::operator*(const FVector3& other) const
{
    return FVector3(X * other.X, Y * other.Y, Z * other.Z);
}

FVector3 FVector3::operator/(float coeff) const
{
    return operator*(1.f / coeff);
}

FVector3 FVector3::operator/(const FVector3& other) const
{
    return operator*(FVector3(1.f / other.X, 1.f / other.Y, 1.f / other.Z));
}

FVector3& FVector3::operator+=(const FVector3& other)
{
    return operator=(operator+(other));
}

FVector3& FVector3::operator-=(const FVector3& other)
{
    return operator=(operator-(other));
}

FVector3& FVector3::operator*=(float coeff)
{
    return operator=(operator*(coeff));
}

FVector3& FVector3::operator*=(const FVector3& other)
{
    return operator=(operator*(other));
}

FVector3& FVector3::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

FVector3& FVector3::operator/=(const FVector3& other)
{
    return operator=(operator/(other));
}

bool FVector3::operator==(const FVector3& other) const
{
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool FVector3::operator!=(const FVector3& other) const
{
    return !operator==(other);
}

Val_t& FVector3::operator[](int index)
{
    switch (static_cast<V3Idx>(index))
    {
    default:
    case V3Idx::X:
        return X;
    case V3Idx::Y:
        return Y;
    case V3Idx::Z:
        return Z;
    }
    return X;
}

const Val_t& FVector3::operator[](int index) const
{
    switch (static_cast<V3Idx>(index))
    {
    default:
    case V3Idx::X:
        return X;
    case V3Idx::Y:
        return Y;
    case V3Idx::Z:
        return Z;
    }
    return X;
}

void FVector3::Map(VE_pred_t pred)
{
    operator=(FVector3(pred(X), pred(Y), pred(Z)));
}

FVector3 operator*(float coeff, const FVector3& ref)
{
    return ref.operator*(coeff);
}

string FVector3::GetAsString() const
{
    return "(" + to_string(X) + ", " + to_string(Y) + ", " + to_string(Z) + ")";
}

RDS_END