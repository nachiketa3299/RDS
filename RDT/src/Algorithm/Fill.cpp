#include "Algorithm.hpp"
#include "RDT_CoreDefs.h"

#include "List.hpp"
#include "Vector.hpp"
#include <vector>

RDT_BEGIN

using namespace rds;
using namespace std;

struct FillDummy
{
    int x{99};
};

TEST(__Fill, Basic)

{
    Vector<FillDummy> vec(10);
    List<FillDummy>   lst(10);

    Fill(++vec.Begin(), -- --vec.End(), FillDummy{1'000});
    Fill(++lst.Begin(), -- --lst.End(), FillDummy{1'000});
}

TEST(__FillN, Basic)
{
    Vector<FillDummy> vec(5);
    auto              it = FillN(vec.Begin(), 3, FillDummy{1'000});
}

RDT_END
