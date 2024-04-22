# Simple list logging function
FUNCTION(log_list _list_to_log)
    FOREACH(item IN LISTS ${_list_to_log})
        MESSAGE("\t- ${item}")
    ENDFOREACH()
ENDFUNCTION()

SET(rds_log_prefix ">> [RDS]")

SET(rds_private_hpp_include_dir ${PROJECT_SOURCE_DIR}/include/RDS/)
SET(rds_private_cpp_include_dir ${PROJECT_SOURCE_DIR}/src/)
SET(rds_cpp_source_list)
SET(rds_hpp_source_list)
SET(rds_source_list)

LIST(APPEND rds_cpp_source_list Assertion FVector3)
LIST(APPEND rds_hpp_source_list AllocatorTraits Mallocator Nallocator)
LIST(APPEND rds_hpp_source_list Tuple TypeList Pair)
LIST(APPEND rds_hpp_source_list Iterator)
LIST(APPEND rds_hpp_source_list Array Array_ConstIterator Array_Iterator)
LIST(APPEND rds_hpp_source_list Node_D List List_ConstIterator List_Iterator)
LIST(APPEND rds_hpp_source_list Node_S ForwardList ForwardList_ConstIterator ForwardList_Iterator)
LIST(APPEND rds_hpp_source_list Vector Vector_ConstIterator Vector_Iterator)
LIST(APPEND rds_hpp_source_list Algorithm)
LIST(APPEND rds_hpp_source_list Functional)

LIST(TRANSFORM rds_cpp_source_list APPEND .cpp)
list(TRANSFORM rds_cpp_source_list PREPEND ${rds_private_cpp_include_dir})
LIST(TRANSFORM rds_hpp_source_list APPEND .hpp)
LIST(TRANSFORM rds_hpp_source_list PREPEND ${rds_private_hpp_include_dir})

MESSAGE("${rds_log_prefix} 소스 파일(.hpp) 목록:")
log_list(rds_hpp_source_list)

MESSAGE("${rds_log_prefix} 소스 파일(.cpp) 목록:")
log_list(rds_cpp_source_list)

LIST(APPEND rds_source_list ${rds_hpp_source_list} ${rds_cpp_source_list})