#include "Algorithm.hpp"
#include "RDT_CoreDefs.h"

#include "List.hpp"
#include "Vector.hpp"
#include <type_traits>
#include <utility>

RDT_BEGIN

using namespace rds;
using namespace std;

// TODO 아주 기본적인 테스트만 작성했음. 더 많은 예시가 필요함

struct Dummy
{
    Dummy() = default;

    Dummy(const int& x, const int& y)
        : x(x)
        , y(y)
    {}

    auto operator==(const Dummy& other) const -> bool
    {
        return x == other.x && y == other.y;
    }

    int x, y;
};

struct Dummy_NoOpOv: Dummy
{
    Dummy_NoOpOv() = default;

    Dummy_NoOpOv(const int& x, const int& y)
        : Dummy(x, y)
    {}
};

struct Dummy_OpOv: Dummy
{
    Dummy_OpOv() = default;

    Dummy_OpOv(const int& x, const int& y)
        : Dummy(x, y)
    {}

    auto operator<(const Dummy_OpOv& other) const -> bool
    {
        return x < other.x;
    }

    auto operator>(const Dummy_OpOv& other) const -> bool
    {
        return x > other.x;
    }
};

TEST(__MinElement, Basic)

{
    List<int> li     = {99, 99, 0, 99, 99};
    int       arr[3] = {99, 0, 99};

    auto it_arr_min = MinElement(arr, arr + 3);
    auto it_li_min  = MinElement(li.CBegin(), li.CEnd());
    EXPECT_EQ(*it_arr_min, *it_li_min);
}

TEST(__MaxElement, Basic)
{
    List<int> li     = {0, 0, 99, 0, 0};
    int       arr[3] = {0, 99, 0};

    auto it_arr_max = MaxElement(arr, arr + 3);
    auto it_li_max  = MaxElement(li.CBegin(), li.CEnd());
    EXPECT_EQ(*it_arr_max, *it_li_max);
}

TEST(__MinElement, Object_NoOpOv)
{
    const List<Dummy_NoOpOv> li = {
        {1,   2},
        {2,   1},
        {-99, 1},
        {2,   2}
    };

    const Dummy_NoOpOv arr[3] = {
        {1,   2},
        {-99, 1},
        {2,   1}
    };

    auto comp = [](const Dummy_NoOpOv& l, const Dummy_NoOpOv& r)
    { return l.x < l.y; };

    auto it_li_min  = MinElement(li.CBegin(), li.CEnd(), comp);
    auto it_arr_min = MinElement(arr, arr + 3, comp);

    EXPECT_EQ(*it_arr_min, *it_li_min);
}

TEST(__MinElement, Object_OpOv)
{
    const List<Dummy_OpOv> li = {
        {1,   2},
        {2,   1},
        {-99, 1},
        {2,   2}
    };

    const Dummy_OpOv arr[3] = {
        {1,   2},
        {-99, 1},
        {2,   1}
    };

    auto it_li_min  = MinElement(li.CBegin(), li.CEnd());
    auto it_arr_min = MinElement(arr, arr + 3);

    EXPECT_EQ(*it_arr_min, *it_li_min);
}

TEST(__MinMax, Basic)
{
    EXPECT_EQ(Min(3, 4), 3);
    EXPECT_EQ(Max(3, 4), 4);
}

TEST(__MinMax, Object_NoOpOv)
{
    auto min_comp = [](const Dummy_NoOpOv& l, const Dummy_NoOpOv& r)
    { return l.x < l.y; };
    EXPECT_EQ(Min(Dummy_NoOpOv{1, 2}, Dummy_NoOpOv{99, 1}, min_comp),
              (Dummy_NoOpOv{1, 2}));

    auto max_comp = [](const Dummy_NoOpOv& l, const Dummy_NoOpOv& r) -> bool
    { return l.x > l.y; };

    EXPECT_EQ(Max(Dummy_NoOpOv{1, 2}, Dummy_NoOpOv{99, 1}, max_comp),
              (Dummy_NoOpOv{99, 1}));
}

TEST(__MinMax, Object_OpOv)
{
    EXPECT_EQ(Min(Dummy_OpOv{1, 2}, Dummy_OpOv{99, 1}), (Dummy_OpOv{1, 2}));

    EXPECT_EQ(Max(Dummy_OpOv{1, 2}, Dummy_OpOv{99, 1}), (Dummy_OpOv{99, 1}));
}

RDT_END