#ifndef RDS_FVECTOR2_H
#define RDS_FVECTOR2_H

#include <functional>
#include <string>

#include "RDS_CoreDefs.h"

RDS_BEGIN

/// @brief Simple FVector2 class containing 2 floats
class FVector2
{
public:
    using Val_t     = float;
    using VE_pred_t = std::function<float(float)>;
    /// @enum V2Idx
    /// @brief Represents index of each component
    enum class V2Idx
    {
        X   = 0,
        Y   = 1,
        MAX = 2
    };

public:
    /// @brief Default Constructor(no initialization).
    FVector2();
    /// @brief Constructor initializing all components to a single float value.
    FVector2(Val_t xy);
    /// @brief Constructor using initial values for each components.
    FVector2(Val_t x, Val_t y);
    /// @brief  Copy Constructor.
    FVector2(const FVector2& other);
    /// @brief Destructor.
    ~FVector2();

public:
    /// @brief Get (1.0, 0.0) vector.
    static const FVector2 XAxisVector();
    /// @brief Get (0.0, 1.0) vector.
    static const FVector2 YAxisVector();
    /// @brief Get (0.0, 0.0) vector.
    static const FVector2 ZeroVector();

public:
    /// @brief Get a copy of this vector with absolute value of each component
    FVector2 GetAbs() const;

public:
    /// @brief Set this vector's component with other vector.
    void Set(const FVector2& other);
    /// @brief Set this vector's component with each parameters.
    void Set(Val_t x, Val_t y);
    /// @brief Set this vector to zero vector
    void Clear();

public:
    /// @brief Gets a normalized copy of vector, checking it is safe to do so based on
    /// length. Returns zero vector if vector length is too small to safely normalize.
    /// @param tolerance Vector's minimum squared length
    /// @return A copy of normalized vector if safe, otherwise (0.0, 0.0)
    FVector2 GetSafeNormal(float tolerance) const;
    /// @brief Gets a normazlied copy of vector, without checking for zero length
    FVector2 GetUnsafeNormal() const;

public:
    /// @brief Get the result of this product of this and other.
    float GetDotProduct(const FVector2& other) const;

public:
    /// @brief Get squared length of this vector
    float        LengthSquared() const;
    /// @brief Get length of this vector
    float        Length() const;
    /// @brief Get squared distance between two vectors
    static float DistanceSquared(const FVector2& start, const FVector2& end);
    /// @brief Get distance between two vectors
    static float Distance(const FVector2& start, const FVector2& end);

public:
    FVector2&    operator=(const FVector2& other);
    /// @brief Get the result of coponent-wise addition of this by another vector.
    FVector2     operator+(const FVector2& other) const;
    /// @brief Get the result of adding bias from each component of this vector.
    FVector2     operator+(float bias) const;
    /// @brief Get a negate copy of this vector
    FVector2     operator-() const;
    /// @brief Get the result of adding bias from each component of this vector.
    FVector2     operator-(const FVector2& other) const;
    /// @brief Get the result of subtracting bias from each component of this vector.
    FVector2     operator-(float bias) const;
    /// @brief Get the result of scaling this vector by multiplying each component with
    /// coefficient.
    FVector2     operator*(float coeff) const;
    /// @brief Get the result of coponent-wise multiplication of this by another vector.
    FVector2     operator*(const FVector2& other) const;
    /// @brief Get the result of dividing each component by coefficient.
    /// @todo 0-divide case
    FVector2     operator/(float coeff) const;
    /// @brief Get the result of coponent-wise division of this by another vector.
    FVector2     operator/(const FVector2& other) const;
    /// @brief Adds anothre vector to this using component-wise addition.
    FVector2&    operator+=(const FVector2& other);
    /// @brief Subtracts another vector to this using component-wise subtraction.
    FVector2&    operator-=(const FVector2& other);
    /// @brief Scales this vector's each component with coefficient.
    FVector2&    operator*=(float coeff);
    /// @brief Multiplies this vector with another vector, using component-wise
    /// multiplication.
    FVector2&    operator*=(const FVector2& other);
    /// @brief Divides this vector's each component with coefficient.
    /// @todo 0-divide case
    FVector2&    operator/=(float coeff);
    /// @brief Divides this vector with another vector, using component-wise divide.
    /// @todo 0-divide case
    FVector2&    operator/=(const FVector2& other);
    /// @brief Check against another vector for eqaulity.
    bool         operator==(const FVector2& other);
    /// @brief Check against another vector for ineqaulity.
    bool         operator!=(const FVector2& other);
    /// @brief Get l-value of  @p index th component of this vector. @p index is in
    /// range [0, 2). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V2Idx .
    Val_t&       operator[](int index);
    /// @brief Get const l-value of  @p index th component of this vector. @p index is
    /// in range [0, 2). If @p index is out of bound, it is treated as 0. Internally @p
    /// index is treated as @ref V2Idx .
    const Val_t& operator[](int index) const;
    /// @brief Apply @p pred to all component.
    void         Map(VE_pred_t pred);

public:
    friend FVector2 operator*(float coeff, const FVector2& ref);

public:
    std::string GetAsString() const;

private:
    Val_t X;
    Val_t Y;
};

RDS_END

#endif // RDS_VECTOR2_H