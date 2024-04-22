# @date 2024-04-22
# Project Settings

CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RDS VERSION 0.1.2 LANGUAGES CXX)
SET(PROJECT_DESCRIPTION "C++ Data Structures Library written by RZN")
SET(CMAKE_CXX_STANDARD 23)

# Set list variables for `[rds_hpp_source_list;rds_cpp_source_list] = rds_source_list`
# also set `rds_private_hpp_include_dir` and `rds_private_cpp_include_dir`
INCLUDE(RDS.cmake)

# RDS 스태틱 라이브러리를 생성한다.
ADD_LIBRARY(${PROJECT_NAME} STATIC ${rds_source_list})

# 외부에서 이 라이브러리를 사용할 때 인클루드 경로. 예) #include "RDS/Array.hpp"
SET(rds_public_include_dir ${PROJECT_SOURCE_DIR}/include)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${rds_public_include_dir})

# 내부 인클루드 경로
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${rds_private_hpp_include_dir})
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${rds_private_cpp_include_dir})

OPTION(rds_enable_gtest "Enable GTest" OFF)
OPTION(rds_enable_test "Enable Test" ON)

IF(PROJECT_IS_TOP_LEVEL)
    MESSAGE("${rds_log_prefix} 프로젝트가 최상위입니다.")

    IF(rds_enable_gtest)
        MESSAGE(STATUS "${rds_log_prefix} 설정에 따라 구글 테스트 프로그램을 추가합니다.")
        ADD_SUBDIRECTORY(RDS_Gtest)
    ENDIF()

    IF(rds_enable_test)
        MESSAGE(STATUS "${rds_log_prefix} 설정에 따라 테스트 프로그램을 추가합니다.")
        ADD_SUBDIRECTORY(RDS_Test)
    ENDIF()
ENDIF()

UNSET(rds_enable_gtest CACHE)
UNSET(rds_enable_test CACHE)

# TODO MSVC에 무슨 문제가 있어서 오류가 나는 건지 확인할 것, 재설치 하라는데 너무 귀찮음
# TODO MSVC로 테스트 할 때, utf-8 옵션에 대해서 고민해 보아야 함. (GCC 에서는 상관 없는 듯 함)
# UNKNOWN GCC의 경우 ADD_COMPILE_OPTIONS("/utf-8") 이걸 추가하면, 오류가 난다. 하지만 빼니까 됨.
# TODO Log Verbose 설정을 해야 할 것 같음. ^.^ 내가 만든건데 너무 많이 나옴.