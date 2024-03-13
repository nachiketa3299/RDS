set(RDS_SRCS

    # === Assertion
    src/Assertion.cpp

    # === Memory Management
    include/AllocatorTraits.hpp
    include/Mallocator.hpp
    include/Nallocator.hpp

    # === Array
    include/Array.hpp
    include/Array_ConstIterator.hpp
    include/Array_Iterator.hpp

    # === List
    include/Node_D.hpp
    include/List.hpp
    include/List_ConstIterator.hpp
    include/List_Iterator.hpp

    # === ForwardList
    include/Node_S.hpp
    include/ForwardList.hpp
    include/ForwardList_ConstIterator.hpp
    include/ForwardList_Iterator.hpp

    # === Vector
    include/Vector.hpp
    include/Vector_ConstIterator.hpp
    include/Vector_Iterator.hpp

    # === Iterator
    include/Iterator.hpp

    # === Tuple & Pair
    include/Tuple.hpp
    include/TypeList.hpp
    include/Pair.hpp

    # === FVector
    src/FVector3.cpp

    # === Algorithm
    include/Algorithm.hpp

    # === Functional
    include/Functional.hpp
)

set(RDS_INC_PRIVATE src/)

set(RDS_INC_PUBLIC include/)
