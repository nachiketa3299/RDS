cmake_minimum_required(VERSION 3.27)

project(RDS_GTest
    VERSION 0.1.0
    DESCRIPTION "GTest Project for RDS library"

    # LANGUAGES CXX
)

include(RDS_Gtest.cmake)

rds_enable_gtest()

# 테스트를 추가하려면 `rds_add_test(<src 폴더 경로> <src 파일 이름>)`을 사용한다.
rds_add_test(Iterator Deref_BeginEnd)
rds_add_test(Iterator Deref_Invalid)
