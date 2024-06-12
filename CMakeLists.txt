CMAKE_MINIMUM_REQUIRED(VERSION 3.27)
PROJECT(RDS VERSION 0.1.2 LANGUAGES CXX)
SET(PROJECT_DESCRIPTION "C++를 사용한 자료구조와 알고리즘 라이브러리")
SET(CMAKE_CXX_STANDARD 23)

SET(rds_public_include_dir ${PROJECT_SOURCE_DIR}/include)
SET(rds_private_include_dir ${PROJECT_SOURCE_DIR}/src)

# SET(rds_sources Assertion.cpp FVector3.cpp)
SET(rds_template_sources array.h vector.h allocator.h heap.h)

LIST(TRANSFORM rds_sources PREPEND ${rds_private_include_dir}/)
LIST(TRANSFORM rds_template_sources PREPEND ${rds_public_include_dir}/RDS/)

SET(rds_all_sources ${rds_sources} ${rds_template_sources})

# RDS 스태틱 라이브러리를 생성한다.
ADD_LIBRARY(${PROJECT_NAME} STATIC ${rds_all_sources})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# 외부에서 이 라이브러리를 사용할 때 인클루드 경로. 예) #include "RDS/Array.hpp"
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${rds_public_include_dir})

# 내부 인클루드 경로
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${rds_private_include_dir})

OPTION(rds_enable_gtest "Enable GTest" OFF)
OPTION(rds_enable_test "Enable Test" ON)

IF(PROJECT_IS_TOP_LEVEL)
    MESSAGE("${rds_log_prefix} 프로젝트가 최상위입니다.")

    IF(rds_enable_gtest)
        MESSAGE(STATUS "${rds_log_prefix} 설정에 따라 구글 테스트 프로그램을 추가합니다.")
        ADD_SUBDIRECTORY(RDS_Gtest)
    ENDIF()

    IF(rds_enable_test)
        MESSAGE(STATUS "${rds_log_prefix} 설정에 따라 기본 테스트 프로그램을 추가합니다.")
        ADD_SUBDIRECTORY(RDS_Test)
    ENDIF()
ENDIF()

UNSET(rds_enable_gtest CACHE)
UNSET(rds_enable_test CACHE)

# TODO MSVC에 무슨 문제가 있어서 오류가 나는 건지 확인할 것, 재설치 하라는데 너무 귀찮음
# TODO MSVC로 테스트 할 때, utf-8 옵션에 대해서 고민해 보아야 함. (GCC 에서는 상관 없는 듯 함)
# UNKNOWN GCC의 경우 ADD_COMPILE_OPTIONS("/utf-8") 이걸 추가하면, 오류가 난다. 하지만 빼니까 됨.
# TODO Log Verbose 설정을 해야 할 것 같음. ^.^ 내가 만든건데 너무 많이 나옴.