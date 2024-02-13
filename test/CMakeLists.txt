cmake_minimum_required(VERSION 3.27)

project(RDS_GTest
    VERSION 0.1.0
    DESCRIPTION "GTest Project for RDS library"
    LANGUAGES CXX
)

include(RDS_Gtest.cmake)

rds_enable_gtest()

# 테스트를 추가하려면 `rds_add_test(<src 폴더 경로> <src 파일 이름>)`을 사용한다.
rds_add_test(Array ElementAccess)
rds_add_test(Array Capacity)
rds_add_test(Array Iterator_Type)

rds_add_test(List Equality)
rds_add_test(List Erase_Range)
rds_add_test(List Erase)
rds_add_test(List Iterator_Basic)
rds_add_test(List Iterator_Boundary)
rds_add_test(List Iterator_Equality)
rds_add_test(List Iterator_Ctor)