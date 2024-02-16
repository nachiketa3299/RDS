/// @file Mallocator_Fundamental_Types.cpp
/// 기본 자료형에 대해 Mallocator 클래스의 테스트 코드

#include <gtest/gtest.h>

#include "MAllocator.hpp"
#include "RDT_CoreDefs.h"

RDT_BEGIN

template <class T_t>
class tfMallocator_Test: public testing::Test
{
protected:
    rds::Mallocator<T_t> m_mallocator{};
};

TYPED_TEST_SUITE_P(tfMallocator_Test);

TYPED_TEST_P(tfMallocator_Test, Mallocate_Fundamental_Types)
{
    static constexpr std::size_t count = 10;

    auto* ptr = this->m_mallocator.Allocate(count);

    this->m_mallocator.Construct(ptr, count);
    EXPECT_EQ(*ptr, TypeParam{});
    this->m_mallocator.Deconstruct(ptr, count);

    this->m_mallocator.Construct(ptr, count, 0);
    EXPECT_EQ(*ptr, TypeParam{0});
    this->m_mallocator.Deconstruct(ptr, count);

    this->m_mallocator.Construct(ptr, count, 1);
    EXPECT_EQ(*ptr, TypeParam{1});
    this->m_mallocator.Deconstruct(ptr, count);

    this->m_mallocator.Deallocate(ptr);
}

REGISTER_TYPED_TEST_SUITE_P(tfMallocator_Test, Mallocate_Fundamental_Types);

INSTANTIATE_TYPED_TEST_SUITE_P(i_integers, tfMallocator_Test,
                               cxx_fundamental_GTestTypes::integers);
INSTANTIATE_TYPED_TEST_SUITE_P(i_booleans, tfMallocator_Test,
                               cxx_fundamental_GTestTypes::booleans);
INSTANTIATE_TYPED_TEST_SUITE_P(i_characters, tfMallocator_Test,
                               cxx_fundamental_GTestTypes::characters);
INSTANTIATE_TYPED_TEST_SUITE_P(i_floating_points, tfMallocator_Test,
                               cxx_fundamental_GTestTypes::floating_points);

RDT_END
