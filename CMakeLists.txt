cmake_minimum_required(VERSION 3.27)

project(RDS
    VERSION 0.1.1
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

include(RDS.cmake)

# RDS.cmake 에는 아래 변수가 정의되어 있음
# RDS_SRCS
# RDS_INC_PUBLIC (./include/RDS/)
# RDS_INC_PRIVATE (./src/)

# 'RDS' Static Library 타겟 생성
add_library(${PROJECT_NAME} STATIC ${RDS_SRCS})

# 타겟의 포함 경로 설정 (RDS_INC_PUBLIC, RDS_INC_PRIVATE)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/ PRIVATE ./include/RDS/ PRIVATE ./include/src/)

if(PROJECT_IS_TOP_LEVEL)
    if(MSVC)
        message(STATUS "${RDS_LOG_PREFIX} 프로젝트가 최상위이므로 UTF-8 설정을 합니다.")
        add_compile_options("/utf-8") # MSVC UTF-8 설정 (안하면 자꾸 뭐라고 함...)
    endif()

    message(STATUS "${RDS_LOG_PREFIX} 프로젝트가 최상위이므로 테스트 프로그램을 추가합니다.")
    set(RDT_BUILD_TEST ON CACHE BOOL "")
    add_subdirectory(RDT)
endif()
