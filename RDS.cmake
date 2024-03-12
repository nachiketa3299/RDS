set(RDS_SRCS

    # === Assertion
    src/Assertion/Assertion.cpp

    # === Array
    include/Array/Array.hpp
    include/Array/Array_ConstIterator.hpp
    include/Array/Array_Iterator.hpp

    # === Memory Management
    include/Allocator/AllocatorTraits.hpp
    include/Allocator/Mallocator.hpp
    include/Allocator/Nallocator.hpp

    # === Node
    include/Node/Node_D.hpp
    include/Node/Node_s.hpp

    # === List
    include/List/List.hpp
    include/List/List_ConstIterator.hpp
    include/List/List_Iterator.hpp

    # === ForwardList
    include/ForwardList/ForwardList.hpp
    include/ForwardList/ForwardList_ConstIterator.hpp
    include/ForwardList/ForwardList_Iterator.hpp

    # === Vector
    include/Vector/Vector.hpp
    include/Vector/Vector_ConstIterator.hpp
    include/Vector/Vector_Iterator.hpp

    # === Iterator
    include/Iterator/Iterator.hpp

    # === Tuple
    include/Tuple/Tuple.hpp
    include/TypeList/TypeList.hpp
    include/Pair/Pair.hpp

    # === FVector
    src/FVector/FVector3.cpp
)

set(RDS_INC_PRIVATE
    src/
    src/Assertion/
    src/FVector/
)

set(RDS_INC_PUBLIC
    include/

    include/Assertion/

    include/Array/

    include/Allocator/

    include/Node/

    include/List/

    include/Vector/
    include/Iterator/

    include /Tuple/
    include/TypeList/
    include/Pair/

    include/FVector/
)
