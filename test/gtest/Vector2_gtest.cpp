#include <gtest/gtest.h>

#include <cmath>

#include "Vector2.h"

using namespace rds;
using namespace std;

const auto a = 2.f;
const auto b = 3.f;

TEST(Vector2_test, Length)
{

    static auto len_f = [](float a, float b) { return sqrt(pow(a, 2) + pow(b, 2)); };
    const auto vec = Vector2(a, b);

    EXPECT_FLOAT_EQ(len_f(a, b), vec.Length());
}

TEST(Vector2_test, LengthSquared)
{
    static auto len_sq_f = [](float a, float b) { return pow(a, 2) + pow(b, 2); };

    EXPECT_FLOAT_EQ(len_sq_f(a, b), Vector2(a, b).LengthSquared());
    EXPECT_FLOAT_EQ(len_sq_f(a, b), Vector2(b, a).LengthSquared());
    EXPECT_FLOAT_EQ(len_sq_f(b, a), Vector2(a, b).LengthSquared());
    EXPECT_FLOAT_EQ(len_sq_f(b, a), Vector2(b, a).LengthSquared());
}

TEST(Vector2_test, Distance)
{
    static auto dis_f = [](float x1, float y1, float x2, float y2)
    { return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); };

    EXPECT_FLOAT_EQ(dis_f(0.f, 0.f, 1.f, 1.f),
                    Vector2::Distance(Vector2(0.f), Vector2(1.f)));
    EXPECT_FLOAT_EQ(dis_f(1.f, 1.f, 0.f, 0.f),
                    Vector2::Distance(Vector2(0.f), Vector2(1.f)));
}

TEST(Vector2_test, DistanceSquared)
{
    static auto dis_sq_f = [](float x1, float y1, float x2, float y2)
    { return pow(x1 - x2, 2) + pow(y1 - y2, 2); };

    EXPECT_FLOAT_EQ(dis_sq_f(0.f, 0.f, 1.f, 1.f),
                    Vector2::DistanceSquared(Vector2(0.f), Vector2(1.f)));
    EXPECT_FLOAT_EQ(dis_sq_f(1.f, 1.f, 0.f, 0.f),
                    Vector2::DistanceSquared(Vector2(0.f), Vector2(1.f)));
}

TEST(Vector2_test, Map)
{
    static auto pred = [](float v) { return (v + 0.5f) * 2 + 3.f; };
    auto vec = Vector2(2.f, 3.f);
    vec.Map(pred);
    cout << vec.GetAsString() << endl;
}