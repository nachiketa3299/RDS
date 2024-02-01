#include "Vector2.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;
using VE_t = Vector2::VE_t;
using VE_pred_t = Vector2::VE_pred_t;

Vector2::Vector2()
{}

Vector2::Vector2(VE_t xy)
    : X(xy)
    , Y(xy)
{}

Vector2::Vector2(VE_t x, VE_t y)
    : X(x)
    , Y(y)
{}

Vector2::Vector2(const Vector2& other)
    : X(other.X)
    , Y(other.Y)
{}

Vector2::~Vector2()
{}

const Vector2 Vector2::XAxisVector()
{
    return Vector2(1.f, 0.f);
}

const Vector2 Vector2::YAxisVector()
{
    return Vector2(0.f, 1.f);
}

const Vector2 Vector2::ZeroVector()
{
    return Vector2(0.f, 0.f);
}

Vector2 Vector2::GetAbs() const
{
    return Vector2(abs(X), abs(Y));
}

void Vector2::Set(const Vector2& other)
{
    operator=(other);
}

void Vector2::Set(VE_t x, VE_t y)
{
    operator=(Vector2(x, y));
}

inline void Vector2::Clear()
{
    operator=(Vector2(0, 0));
}

float Vector2::LengthSquared() const
{
    return pow(X, 2) + pow(Y, 2);
}

float Vector2::Length() const
{
    return sqrt(LengthSquared());
}

float Vector2::DistanceSquared(const Vector2& s, const Vector2& e)
{
    return pow(s.X - e.X, 2) + pow(s.Y - e.Y, 2);
}

float Vector2::Distance(const Vector2& start, const Vector2& end)
{
    return sqrt(DistanceSquared(start, end));
}

Vector2 Vector2::GetSafeNormal(float tolerance) const
{
    const auto len = Length();
    if (len <= tolerance)
        return ZeroVector();
    return operator/(len);
}

Vector2 Vector2::GetUnsafeNormal() const
{
    return operator/(Length());
}

float Vector2::GetDotProduct(const Vector2& other) const
{
    const auto& [x1, y1] = *this;
    const auto& [x2, y2] = other;
    return (x1 * x2) + (y1 * y2);
}

Vector2& Vector2::operator=(const Vector2& other)
{
    X = other.X;
    Y = other.Y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator+(float bias) const
{
    return Vector2(X + bias, Y + bias);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-X, -Y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return operator+(other.operator-());
}

Vector2 Vector2::operator-(float bias) const
{
    return operator+(-bias);
}

Vector2 Vector2::operator*(float coeff) const
{
    return Vector2(X * coeff, Y * coeff);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
    return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator/(float coeff) const
{
    return operator*(1.f / coeff);
}

Vector2 Vector2::operator/(const Vector2& other) const
{
    return operator*(Vector2(1.f / other.X, 1.f / other.Y));
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    return operator=(operator+(other));
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    return operator=(operator-(other));
}

Vector2& Vector2::operator*=(float coeff)
{
    return operator=(operator*(coeff));
}

Vector2& Vector2::operator*=(const Vector2& other)
{
    return operator=(operator*(other));
}

Vector2& Vector2::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

Vector2& Vector2::operator/=(const Vector2& other)
{
    return operator=(operator/(other));
}

bool Vector2::operator==(const Vector2& other)
{
    return X == other.X && Y == other.Y;
}

bool Vector2::operator!=(const Vector2& other)
{
    return !operator==(other);
}

VE_t& Vector2::operator[](int index)
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

const VE_t& Vector2::operator[](int index) const
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

void Vector2::Map(VE_pred_t pred)
{
    operator=(Vector2(pred(X), pred(Y)));
}

Vector2 operator*(float coeff, const Vector2& ref)
{
    return ref.operator*(coeff);
}

string Vector2::GetAsString() const
{
    return "(" + to_string(X) + ", " + to_string(Y) + ")";
}

RDS_END
