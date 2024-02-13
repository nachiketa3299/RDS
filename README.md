# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

계획 및 일지는 [여기](.\docs\mds\Plans.md)를 참조

## Tools

- `Text Editor` **Visual Studio Code**
- `Build Automation` **CMake (3.27.0)**
    - **_Main_: RDS 라이브러리**
        - [/CMakeList.txt](/CMakeLists.txt) <sub>기본 RDS 라이브러리 빌드 설정</sub>
        - [/RDS.cmake](/RDS.cmake) <sub>빌드 설정 위한 변수 및 매크로 정의</sub>
    - **_Sub_: RDS_GTest 테스트**
        - [/test/CMakeList.txt](/test/CMakeLists.txt)<sub>라이브러리 GTest 용 프로젝트</sub>
        - [/test/RDS_Gtest.cmake](/test/RDS_Gtest.cmake)<sub>테스트 프로젝트 빌드 설정 위한 변수 및 매크로 정의</sub>
- `Compilers`
    - MSVC 
        - Visual Studio 2019 Community Release
    - MSYS g++
    - Clang
- `Static Analysis` **Clang-tidy**
- `Test` **Google Test**
- `Formatting` **clang-format**
- `Documentation` **Doxygen**

# *RDS* - outlines

## Utilities

### Cores

- [RDS_CoreDefs.h](/include/RDS_CoreDefs.h)
- [RDS_Concepts.h](/include/RDS_Concepts.h)
- [RDS_FVectors.h](/include/RDS_FVectors.h)

### Assertion

- [X] [Assertion.h](/include/Assertion/Assertion.h)<sup>Macro function <code>RDS_Assert</code></sup>
- [X] [Assertion.cpp](/src/Assertion/Assertion.cpp)

## Linear Data Structures


### Static Array

> 정적 배열 템플릿 클래스

- [X] [Array.hpp](/include/Array/Array.hpp)
- [X] [Array_ConstIterator.hpp](/include/Array/Array_ConstIterator.hpp)
- [X] [Array_Iterator.hpp](/include/Array/Array_Iterator.hpp)

### Dynamic Array

> 동적 배열 템플릿 클래스

- [ ] [Vector.hpp](/include/Vector/Vector.hpp)
- [ ] [Vector_ConstIterator.hpp](/include/Vector/Vector_ConstIterator.hpp)
- [ ] [Vector_Iterator.hpp](/include/Vector/Vector_Iterator.hpp)


### Doubly Linked List

> 이중 연결 리스트 템플릿 클래스

- [ ] [List.hpp](/include/List/List.hpp)
- [ ] [List_ConstIterator.hpp](/include/List/List_ConstIterator.hpp)
- [ ] [List_Iterator.hpp](/include/List/List_Iterator.hpp)

### Singly Linked List

> 단일 연결 리스트 템플릿 클래스

- [ ] ForwardList.hpp
- [ ] ForwardList_ConstIterator.hpp
- [ ] ForwardList_Iterator.hpp

### Heap

- [ ] Heap

### Queue

- [ ] Queue
- [ ] Deque
- [ ] Queue<sup>Circular</sup>
- [ ] Priority Queue

### Stack

- [ ] Stack

### Matrix 

- [ ] Matrix

## Non-Linear Data Structures

### Trees

- [ ] Binary Tree

### Graphs

- [ ] Graph<sup>with Adjacent List</sup>
- [ ] Graph<sup>with Adjacent Matrix</sup>

## Other Data Structures

- [ ] Pair
- [ ] Tuple
- [ ] HashMap
- [ ] HashSet

### FVector2

> 2 개의 실수를 저장하는 벡터 클래스

- [X] [FVector2.h](/include/FVector2/FVector2.h)
- [X] [FVector2.cpp](/src/FVector2/FVector2.cpp)

### FVector3

> 3 개의 실수를 저장하는 벡터 클래스

- [X] [FVector3.h](/include/FVector3/FVector3.h)
- [X] [FVector3.cpp](/src/FVector3/FVector3.cpp)

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