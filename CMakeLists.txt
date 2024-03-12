cmake_minimum_required(VERSION 3.27)

project(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# MSVC 컴파일러가 인코딩 오류를 내는 문제를 해결하기 위해 UTF-8로 인코딩을 강제로 바꿈
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(RDS.cmake)

# RDS 라이브러리 빌드
add_library(${PROJECT_NAME} STATIC ${RDS_SRCS})
target_include_directories(${PROJECT_NAME}
    PUBLIC ${RDS_INC_PUBLIC}
    PRIVATE ${RDS_INC_PRIVATE}
)

if(NOT DEFINED RDS_BUILD_TEST)
    option(RDS_BUILD_TEST "RDS 테스트 프로그램 빌드" ON)
endif()

if(RDS_BUILD_TEST)
    # 테스트 프로그램 빌드
    add_subdirectory(RDT)
endif()