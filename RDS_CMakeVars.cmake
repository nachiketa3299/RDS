set(RDS_SRCS

    # Assertion
    src/Assertion/Assertion.cpp

    # FVectors
    src/FVector2/FVector2.cpp
    src/FVector3/FVector3.cpp

    # Array
    include/Array/Array.hpp
    include/Array/Array_ConstIterator.hpp
    include/Array/Array_Iterator.hpp

    # Memory Management
    include/Allocator/MAllocator.hpp
    include/Allocator/Allocator.hpp
    include/Arena/Arena.hpp

    # List
    include/Node_D/Node_D.hpp
    include/List/List.hpp
    include/List/List_ConstIterator.hpp
    include/List/List_Iterator.hpp
)

set(RDS_INC_PRIVATE
    src/
    src/Assertion/
    src/FVector2/
    src/FVector3/
)

set(RDS_INC_PUBLIC
    include/
    include/Assertion/
    include/FVector2/
    include/FVector3/
    include/Allocator/
    include/Arena/
    include/Node_D/
    include/List/
)

macro(rds_enable_gtest)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    enable_testing()
endmacro()

set(GTEST_DIR test/gtest)

macro(rds_add_test CLASS_NAME TEST_NAME)
    set(TARGET_NAME ${CLASS_NAME}_${TEST_NAME}_gtest)
    set(TARGET_NAME_EXET ${TARGET_NAME}.cpp)
    set(TEST_DIR ${GTEST_DIR}/${CLASS_NAME})

    add_executable(${TARGET_NAME} ${TEST_DIR}/${TARGET_NAME_EXET})
    target_link_libraries(${TARGET_NAME} ${PROJECT_NAME} GTest::gtest_main)
    target_include_directories(${TARGET_NAME}
        PRIVATE ${RDS_INC_PRIVATE} ${RDS_INC_PUBLIC}
    )
    gtest_discover_tests(${TARGET_NAME})
endmacro()