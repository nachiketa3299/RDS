cmake_minimum_required(
    VERSION 3.27
)

project(RDS
    VERSION 0.1.0
    DESCRIPTION "C++ Data Structures Library written by RZN"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)

# MSVC Code page(949) Warning sucks please
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# =[Target: Main RDS Lib]=
add_library(${PROJECT_NAME}
    src/Assertion/Assertion.cpp
    src/FVector2/FVector2.cpp
    src/FVector3/FVector3.cpp
    include/Array/Array.hpp
    include/Array/Array_ConstIterator.hpp
    include/Array/Array_Iterator.hpp
    include/Allocator/MAllocator.hpp
    include/Allocator/Allocator.hpp
    include/Arena/Arena.hpp
    include/Node_D/Node_D.hpp
    include/List/List.hpp
    include/List/List_ConstIterator.hpp
    include/List/List_Iterator.hpp
)

# Main RDS include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE src/ src/Assertion/ src/FVector2/ src/FVector3/
    PUBLIC include/ include/Assertion/ include/FVector2/ include/FVector3/ include/Array/ include/List/ include/Allocator/ include/Arena/ include/Node_D/
)

# =[Targets: GTests]== Google Test Settings
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

# === TEST SETTINGS
macro(radd_class_gtest CLASS_NAME)
    add_executable(${CLASS_NAME}_gtest test/gtest/${CLASS_NAME}_gtest.cpp)
    target_link_libraries(${CLASS_NAME}_gtest ${PROJECT_NAME} GTest::gtest_main)
    target_include_directories(${CLASS_NAME}_gtest PRIVATE include/${CLASS_NAME}/ src/ src/${CLASS_NAME}/)
    gtest_discover_tests(${CLASS_NAME}_gtest)
endmacro()

macro(radd_tclass_gtest TEMPLATED_CLASS_NAME)
    add_executable(${TEMPLATED_CLASS_NAME}_gtest test/gtest/${TEMPLATED_CLASS_NAME}_gtest.cpp)
    target_link_libraries(${TEMPLATED_CLASS_NAME}_gtest ${PROJECT_NAME} GTest::gtest_main)
    target_include_directories(${TEMPLATED_CLASS_NAME}_gtest PRIVATE include/${TEMPLATED_CLASS_NAME}/ src/)
    gtest_discover_tests(${TEMPLATED_CLASS_NAME}_gtest)
endmacro()

macro(radd_tclass_gtest_include TEMPLATED_CLASS_NAME INCLUDE_DIR_NAME)
    add_executable(${TEMPLATED_CLASS_NAME}_gtest test/gtest/${TEMPLATED_CLASS_NAME}_gtest.cpp)
    target_link_libraries(${TEMPLATED_CLASS_NAME}_gtest ${PROJECT_NAME} GTest::gtest_main)
    target_include_directories(${TEMPLATED_CLASS_NAME}_gtest PRIVATE include/${INCLUDE_DIR_NAME}/ src/)
    gtest_discover_tests(${TEMPLATED_CLASS_NAME}_gtest)
endmacro()

radd_class_gtest(FVector2)
radd_class_gtest(FVector3)
radd_tclass_gtest(Array)
radd_tclass_gtest(Arena)

radd_tclass_gtest(List)
radd_tclass_gtest_include(List_ConstIterator List)
radd_tclass_gtest_include(List_Iterator List)
radd_tclass_gtest(Node_D)