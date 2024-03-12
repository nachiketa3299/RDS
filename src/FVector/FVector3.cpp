#include "FVector3.h"
#include <cmath>

namespace rds
{

FVector3::FVector3(const float& x, const float& y, const float& z)
    : _data{x, y, z}
{}

FVector3::FVector3(const float& xyz)
    : FVector3(xyz, xyz, xyz)
{}

auto FVector3::operator-() const -> FVector3
{
    return FVector3(-x, -y, -z);
}

auto FVector3::operator+(const FVector3& other) const -> FVector3
{
    return FVector3(x + other.x, y + other.y, z + other.z);
}

auto FVector3::operator+(const float& bias) const -> FVector3
{
    return FVector3(x + bias, y + bias, z + bias);
}

auto FVector3::operator-(const FVector3& other) const -> FVector3
{
    return operator+(other.operator-());
}

auto FVector3::operator-(const float& bias) const -> FVector3
{
    return operator+(-bias);
}

auto operator*(const FVector3& vec, const float& coeff) -> FVector3
{
    return FVector3(vec.x * coeff, vec.y * coeff, vec.z * coeff);
}

auto operator*(const float& coeff, const FVector3& vec) -> FVector3
{
    return operator*(vec, coeff);
}

auto FVector3::operator/(const float& coeff) const -> FVector3
{
    return operator*(*this, 1.0f / coeff);
}

auto FVector3::operator==(const FVector3& other) const -> bool
{
    return x == other.x && y == other.y && z == other.z;
}

auto FVector3::operator!=(const FVector3& other) const -> bool
{
    return !operator==(other);
}

auto FVector3::operator+=(const FVector3& other) -> FVector3&
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

auto FVector3::operator-=(const FVector3& other) -> FVector3&
{
    return operator+=(other.operator-());
}

auto FVector3::operator*=(const float& coeff) -> FVector3&
{
    x *= coeff;
    y *= coeff;
    z *= coeff;
    return *this;
}

auto FVector3::operator/=(const float& coeff) -> FVector3&
{
    return operator*=(1.0f / coeff);
}

auto FVector3::operator[](const int& index) const -> const float&
{
    return _data[index];
}

auto FVector3::operator[](const int& index) -> float&
{
    return const_cast<float&>(
        static_cast<const FVector3&>(*this).operator[](index));
}

auto FVector3::Clear() -> void
{
    x = y = z = 0.0f;
}

auto FVector3::Absolute() -> FVector3&
{
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);
    return *this;
}

auto FVector3::GetAbsoluted() const -> FVector3
{
    return FVector3(std::abs(x), std::abs(y), std::abs(z));
}

auto FVector3::Dot(const FVector3& other) const -> float
{
    return x * other.x + y * other.y + z * other.z;
}

auto FVector3::Cross(const FVector3& other) const -> FVector3
{
    return FVector3(y * other.z - z * other.y, z * other.x - x * other.z,
                    x * other.y - y * other.x);
}

auto FVector3::LengthSquared() const -> float
{
    return Dot(*this);
}

auto FVector3::Length() const -> float
{
    return std::sqrt(LengthSquared());
}

auto FVector3::DistanceSquared(const FVector3& other) const -> float
{
    return (*this - other).LengthSquared();
}

auto FVector3::Distance(const FVector3& other) const -> float
{
    return std::sqrt(DistanceSquared(other));
}

auto FVector3::Normalize_Unsafe() -> void
{
    operator/=(Length());
}

auto FVector3::Normalize() -> void
{
    if (Length() == 0.0f)
        return;
    Normalize_Unsafe();
}

auto FVector3::GetNormalized_Unsafe() const -> FVector3
{
    return operator/(Length());
}

auto FVector3::GetNormalized() const -> FVector3
{
    if (Length() == 0.0f)
        return *this;
    return GetNormalized_Unsafe();
}

auto FVector3::IsNormalized() const -> bool
{
    return Length() == 1.0f;
}

} // namespace rds