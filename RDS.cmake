set(RDS_SRCS

    # === Assertion
    src/Assertion/Assertion.cpp

    # === TypeTraits
    include/TypeTraits/TypeTraits.hpp

    # === FVectors
    src/FVector2/FVector2.cpp
    src/FVector3/FVector3.cpp

    # === Array
    include/Array/Array.hpp
    include/Array/Array_ConstIterator.hpp
    include/Array/Array_Iterator.hpp

    # Memory Management
    include/Allocator/Allocator_Trait.hpp
    include/Allocator/Mallocator.hpp

    # include/Allocator/Allocator.hpp
    # include/Arena/Arena.hpp

    # === List
    include/Node_D/Node_D.hpp
    include/List/List.hpp
    include/List/List_ConstIterator.hpp
    include/List/List_Iterator.hpp

    # === ForwardList
    include/Node_S/Node_S.hpp
    include/ForwardList/ForwardList.hpp
    include/ForwardList/ForwardList_ConstIterator.hpp
    include/ForwardList/ForwardList_Iterator.hpp

    # === Vector
    include/Vector/Vector.hpp
    include/Vector/Vector_ConstIterator.hpp
    include/Vector/Vector_Iterator.hpp

    # === Tuple
    include/Tuple/Tuple.hpp
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

    include/TypeTraits/

    include/Array/

    include/FVector2/
    include/FVector3/

    include/Allocator/

    include/Arena/

    include/Node_D/
    include/Node_S/

    include/List/

    include/Vector/

    include/ForwardList/
)
