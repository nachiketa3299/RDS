/// @file Allocator_Trait_Mallocator_Fundamental_Types.cpp
/// 기본 자료형에 대해 Mallocator 를 사용하는 Allocator_Trait 클래스의 테스트 코드

#include <gtest/gtest.h>

#include "Allocator_Trait.hpp"
#include "Mallocator.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

template <class T_t>
class tfAllocator_Trait_Mallocator_Test: public testing::Test
{
};

TYPED_TEST_SUITE_P(tfAllocator_Trait_Mallocator_Test);

TYPED_TEST_P(tfAllocator_Trait_Mallocator_Test, Allocator_Trait_Fundamental_Types)
{
    static constexpr std::size_t count = 10;
    auto* ptr = rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Allocate(count);

    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Construct(ptr, count);
    EXPECT_EQ(*ptr, TypeParam{});
    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Deconstruct(ptr, count);

    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Construct(ptr, count, 0);
    EXPECT_EQ(*ptr, TypeParam{0});
    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Deconstruct(ptr, count);

    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Construct(ptr, count, 1);
    EXPECT_EQ(*ptr, TypeParam{1});
    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Deconstruct(ptr, count);

    rds::Allocator_Trait<rds::Mallocator<TypeParam>>::Deallocate(ptr);
}

REGISTER_TYPED_TEST_SUITE_P(tfAllocator_Trait_Mallocator_Test,
                            Allocator_Trait_Fundamental_Types);

INSTANTIATE_TYPED_TEST_SUITE_P(i_integers, tfAllocator_Trait_Mallocator_Test,
                               cxx_fundamental_GTestTypes::integers);
INSTANTIATE_TYPED_TEST_SUITE_P(i_booleans, tfAllocator_Trait_Mallocator_Test,
                               cxx_fundamental_GTestTypes::booleans);
INSTANTIATE_TYPED_TEST_SUITE_P(i_characters, tfAllocator_Trait_Mallocator_Test,
                               cxx_fundamental_GTestTypes::characters);
INSTANTIATE_TYPED_TEST_SUITE_P(i_floating_points, tfAllocator_Trait_Mallocator_Test,
                               cxx_fundamental_GTestTypes::floating_points);

RDT_END