#ifndef RDS_FVECTOR3_H
#define RDS_FVECTOR3_H

#include <functional>
#include <string>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Simple FVector3 class containing 3 floats.
class FVector3
{
public:
    /// @enum V3Idx
    /// @brief Represents index of each component
    enum class V3Idx
    {
        X   = 0,
        Y   = 1,
        Z   = 2,
        MAX = 3
    };

public:
    using Val_t     = float;
    using VE_pred_t = std::function<float(float)>;

public:
    /// @brief Default Constructor(no initialization).
    FVector3();
    /// @brief Constructor initializing all components to a single float value.
    FVector3(Val_t xyz);
    /// @brief Constructor using initial values for each components.
    FVector3(Val_t x, Val_t y, Val_t z);
    /// @brief Copy Constructor.
    FVector3(const FVector3& other);
    /// @brief Destructor.
    ~FVector3();

public:
    /// @brief Get (1.0, 0.0, 0.0) vector.
    static const FVector3 XAxisVector();
    /// @brief Get (0.0, 1.0, 0.0) vector.
    static const FVector3 YAxisVector();
    /// @brief Get (0.0, 0.0, 1.0) vector.
    static const FVector3 ZAxisVector();
    /// @brief Get (0.0, 0.0, 0.0) vector.
    static const FVector3 ZeroVector();
    /// @brief Get (1.0, 0.0, 0.0) vector(Unreal-coord).
    static const FVector3 ForwardVector();
    /// @brief Get (-1.0, 0.0, 0.0) vector(Unreal-coord).
    static const FVector3 BackwardVector();
    /// @brief Get (0.0, -1.0, 0.0) vector(Unreal-coord).
    static const FVector3 LeftVector();
    /// @brief Get (0.0, 1.0, 0.0) vector(Unreal-coord).
    static const FVector3 RightVector();
    /// @brief Get (0.0, 0.0, 1.0) vector(Unreal-coord).
    static const FVector3 UpVector();
    /// @brief Get (0.0, 0.0, -1.0) vector(Unreal-coord).
    static const FVector3 DownVector();

public:
    /// @brief Get a copy of this vector with absolute value of each component
    FVector3 GetAbs() const;

public:
    /// @brief Set this vector's component with other vector.
    void Set(const FVector3& other);
    /// @brief Set this vector's component with each parameters.
    void Set(Val_t x, Val_t y, Val_t z);
    /// @brief Set this vector to zero vector
    void Clear();

public:
    /// @brief Gets a normalized copy of vector, checking it is safe to do so based on
    /// length. Returns zero vector if vector length is too small to safely normalize.
    /// @param tolerance Vector's minimum squared length
    /// @return A copy of normalized vector if safe, otherwise (0.0, 0.0, 0.0)
    FVector3 GetSafeNormal(float tolerance) const;
    /// @brief Gets a normazlied copy of vector, without checking for zero length
    FVector3 GetUnsafeNormal() const;

public:
    /// @brief Get squared length of this vector
    float        LengthSquared() const;
    /// @brief Get length of this vector
    float        Length() const;
    /// @brief Get squared distance between two vectors
    static float DistanceSquared(const FVector3& start, const FVector3& end);
    /// @brief Get distance between two vectors
    static float Distance(const FVector3& start, const FVector3& end);

public:
    /// @brief Get the result of cross product of this and other.
    FVector3 GetCrossProduct(const FVector3& other) const;
    /// @brief Get the result of this product of this and other.
    float    GetDotProduct(const FVector3& other) const;

public:
    FVector3&    operator=(const FVector3& other);
    /// @brief Get the result of coponent-wise addition of this by another vector.
    FVector3     operator+(const FVector3& other) const;
    /// @brief Get the result of adding bias from each component of this vector.
    FVector3     operator+(float bias) const;
    /// @brief Get a negate copy of this vector
    FVector3     operator-() const;
    /// @brief Get the result of coponent-wise subtraction of this by another vector.
    FVector3     operator-(const FVector3& other) const;
    /// @brief Get the result of subtracting bias from each component of this vector.
    FVector3     operator-(float bias) const;
    /// @brief Get the result of scaling this vector by multiplying each component with
    /// coefficient.
    FVector3     operator*(float coeff) const;
    /// @brief Get the result of coponent-wise multiplication of this by another vector.
    FVector3     operator*(const FVector3& other) const;
    /// @brief Get the result of dividing each component by coefficient.
    /// @todo 0-divide case
    FVector3     operator/(float coeff) const;
    /// @brief Get the result of coponent-wise division of this by another vector.
    FVector3     operator/(const FVector3& other) const;
    /// @brief Adds anothre vector to this using component-wise addition.
    FVector3&    operator+=(const FVector3& other);
    /// @brief Subtracts another vector to this using component-wise subtraction.
    FVector3&    operator-=(const FVector3& other);
    /// @brief Scales this vector's each component with coefficient.
    FVector3&    operator*=(float coeff);
    /// @brief Multiplies this vector with another vector, using component-wise
    /// multiplication.
    FVector3&    operator*=(const FVector3& other);
    /// @brief Divides this vector's each component with coefficient.
    /// @todo 0-divide case
    FVector3&    operator/=(float coeff);
    /// @brief Divides this vector with another vector, using component-wise divide.
    /// @todo 0-divide case
    FVector3&    operator/=(const FVector3& other);
    /// @brief Check against another vector for eqaulity.
    bool         operator==(const FVector3& other) const;
    /// @brief Check against another vector for ineqaulity.
    bool         operator!=(const FVector3& other) const;
    /// @brief Get l-value of  @p index th component of this vector. @p index is in
    /// range [0, 3). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V3Idx .
    Val_t&       operator[](int index);
    /// @brief Get const l-value of  @p index th component of this vector. @p index is
    /// in range [0, 3). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V3Idx .
    const Val_t& operator[](int index) const;
    /// @brief Apply @p pred to all component.
    void         Map(VE_pred_t pred);

public:
    friend FVector3 operator*(float coeff, const FVector3& ref);

public:
    std::string GetAsString() const;

public:
    Val_t X;
    Val_t Y;
    Val_t Z;
};

RDS_END

#endif // RDS_VECTOR3_H