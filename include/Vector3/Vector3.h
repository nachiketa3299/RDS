#ifndef RDS_VECTOR3_H
#define RDS_VECTOR3_H

#include <functional>
#include <string>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Simple Vector3 class containing 3 floats.
class Vector3
{
public:
    /// @brief Enum class for notating vector indices.
    enum class V3Idx
    {
        X = 0,
        Y = 1,
        Z = 2,
        MAX = 3
    };

public:
    using VE_t = float;
    using VE_pred_t = std::function<float(float)>;

public:
    /// @brief Default Constructor(no initialization).
    Vector3();
    /// @brief Constructor initializing all components to a single float value.
    Vector3(VE_t xyz);
    /// @brief Constructor using initial values for each components.
    Vector3(VE_t x, VE_t y, VE_t z);
    /// @brief Copy Constructor.
    Vector3(const Vector3& other);
    /// @brief Destructor.
    ~Vector3();

public:
    /// @brief Get (1.0, 0.0, 0.0) vector.
    static const Vector3 XAxisVector();
    /// @brief Get (0.0, 1.0, 0.0) vector.
    static const Vector3 YAxisVector();
    /// @brief Get (0.0, 0.0, 1.0) vector.
    static const Vector3 ZAxisVector();
    /// @brief Get (0.0, 0.0, 0.0) vector.
    static const Vector3 ZeroVector();
    /// @brief Get (1.0, 0.0, 0.0) vector(Unreal-coord).
    static const Vector3 ForwardVector();
    /// @brief Get (-1.0, 0.0, 0.0) vector(Unreal-coord).
    static const Vector3 BackwardVector();
    /// @brief Get (0.0, -1.0, 0.0) vector(Unreal-coord).
    static const Vector3 LeftVector();
    /// @brief Get (0.0, 1.0, 0.0) vector(Unreal-coord).
    static const Vector3 RightVector();
    /// @brief Get (0.0, 0.0, 1.0) vector(Unreal-coord).
    static const Vector3 UpVector();
    /// @brief Get (0.0, 0.0, -1.0) vector(Unreal-coord).
    static const Vector3 DownVector();

public:
    /// @brief Get a copy of this vector with absolute value of each component
    Vector3 GetAbs() const;

public:
    /// @brief Set this vector's component with other vector.
    void Set(const Vector3& other);
    /// @brief Set this vector's component with each parameters.
    void Set(VE_t x, VE_t y, VE_t z);
    /// @brief Set this vector to zero vector
    void Clear();

public:
    /// @brief Gets a normalized copy of vector, checking it is safe to do so based on
    /// length. Returns zero vector if vector length is too small to safely normalize.
    /// @param tolerance Vector's minimum squared length
    /// @return A copy of normalized vector if safe, otherwise (0.0, 0.0, 0.0)
    Vector3 GetSafeNormal(float tolerance) const;
    /// @brief Gets a normazlied copy of vector, without checking for zero length
    Vector3 GetUnsafeNormal() const;

public:
    /// @brief Get squared length of this vector
    float LengthSquared() const;
    /// @brief Get length of this vector
    float Length() const;
    /// @brief Get squared distance between two vectors
    static float DistanceSquared(const Vector3& start, const Vector3& end);
    /// @brief Get distance between two vectors
    static float Distance(const Vector3& start, const Vector3& end);

public:
    /// @brief Get the result of cross product of this and other.
    Vector3 GetCrossProduct(const Vector3& other) const;
    /// @brief Get the result of this product of this and other.
    float GetDotProduct(const Vector3& other) const;

public:
    Vector3& operator=(const Vector3& other);
    /// @brief Get the result of coponent-wise addition of this by another vector.
    Vector3 operator+(const Vector3& other) const;
    /// @brief Get the result of adding bias from each component of this vector.
    Vector3 operator+(float bias) const;
    /// @brief Get a negate copy of this vector
    Vector3 operator-() const;
    /// @brief Get the result of coponent-wise subtraction of this by another vector.
    Vector3 operator-(const Vector3& other) const;
    /// @brief Get the result of subtracting bias from each component of this vector.
    Vector3 operator-(float bias) const;
    /// @brief Get the result of scaling this vector by multiplying each component with
    /// coefficient.
    Vector3 operator*(float coeff) const;
    /// @brief Get the result of coponent-wise multiplication of this by another vector.
    Vector3 operator*(const Vector3& other) const;
    /// @brief Get the result of dividing each component by coefficient.
    /// @todo 0-divide case
    Vector3 operator/(float coeff) const;
    /// @brief Get the result of coponent-wise division of this by another vector.
    Vector3 operator/(const Vector3& other) const;
    /// @brief Adds anothre vector to this using component-wise addition.
    Vector3& operator+=(const Vector3& other);
    /// @brief Subtracts another vector to this using component-wise subtraction.
    Vector3& operator-=(const Vector3& other);
    /// @brief Scales this vector's each component with coefficient.
    Vector3& operator*=(float coeff);
    /// @brief Multiplies this vector with another vector, using component-wise
    /// multiplication.
    Vector3& operator*=(const Vector3& other);
    /// @brief Divides this vector's each component with coefficient.
    /// @todo 0-divide case
    Vector3& operator/=(float coeff);
    /// @brief Divides this vector with another vector, using component-wise divide.
    /// @todo 0-divide case
    Vector3& operator/=(const Vector3& other);
    /// @brief Check against another vector for eqaulity.
    bool operator==(const Vector3& other) const;
    /// @brief Check against another vector for ineqaulity.
    bool operator!=(const Vector3& other) const;
    /// @brief Get l-value of  @p index th component of this vector. @p index is in
    /// range [0, 3). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V3Idx .
    VE_t& operator[](int index);
    /// @brief Get const l-value of  @p index th component of this vector. @p index is
    /// in range [0, 3). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V3Idx .
    const VE_t& operator[](int index) const;
    /// @brief Apply @p pred to all component.
    void Map(VE_pred_t pred);

public:
    friend Vector3 operator*(float coeff, const Vector3& ref);

public:
    std::string GetAsString() const;

public:
    VE_t X;
    VE_t Y;
    VE_t Z;
};

RDS_END

#endif // RDS_VECTOR3_H