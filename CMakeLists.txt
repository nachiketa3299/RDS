cmake_minimum_required(VERSION 3.27)

project(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)

# MSVC Code page(949) Warning sucks please
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(RDS_CMakeVars.cmake)

# =[Target: Main RDS Lib]=
add_library(${PROJECT_NAME} ${RDS_SRCS}
)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${RDS_INC_PRIVATE}
    PUBLIC ${RDS_INC_PUBLIC}
)

# ###=== GOOGLE TEST ===####
rds_enable_gtest()

rds_add_test(List Erase)