#include "Vector3.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;
using VE_t = Vector3::VE_t;
using VE_pred_t = Vector3::VE_pred_t;

Vector3::Vector3()
{}

Vector3::Vector3(VE_t xyz)
    : X(xyz)
    , Y(xyz)
    , Z(xyz)
{}

Vector3::Vector3(VE_t x, VE_t y, VE_t z)
    : X(x)
    , Y(y)
    , Z(z)
{}

Vector3::Vector3(const Vector3& other)
    : X(other.X)
    , Y(other.Y)
    , Z(other.Z)
{}

Vector3::~Vector3()
{}

const Vector3 Vector3::XAxisVector()
{
    return Vector3(1.f, 0.f, 0.f);
}

const Vector3 Vector3::YAxisVector()
{
    return Vector3(0.f, 1.f, 0.f);
}

const Vector3 Vector3::ZAxisVector()
{
    return Vector3(0.f, 0.f, 0.f);
}

const Vector3 Vector3::ZeroVector()
{
    return Vector3(0.f);
}

const Vector3 Vector3::ForwardVector()
{
    return Vector3(1.f, 0.f, 0.f);
}

const Vector3 Vector3::BackwardVector()
{
    return ForwardVector().operator-();
}

const Vector3 Vector3::LeftVector()
{
    return RightVector().operator-();
}

const Vector3 Vector3::RightVector()
{
    return Vector3(0.f, 1.f, 0.f);
}

const Vector3 Vector3::UpVector()
{
    return Vector3(0.f, 0.f, 1.f);
}

const Vector3 Vector3::DownVector()
{
    return UpVector().operator-();
}

Vector3 Vector3::GetAbs() const
{
    return Vector3(abs(X), abs(Y), abs(Z));
}

void Vector3::Set(const Vector3& other)
{
    operator=(other);
}

void Vector3::Set(VE_t x, VE_t y, VE_t z)
{
    operator=(Vector3(x, y, z));
}

void Vector3::Clear()
{
    operator=(ZeroVector());
}

Vector3 Vector3::GetSafeNormal(float tolerance) const
{
    const auto len = Length();
    if (len <= tolerance)
        return ZeroVector();
    return operator/(len);
}

Vector3 Vector3::GetUnsafeNormal() const
{
    return operator/(Length());
}

float Vector3::LengthSquared() const
{
    return pow(X, 2) + pow(Y, 2) + pow(Z, 2);
}

float Vector3::Length() const
{
    return sqrt(LengthSquared());
}

float Vector3::DistanceSquared(const Vector3& s, const Vector3& e)
{
    return s.operator-(e).Length();
}

float Vector3::Distance(const Vector3& s, const Vector3& e)
{
    return sqrt(DistanceSquared(s, e));
}

Vector3 Vector3::GetCrossProduct(const Vector3& other) const
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return Vector3((y1 * z2 - z1 * y2), (z1 * x2 - x1 * z2), (x1 * y2 - y1 * x2));
}

float Vector3::GetDotProduct(const Vector3& other) const
{
    const auto& [x1, y1, z1] = *this;
    const auto& [x2, y2, z2] = other;
    return x1 * x2 + y1 * y2 + z1 * z2;
}

Vector3& Vector3::operator=(const Vector3& other)
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3 Vector3::operator+(float bias) const
{
    return Vector3(X + bias, Y + bias, Z + bias);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-X, -Y, -Z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return operator+(other.operator-());
}

Vector3 Vector3::operator-(float bias) const
{
    return operator+(-bias);
}

Vector3 Vector3::operator*(float coeff) const
{
    return Vector3(X * coeff, Y * coeff, Z * coeff);
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(X * other.X, Y * other.Y, Z * other.Z);
}

Vector3 Vector3::operator/(float coeff) const
{
    return operator*(1.f / coeff);
}

Vector3 Vector3::operator/(const Vector3& other) const
{
    return operator*(Vector3(1.f / other.X, 1.f / other.Y, 1.f / other.Z));
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    return operator=(operator+(other));
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    return operator=(operator-(other));
}

Vector3& Vector3::operator*=(float coeff)
{
    return operator=(operator*(coeff));
}

Vector3& Vector3::operator*=(const Vector3& other)
{
    return operator=(operator*(other));
}

Vector3& Vector3::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

Vector3& Vector3::operator/=(const Vector3& other)
{
    return operator=(operator/(other));
}

bool Vector3::operator==(const Vector3& other) const
{
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !operator==(other);
}

VE_t& Vector3::operator[](int index)
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

const VE_t& Vector3::operator[](int index) const
{
    switch (static_cast<V3Idx>(index))
    {
    case V3Idx::X:
        return X;
    case V3Idx::Y:
        return Y;
    default:
    case V3Idx::Z:
        return Z;
    }
}

void Vector3::Map(VE_pred_t pred)
{
    operator=(Vector3(pred(X), pred(Y), pred(Z)));
}

Vector3 operator*(float coeff, const Vector3& ref)
{
    return ref.operator*(coeff);
}

string Vector3::GetAsString() const
{
    return "(" + to_string(X) + ", " + to_string(Y) + ", " + to_string(Z) + ")";
}

RDS_END