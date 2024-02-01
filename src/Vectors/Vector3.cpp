#include "Vector3.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;
using VE_t = Vector3::VE_t;

Vector3::Vector3()
{
}

Vector3::Vector3(VE_t xyz)
    : m_x(xyz)
    , m_y(xyz)
    , m_z(xyz)
{
}

Vector3::Vector3(VE_t x, VE_t y, VE_t z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{
}

Vector3::Vector3(const Vector3& other)
    : m_x(other.m_x)
    , m_y(other.m_y)
    , m_z(other.m_z)
{
}

Vector3::~Vector3()
{
}

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
    return -ForwardVector();
}

const Vector3 Vector3::LeftVector()
{
    return -RightVector();
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
    return -UpVector();
}

Vector3 Vector3::GetAbs() const
{
    return Vector3(abs(m_x), abs(m_y), abs(m_z));
}

void Vector3::Set(const Vector3& other)
{
    operator=(other);
}

void Vector3::Set(VE_t x, VE_t y, VE_t z)
{
    Set(Vector3(x, y, z));
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
    return *this / len;
}

Vector3 Vector3::GetUnsafeNormal() const
{
    return *this / Length();
}

float Vector3::LengthSquared() const
{
    const auto x_sq_sum = pow(m_x, 2);
    const auto y_sq_sum = pow(m_y, 2);
    const auto z_sq_sum = pow(m_z, 2);
    return x_sq_sum + y_sq_sum + z_sq_sum;
}

float Vector3::Length() const
{
    return sqrt(LengthSquared());
}

float Vector3::DistanceSquared(const Vector3& start, const Vector3& end)
{
    const auto x_sq_sum = pow(start.m_x - end.m_x, 2);
    const auto y_sq_sum = pow(start.m_y - end.m_y, 2);
    const auto z_sq_sum = pow(start.m_z - end.m_z, 2);
    return x_sq_sum + y_sq_sum + z_sq_sum;
}

float Vector3::Distance(const Vector3& start, const Vector3& end)
{
    return sqrt(DistanceSquared(start, end));
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
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-m_x, -m_y, -m_z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return operator+(other.operator-());
}

Vector3 Vector3::operator-(float bias) const
{
    return Vector3(m_x - bias, m_y - bias, m_z - bias);
}

Vector3 Vector3::operator*(float coeff) const
{
    return Vector3(m_x * coeff, m_y * coeff, m_z * coeff);
}

Vector3 Vector3::operator/(float coeff) const
{
    assert(coeff != 0.0000000001);
    return operator*(1 / coeff);
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
    return operator=(Vector3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z));
}

Vector3& Vector3::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

Vector3& Vector3::operator/=(const Vector3& other)
{
    return operator=(Vector3(m_x / other.m_x, m_y / other.m_y, m_z / other.m_z));
}

bool Vector3::operator==(const Vector3& other) const
{
    return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !operator==(other);
}

VE_t& Vector3::operator[](int index)
{
    switch (static_cast<V3Idx>(index)) {
    case V3Idx::X:
        return m_x;
    case V3Idx::Y:
        return m_y;
    default:
    case V3Idx::Z:
        return m_z;
    }
}

const VE_t& Vector3::operator[](int index) const
{
    switch (static_cast<V3Idx>(index)) {
    case V3Idx::X:
        return m_x;
    case V3Idx::Y:
        return m_y;
    default:
    case V3Idx::Z:
        return m_z;
    }
}

Vector3 operator*(float coeff, const Vector3& ref)
{
    return ref.operator*(coeff);
}

string Vector3::GetAsString() const
{
    return "(" + to_string(m_x) + ", " + to_string(m_y) + ", " + to_string(m_z) + ")";
}

RDS_END