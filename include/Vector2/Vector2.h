#ifndef RDS_VECTOR2_H
#define RDS_VECTOR2_H

#include <functional>
#include <string>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Simple Vector2 class containing 2 floats
class Vector2
{
public:
    using VE_t = float;
    using VE_pred_t = std::function<float(float)>;
    enum class V2Idx
    {
        X = 0,
        Y = 1,
        MAX = 2
    };

public:
    /// @brief Default Constructor(no initialization).
    Vector2();
    /// @brief Constructor initializing all components to a single float value.
    Vector2(VE_t xy);
    /// @brief Constructor using initial values for each components.
    Vector2(VE_t x, VE_t y);
    /// @brief  Copy Constructor.
    Vector2(const Vector2& other);
    /// @brief Destructor.
    ~Vector2();

public:
    /// @brief Get (1.0, 0.0) vector.
    static const Vector2 XAxisVector();
    /// @brief Get (0.0, 1.0) vector.
    static const Vector2 YAxisVector();
    /// @brief Get (0.0, 0.0) vector.
    static const Vector2 ZeroVector();

public:
    /// @brief Get a copy of this vector with absolute value of each component
    Vector2 GetAbs() const;

public:
    /// @brief Set this vector's component with other vector.
    void Set(const Vector2& other);
    /// @brief Set this vector's component with each parameters.
    void Set(VE_t x, VE_t y);
    /// @brief Set this vector to zero vector
    void Clear();

public:
    /// @brief Gets a normalized copy of vector, checking it is safe to do so based on
    /// length. Returns zero vector if vector length is too small to safely normalize.
    /// @param tolerance Vector's minimum squared length
    /// @return A copy of normalized vector if safe, otherwise (0.0, 0.0)
    Vector2 GetSafeNormal(float tolerance) const;
    /// @brief Gets a normazlied copy of vector, without checking for zero length
    Vector2 GetUnsafeNormal() const;

public:
    /// @brief Get the result of this product of this and other.
    float GetDotProduct(const Vector2& other) const;

public:
    /// @brief Get squared length of this vector
    float LengthSquared() const;
    /// @brief Get length of this vector
    float Length() const;
    /// @brief Get squared distance between two vectors
    static float DistanceSquared(const Vector2& start, const Vector2& end);
    /// @brief Get distance between two vectors
    static float Distance(const Vector2& start, const Vector2& end);

public:
    Vector2& operator=(const Vector2& other);
    /// @brief Get the result of coponent-wise addition of this by another vector.
    Vector2 operator+(const Vector2& other) const;
    /// @brief Get the result of adding bias from each component of this vector.
    Vector2 operator+(float bias) const;
    /// @brief Get a negate copy of this vector
    Vector2 operator-() const;
    /// @brief Get the result of adding bias from each component of this vector.
    Vector2 operator-(const Vector2& other) const;
    /// @brief Get the result of subtracting bias from each component of this vector.
    Vector2 operator-(float bias) const;
    /// @brief Get the result of scaling this vector by multiplying each component with
    /// coefficient.
    Vector2 operator*(float coeff) const;
    /// @brief Get the result of coponent-wise multiplication of this by another vector.
    Vector2 operator*(const Vector2& other) const;
    /// @brief Get the result of dividing each component by coefficient.
    /// @todo 0-divide case
    Vector2 operator/(float coeff) const;
    /// @brief Get the result of coponent-wise division of this by another vector.
    Vector2 operator/(const Vector2& other) const;
    /// @brief Adds anothre vector to this using component-wise addition.
    Vector2& operator+=(const Vector2& other);
    /// @brief Subtracts another vector to this using component-wise subtraction.
    Vector2& operator-=(const Vector2& other);
    /// @brief Scales this vector's each component with coefficient.
    Vector2& operator*=(float coeff);
    /// @brief Multiplies this vector with another vector, using component-wise
    /// multiplication.
    Vector2& operator*=(const Vector2& other);
    /// @brief Divides this vector's each component with coefficient.
    /// @todo 0-divide case
    Vector2& operator/=(float coeff);
    /// @brief Divides this vector with another vector, using component-wise divide.
    /// @todo 0-divide case
    Vector2& operator/=(const Vector2& other);
    /// @brief Check against another vector for eqaulity.
    bool operator==(const Vector2& other);
    /// @brief Check against another vector for ineqaulity.
    bool operator!=(const Vector2& other);
    /// @brief Get l-value of  @p index th component of this vector.
    /// @todo process for default case
    VE_t& operator[](int index);
    /// @brief Get const l-value of  @p index th component of this vector.
    const VE_t& operator[](int index) const;
    /// @brief Apply @p pred to all component.
    void Map(VE_pred_t pred);

public:
    friend Vector2 operator*(float coeff, const Vector2& ref);

public:
    std::string GetAsString() const;

private:
    VE_t X;
    VE_t Y;
};

RDS_END

#endif // RDS_VECTOR2_H