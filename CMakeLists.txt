cmake_minimum_required(
    VERSION 3.27
)

project(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)

# Main RDS Library Linking
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

# === Adding `Google Test` for library test
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
add_executable(Vector2_test test/Vector2/Vector2_test.cpp)
target_link_libraries(Vector2_test ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Vector2_test PRIVATE include/Vector2/ src/ src/Vector2/)

# test for Vector3
add_executable(Vector3_test test/Vector3/Vector3_test.cpp)
target_link_libraries(Vector3_test ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Vector3_test PRIVATE include/Vector3/ src/ src/Vector3/)

# test for Array
add_executable(Array_test test/Array/Array_test.cpp)
target_link_libraries(Array_test ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(Array_test PRIVATE include/Array/ src/)

include(GoogleTest)
gtest_discover_tests(Vector2_test)
gtest_discover_tests(Vector3_test)
gtest_discover_tests(Array_test)