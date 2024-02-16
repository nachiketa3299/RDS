cmake_minimum_required(VERSION 3.27)

project(RDT
    VERSION 0.1.0
    DESCRIPTION "GTest Project for RDS library"

    # LANGUAGES CXX
)

include(RDT.cmake)

rdt_enable_test()

# 테스트를 추가하려면 `rds_add_test(<src 폴더 경로> <src 파일 이름>)`을 사용한다.
rdt_add_test(Iterator Deref_BeginEnd)
rdt_add_test(Iterator Deref_Invalid)
rdt_add_test(MemoryManagement Mallocator_Fundamental_Types)
rdt_add_test(MemoryManagement Allocator_Trait_Mallocator_Fundamental_Types)