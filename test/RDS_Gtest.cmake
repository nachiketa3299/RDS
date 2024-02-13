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

set(RDS_TEST_INC include)

macro(rds_add_test FOLDER_NAME TEST_FILE_NAME)
    set(RDS_TEST_SRC src/${FOLDER_NAME}/${TEST_FILE_NAME}.cpp)
    set(TEST_TARGET ${FOLDER_NAME}_${TEST_FILE_NAME})
    add_executable(${TEST_TARGET} ${RDS_TEST_SRC})
    target_link_libraries(${TEST_TARGET}
        ${CMAKE_PROJECT_NAME}
        GTest::gtest_main
    )
    target_include_directories(${TEST_TARGET}
        PRIVATE ${RDS_INC_PRIVATE} ${RDS_INC_PUBLIC} ${RDS_TEST_INC}
    )
    gtest_discover_tests(${TEST_TARGET})
endmacro()