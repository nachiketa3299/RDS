/// @file Capacity.cpp

#include "RDT_CoreDefs.h"

#include "List.hpp"

RDT_BEGIN

using namespace rds;
using namespace std;

/**
 * 다른 테스트에서 이미 Capacity에 관한 테스트를 수행하므로, 여기에서는
 * 기본적인 테스트만 수행한다.
 */

/** @brief Size() const -> Size_t */
TEST(Size, __void)
{
    { // Nallocator
        const size_t          size = 10;
        initializer_list<int> il   = {1, 2, 3};
        { // Default Empty Size
            List<int, Nallocator> li;
            EXPECT_EQ(li.Size(), 0);
        }
        { // Size initialization
            List<int, Nallocator> li(size);
            List<int, Nallocator> li_a(size, 10);
            EXPECT_EQ(li.Size(), size);
            EXPECT_EQ(li_a.Size(), 10);
        }
        { // init_list
            List<int, Nallocator> li(il);
            EXPECT_EQ(li.Size(), il.size());
        }
    }
}

/** @brief Empty() const -> bool */
TEST(Empty, __void)
{
    initializer_list<int> il = {1, 2, 3};
    {     // Nallocator
        { // 비어 있었던 경우
            List<int, Nallocator> li;
            EXPECT_TRUE(li.Empty());
        }
        { // 비어 있지 않았던 경우
            List<int, Nallocator> li(il);
            EXPECT_FALSE(li.Empty());
        }
    }
    {     // Mallocator
        { // 비어 있었던 경우
            List<int, Mallocator> li;
            EXPECT_TRUE(li.Empty());
        }
        { // 비어 있지 않았던 경우
            List<int, Mallocator> li(il);
            EXPECT_FALSE(li.Empty());
        }
    }
}

RDT_END