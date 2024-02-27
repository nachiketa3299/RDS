#include <gtest/gtest.h>

#include "Allocator_Trait.hpp"
#include "Mallocator.hpp"
#include "RDT_CoreDefs.h"

/*
--------------------------------------------------------------------------------
 * Allocate(Size_t count) -> Val_t*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--------------------------------------------------------------------------------
 * Deallocate(Size_t count) -> void
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--------------------------------------------------------------------------------
 * Construct(Val_t* ptr, Size_t count, CtorArgs_&&... CtorArgs) -> void
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--------------------------------------------------------------------------------
 * Deconstruct(const Val_t* ptr, Size_t count) -> void
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--------------------------------------------------------------------------------
*/

RDT_BEGIN

using namespace rds;

TEST(Mallocator_Allocate, one)
{
    int* ptr;
    EXPECT_NO_THROW(ptr = Mallocator<int>().Allocate(1));
    Mallocator<int>().Construct(ptr, 1, 10);
    Mallocator<int>().Deallocate(ptr);

    // const int* cptr;
    // EXPECT_NO_THROW(cptr = Mallocator<int>().Allocate(1));
    // Mallocator<int>().Construct(cptr, 1, 10);
    // Mallocator<int>().Deallocate(cptr);
}

RDT_END
