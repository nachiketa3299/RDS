#ifndef RDS_VECTOR2_H
#define RDS_VECTOR2_H

#include <string>

#include "RDS_CoreDefs.h"
#include "Vector.h"

RDS_BEGIN

class Vector2: public Vector
{
public:
    Vector2();
    Vector2(VE_t x, VE_t y);
    Vector2(const Vector2& other);
    ~Vector2();

public:
    inline float GetX() const;
    inline float GetY() const;

public:
    bool IsNearlyEqual(const Vector2& other,
                       VE_t threshold = DEFAULT_EQUALITY_THRESHOLD) const;

public:
    inline void SetX(VE_t x);
    inline void SetY(VE_t y);
    inline void SetXY(VE_t x, VE_t y);
    inline void Clear();

public:
    void Normalize(VE_t threshold = DEFAULT_NORMALIZE_THRESHOLD);
    Vector2 GetNormalized(VE_t threshold = DEFAULT_NORMALIZE_THRESHOLD) const;

public:
    float SquareSum() const;
    float SquareSum(const Vector2& other) const;
    float Length() const;
    float Distance(const Vector2& other) const;

public:
    float GetDotProduct(const Vector2& other) const;

public:
    Vector2& operator=(const Vector2& other);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-() const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float coeff) const;
    Vector2 operator/(float coeff) const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float coeff);
    Vector2& operator/=(float coeff);
    bool operator==(const Vector2& other);
    bool operator!=(const Vector2& other);

public:
    friend Vector2 operator*(float coeff, const Vector2& ref);

public:
    std::string GetAsString() const;

private:
    VE_t m_x;
    VE_t m_y;
};

RDS_END

#endif // RDS_VECTOR2_H