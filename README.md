# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

[![wakatime](https://wakatime.com/badge/github/nachiketa3299/RDS.svg)](https://wakatime.com/badge/github/nachiketa3299/RDS)

## Tools

- Text Editor 
    - **Visual Studio Code**
- Build Automation 
    - **CMake (3.27.0)**
        - **_Main_: RDS 라이브러리**
            - [/CMakeList.txt](/CMakeLists.txt) <sub>기본 RDS 라이브러리 빌드 설정</sub>
            - [/RDS.cmake](/RDS.cmake) <sub>빌드 설정 위한 변수 및 매크로 정의</sub>
        - **_Sub_: RDS_GTest 테스트**
            - [/test/CMakeList.txt](/test/CMakeLists.txt)<sub>라이브러리 GTest 용 프로젝트</sub>
            - [/test/RDS_Gtest.cmake](/test/RDS_Gtest.cmake)<sub>테스트 프로젝트 빌드 설정 위한 변수 및 매크로 정의</sub>
- Compilers
    - MSVC 
        - Visual Studio 2019 Community Release
    - MSYS g++
    - Clang
- Static Analysis
    - **Clang-tidy**
- Test
    - **Google Test**
- Formatting
    - **clang-format**
- Documentation
    - **Doxygen**
- Special Thanks to *Zenburn* & *VsCodeVim*

# *RDS* <sup><i>outlines</i></sup>

## Container Specs

1. Member Types Aliases
2. Method
    - Constructors
    - Destructor
    - Assignment Operator
    - Iterators
    - Capacity
    - Element Access
    - Modifiers
    - Operations
    - Observers
3. Members
4. Non-Member Function Overloads

## Utilities

- **Cores**
    - [RDS_CoreDefs.h](/include/RDS_CoreDefs.h)
    - [RDS_Concepts.h](/include/RDS_Concepts.h)
- **Assertion**
    - [Assertion.h](/include/Assertion/Assertion.h)
    - [Assertion.cpp](/src/Assertion/Assertion.cpp)

## Linear Data Structures

- **정적 배열(Static Array)**
    - [Array.hpp](/include/Array/Array.hpp)
    - [Array_ConstIterator.hpp](/include/Array/Array_ConstIterator.hpp)
    - [Array_Iterator.hpp](/include/Array/Array_Iterator.hpp)
- **동적 배열(Dynamic Array)**
    - [Vector.hpp](/include/Vector/Vector.hpp)
    - [Vector_ConstIterator.hpp](/include/Vector/Vector_ConstIterator.hpp)
    - [Vector_Iterator.hpp](/include/Vector/Vector_Iterator.hpp)
- **이중 연결 리스트(Doubly Linked List)**
    - [List.hpp](/include/List/List.hpp)
    - [List_ConstIterator.hpp](/include/List/List_ConstIterator.hpp)
    - [List_Iterator](/include/List/List_Iterator.hpp)
- **단일 연결 리스트(Singly Linked List)**
    - [ForwardList.hpp](/include/ForwardList/ForwardList.hpp)
    - [ForwardList_ConstIterator.hpp](/include/ForwardList/ForwardList_ConstIterator.hpp)
    - [ForwardList_Iteartor.hpp](/include/ForwardList/ForwardList_Iterator.hpp)
- **벡터(FVector)**
    - [RDS_FVectors.h](/include/RDS_FVectors.h)
    - **2차원 벡터(FVector2)**
        - [FVector2.h](/include/FVector2/FVector2.h)
        - [FVector2.cpp](/src/FVector2/FVector2.cpp)
    - **3차원 벡터(FVector3)**
        - [FVector3.h](/include/FVector3/FVector3.h)
        - [FVector3.cpp](/src/FVector3/FVector3.cpp)
- Heap
- Queue
    - Queue
    - Circular Queue
    - Priority Queue
- Stack
- Matrix
    - Matrix
    - Sparse Matrix
- Pair
- Tuple
- Hashmap
- Hashset

## Non-Linear Data Structures

- Trees
    - Binary Tree
- Graphs
    - Graph: <sup>with Adjacent List</sup>
    - Graph: <sup>with Adjacent Matrix</sup>

## *Algorithms*

### Sorting Algorithms

- [ ] Bubble Sort
- [ ] Selection Sort
- [ ] Insertion Sort
- [ ] Quick Sort
- [ ] Merge Sort
- [ ] Heap Sort

### Shortest Path Algorithms

- [ ] BFS<sup>Breadth-frist Search</sup>
- [ ] DFS<sup>Depth-first Search</sup>
- [ ] Dijkstra Algorithm
- [ ] Floyd-Warshall Algorithm

### Minimum Spanning Tree

- [ ] Kruskal's Algorithm
- [ ] Prim's Algorithm

### Others

- [ ] Union-find 

# References

- [stlmp/stmlp/Github](https://github.com/stlmp/stlmp)
- [gtest-cmake-example/dmonopoly](https://github.com/dmonopoly/gtest-cmake-example)