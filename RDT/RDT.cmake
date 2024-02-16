# GTest 를 받아와서 테스트를 활성화하는 매크로
macro(rdt_enable_test)
    include(FetchContent)

    # Configure 시점에 구글 테스트 가져오기
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    enable_testing()
endmacro()

# RDS_INC 는 RDT/include/ 임
set(RDT_INC include)

# 테스트 추가 매크로: 테스트를 추가하려면 소스 파일이 있는 폴더 이름과 파일 이름을 인자로 넘겨주면 됨.
macro(rdt_add_test DIR_NAME FILE_NAME)
    set(RDT_SRC src/${DIR_NAME}/${FILE_NAME}.cpp)
    set(RDT_TARGET ${DIR_NAME}_${FILE_NAME})
    add_executable(${RDT_TARGET} ${RDT_SRC})
    target_link_libraries(${RDT_TARGET}
        ${CMAKE_PROJECT_NAME} # RDS 라이브러리
        GTest::gtest_main
    )
    target_include_directories(${RDT_TARGET}
        PRIVATE ${RDS_INC_PRIVATE} ${RDS_INC_PUBLIC} ${RDT_INC}
    )
    gtest_discover_tests(${RDT_TARGET})
endmacro()