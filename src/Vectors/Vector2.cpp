#include "Vector2.h"

#include <cassert>
#include <cmath>

#include "RDS_CoreDefs.h"

RDS_BEGIN

using namespace std;

Vector2::Vector2()
    : m_x(Vector2::INIT_VAL)
    , m_y(Vector2::INIT_VAL)
{
    return;
}

Vector2::Vector2(VE_t x, VE_t y)
    : m_x(x)
    , m_y(y)
{
}

Vector2::Vector2(const Vector2& other)
    : m_x(other.m_x)
    , m_y(other.m_y)
{
}

Vector2::~Vector2()
{
}

float Vector2::GetX() const
{
    return m_x;
}

float Vector2::GetY() const
{
    return m_y;
}

void Vector2::SetX(VE_t x)
{
    m_x = x;
}

void Vector2::SetY(VE_t y)
{
    m_y = y;
}

void Vector2::SetXY(VE_t x, VE_t y)
{
    SetX(x);
    SetY(y);
}

inline void Vector2::Clear()
{
    operator=(Vector2(INIT_VAL, INIT_VAL));
}

inline bool Vector2::IsNearlyEqual(const Vector2& other, VE_t threshold) const
{
    return (abs(m_x - other.m_x) <= threshold && abs(m_y - other.m_y) <= threshold);
}

void Vector2::Normalize(VE_t threshold)
{
    const auto w = Length();

    /// @todo How to notify this?
    if (w < threshold)
        return;
    operator/=(w);
}

Vector2 Vector2::GetNormalized(VE_t threshold) const
{
    auto copy = *this;
    copy.Normalize(threshold);
    return copy;
}

float Vector2::SquareSum() const
{
    const auto x_sq_sum = pow(m_x, 2);
    const auto y_sq_sum = pow(m_y, 2);
    return x_sq_sum + y_sq_sum;
}

float Vector2::SquareSum(const Vector2& other) const
{
    const auto x_sq_sum = pow(m_x - other.m_x, 2);
    const auto y_sq_sum = pow(m_y - other.m_y, 2);
    return x_sq_sum + y_sq_sum;
}

float Vector2::Length() const
{
    return sqrt(SquareSum());
}

float Vector2::Distance(const Vector2& other) const
{
    return sqrt(SquareSum(other));
}

float Vector2::GetDotProduct(const Vector2& other) const
{
    const auto& [x1, y1] = *this;
    const auto& [x2, y2] = other;
    return (x1 * x2) + (y1 * y2);
}

Vector2& Vector2::operator=(const Vector2& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(m_x + other.m_x, m_y + other.m_y);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-m_x, -m_y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return operator+(other.operator-());
}

Vector2 Vector2::operator*(float coeff) const
{
    return Vector2(m_x * coeff, m_y * coeff);
}

Vector2 Vector2::operator/(float coeff) const
{
    assert(coeff != 0.0000000001);
    return operator*(1 / coeff);
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

Vector2& Vector2::operator/=(float coeff)
{
    return operator=(operator/(coeff));
}

bool Vector2::operator==(const Vector2& other)
{
    return m_x == other.m_x && m_y == other.m_y;
}

bool Vector2::operator!=(const Vector2& other)
{
    return !operator==(other);
}

Vector2 operator*(double coeff, const Vector2& ref)
{
    return ref.operator*(coeff);
}

std::string Vector2::GetAsString() const
{
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

RDS_END