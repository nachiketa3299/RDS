# GTest 를 받아와서 테스트를 활성화하는 매크로
MACRO(rdgt_enable_gtest)
    INCLUDE(FetchContent)

    # Configure 시점에 구글 테스트 가져오기
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    INCLUDE(GoogleTest)
    ENABLE_TESTING()
ENDMACRO()

SET(rdgt_private_include_dir ${PROJECT_SOURCE_DIR}/include)
SET(rdgt_source_dir ${PROJECT_SOURCE_DIR}/src/)

MACRO(rdgt_add_test_target _file_name)
    SET(target_name ${_file_name})
    SET(full_file_name "${rdgt_source_dir}${_file_name}.cpp")
    MESSAGE(STATUS "${rdgt_log_prefix} 테스트 파일 ${full_file_name}을 타겟 ${target_name}으로 추가.")

    ADD_EXECUTABLE(${target_name} ${full_file_name})
    TARGET_LINK_LIBRARIES(${target_name} RDS)
    TARGET_LINK_LIBRARIES(${target_name} GTest::gtest_main)
    TARGET_INCLUDE_DIRECTORIES(${target_name} PRIVATE ${rdgt_private_include_dir})
    TARGET_INCLUDE_DIRECTORIES(${target_name} PRIVATE ${rds_public_include_dir})
    GTEST_DISCOVER_TESTS(${target_name})
    ADD_TEST(test_all ${target_name}) # ctest -R test_all
ENDMACRO()

# 테스트 추가 매크로: 테스트를 추가하려면 소스 파일이 있는 폴더 이름과 파일 이름을 인자로 넘겨주면 됨.
MACRO(rdt_add_test DIR_NAME FILE_NAME)
    SET(RDT_SRC src/${DIR_NAME}/${FILE_NAME}.cpp)
    SET(RDT_TARGET ${DIR_NAME}_${FILE_NAME})
    ADD_EXECUTABLE(${RDT_TARGET} ${RDT_SRC})
    TARGET_LINK_LIBRARIES(${RDT_TARGET}
        ${CMAKE_PROJECT_NAME} # RDS 라이브러리
        GTest::gtest_main
    )
    TARGET_INCLUDE_DIRECTORIES(${RDT_TARGET}
        PRIVATE ${RDS_INC_PRIVATE} ${RDS_INC_PUBLIC} ${rdgt_private_include_dir}
    )
    GTEST_DISCOVER_TESTS(${RDT_TARGET})
    ADD_TEST(test_all ${RDT_TARGET}) # ctest -R test_all 로 테스트 실행
endmacro()