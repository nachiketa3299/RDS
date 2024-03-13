# 리스트 로깅 함수
function(log_list list_to_log)
    foreach(item IN LISTS ${list_to_log})
        message("\t- ${item}")
    endforeach()
endfunction()

set(RDS_LOG_PREFIX ">> [RDS]")

# =========

# RDS_INC_PUBLIC: 퍼블릭 포함 경로
set(RDS_INC_PUBLIC ${PROJECT_SOURCE_DIR}/include/RDS/)

# RDS_INC_PRIVATE: 프라이빗 포함 경로
set(RDS_INC_PRIVATE ${PROJECT_SOURCE_DIR}/src/)

# RDS_CPP_SRCS: .cpp 형태의 소스 리스트 정의
set(RDS_CPP_SRCS
    Assertion.cpp
    FVector3.cpp
)

# RDS_HPP_SRCS: .hpp 형태의 소스 리스트 정의 (템플릿 클래스)
set(RDS_HPP_SRCS

    # === Memory Management
    AllocatorTraits.hpp
    Mallocator.hpp
    Nallocator.hpp

    # === Tuple & Pair
    Tuple.hpp
    TypeList.hpp
    Pair.hpp

    # === Iterator
    Iterator.hpp

    # === Container/Array
    Array.hpp
    Array_ConstIterator.hpp
    Array_Iterator.hpp

    # === Container/List
    Node_D.hpp
    List.hpp
    List_ConstIterator.hpp
    List_Iterator.hpp

    # === Container/ForwardList
    Node_S.hpp
    ForwardList.hpp
    ForwardList_ConstIterator.hpp
    ForwardList_Iterator.hpp

    # === Container/Vector
    Vector.hpp
    Vector_ConstIterator.hpp
    Vector_Iterator.hpp

    # === Algorithm
    Algorithm.hpp

    # === Functional
    Functional.hpp
)

# 인클루드 경로를 소스 파일 이름 앞에 추가
list(TRANSFORM RDS_HPP_SRCS PREPEND ${RDS_INC_PUBLIC})
list(TRANSFORM RDS_CPP_SRCS PREPEND ${RDS_INC_PRIVATE})

# 제대로 추가되었는지 확인
message("${RDS_LOG_PREFIX} 템플릿 소스 파일 목록:")
log_list(RDS_HPP_SRCS)

message("${RDS_LOG_PREFIX} 소스 파일 목록:")
log_list(RDS_CPP_SRCS)

# RDS_SRCS: 전체 소스 리스트
set(RDS_SRCS ${RDS_HPP_SRCS} ${RDS_CPP_SRCS})
