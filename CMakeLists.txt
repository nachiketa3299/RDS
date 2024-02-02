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
)

# Main RDS include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE src/ src/Assertion/ src/Vector2/ src/Vector3/
    PUBLIC include/ include/Assertion/ include/Vector2/ include/Vector3/
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
add_executable(vector2_test test/Vector2/Vector2_test.cpp)
target_link_libraries(vector2_test ${PROJECT_NAME} GTest::gtest_main)
target_include_directories(vector2_test PRIVATE include/Vector2/ src/ src/Vector2/)

include(GoogleTest)
gtest_discover_tests(vector2_test)