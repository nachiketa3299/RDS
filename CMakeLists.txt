cmake_minimum_required(VERSION 3.27)

project(RDS
    VERSION 0.1.1
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    add_compile_options("/utf-8") # MSVC UTF-8 설정 (안하면 자꾸 뭐라고 함...)
endif()

include(RDS.cmake)

# RDS.cmake 에는 아래 변수가 정의되어 있음
# RDS_SRCS
# RDS_INC_PUBLIC (./include/RDS/)
# RDS_INC_PRIVATE (./src/)

# 'RDS' Static Library 타겟 생성
add_library(${PROJECT_NAME} STATIC ${RDS_SRCS})

# 타겟의 포함 경로 설정 (RDS_INC_PUBLIC, RDS_INC_PRIVATE)
target_include_directories(${PROJECT_NAME} PUBLIC ${RDS_INC_PUBLIC} PRIVATE ${RDS_INC_PRIVATE})

# 옵션: 테스트 프로그램 빌드 여부
if(NOT DEFINED RDS_BUILD_TEST)
    option(RDS_BUILD_TEST "RDS 테스트 프로그램 빌드" ON)
endif()

if(RDS_BUILD_TEST)
    # 테스트 프로그램 빌드
    add_subdirectory(RDT)
endif()