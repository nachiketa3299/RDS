cmake_minimum_required(VERSION 3.27)

project(RDT
    VERSION 0.1.0
    DESCRIPTION "GTest Project for RDS library"

    # LANGUAGES CXX
)

add_executable(SIMPLE_TEST src/Test.cpp)

include(RDT.cmake)

rdt_enable_test()

# 테스트를 추가하려면 `rds_add_test(<src 폴더 경로> <src 파일 이름>)`을 사용한다.
# rdt_add_test(List Basic_Test)
# rdt_add_test(List Ctor)
rdt_add_test(Allocator Mallocator)

rdt_add_test(List Ctors)
rdt_add_test(List Iterator)
rdt_add_test(List NodeManagement)
rdt_add_test(List ElementAccess)
rdt_add_test(List Capacity)
rdt_add_test(List Modifier)
rdt_add_test(List Operation)

rdt_add_test(Iterator Iterator)

rdt_add_test(Tuple Basic)

# rdt_add_test(MemoryManagement Mallocator_Fundamental_Types)
# rdt_add_test(MemoryManagement Allocator_Trait_Mallocator_Fundamental_Types)