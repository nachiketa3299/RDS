CMAKE_MINIMUM_REQUIRED(
    VERSION 3.27
)

PROJECT(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures by RZN"
    LANGUAGES CXX
)

SET(
    SRC_VECTORS
        src/Vectors/Vector2.cpp
        src/Vectors/Vector3.cpp
)

SET(
    INC_VECTORS
        include/Vectors/
)
SET(
    INC_VECTORS_P
        src/Vectors/
)

ADD_LIBRARY(
    ${PROJECT_NAME}
        ${SRC_VECTORS}
)

TARGET_INCLUDE_DIRECTORIES(
    ${PROJECT_NAME}
        PUBLIC ${INC_VECTORS}
        PRIVATE ${INC_VECTORS_P}

    PRIVATE src
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
add_executable(
    Vectors_test test/Vectors_test.cpp
)
target_link_libraries(
    Vectors_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Vectors_test)
