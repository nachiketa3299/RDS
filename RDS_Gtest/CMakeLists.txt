# @date 2024-04-22
# Project Settings

CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RDS_Gtest VERSION 0.1.0)
SET(PROJECT_DESCRIPTION "GTest Project for RDS Library")

SET(rdgt_log_prefix ">> [RDS_Gtest]")

include(RDS_Gtest.cmake)

# `rdt_enable_gtest`
rdgt_enable_gtest()

rdgt_add_test_target(SimpleGtest)

# 테스트를 추가하려면 `rds_add_test(<src 폴더 경로> <src 파일 이름>)`을 사용한다.
# rdt_add_test(List Basic_Test)
# rdt_add_test(List Ctor)
# rdt_add_test(Allocator Mallocator)

# rdt_add_test(List Ctors)
# rdt_add_test(List Iterator)
# rdt_add_test(List NodeManagement)
# rdt_add_test(List ElementAccess)
# rdt_add_test(List Capacity)
# rdt_add_test(List Modifier)
# rdt_add_test(List Operation)

# rdt_add_test(Iterator Iterator)

# rdt_add_test(Vector Ctor)
# rdt_add_test(Vector Access)

# rdt_add_test(Algorithm MinMax)
# rdt_add_test(Algorithm Fill)

# rdt_add_test(Tuple Basic)

# rdt_add_test(MemoryManagement Mallocator_Fundamental_Types)
# rdt_add_test(MemoryManagement Allocator_Trait_Mallocator_Fundamental_Types)