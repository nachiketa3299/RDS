cmake_minimum_required(
    VERSION 3.27
)

project(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)

# =[Target: Main RDS Lib]=
add_library(${PROJECT_NAME}
    src/Assertion/Assertion.cpp
    src/Vector2/Vector2.cpp
    src/Vector3/Vector3.cpp
    include/Array/Array.hpp
    include/Array/Array_ConstIterator.hpp
    include/Array/Array_Iterator.hpp
)

# Main RDS include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE src/ src/Assertion/ src/Vector2/ src/Vector3/
    PUBLIC include/ include/Assertion/ include/Vector2/ include/Vector3/ include/Array
)

# =[Targets: CTests]= CTest Settings
# Reference: [CTest/freehuni's home](https://freehuni.blogspot.com/2017/12/ctest.html)
include(CTest)
add_executable(Array_ctest test/ctest/Array_ctest.cpp)
target_link_libraries(Array_ctest ${PROJECT_NAME})
add_dependencies(Array_ctest ${PROJECT_NAME})
target_include_directories(Array_ctest PRIVATE include/Array/ src/)
add_test(Array_ctest-0 Array_ctest)

# =[Targets: GTests]== Google Test Settings
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# === TEST SETTINGS
# test for Vector2
add_executable(Vector2_gtest test/gtest/Vector2_gtest.cpp)
target_link_libraries(Vector2_gtest ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Vector2_gtest PRIVATE include/Vector2/ src/ src/Vector2/)

# test for Vector3
add_executable(Vector3_gtest test/gtest/Vector3_gtest.cpp)
target_link_libraries(Vector3_gtest ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Vector3_gtest PRIVATE include/Vector3/ src/ src/Vector3/)

# test for Array
add_executable(Array_gtest test/gtest/Array_gtest.cpp)
target_link_libraries(Array_gtest ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Array_gtest PRIVATE include/Array/ src/)

include(GoogleTest)
gtest_discover_tests(Vector2_gtest)
gtest_discover_tests(Vector3_gtest)
gtest_discover_tests(Array_gtest)