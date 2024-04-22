# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

[![wakatime](https://wakatime.com/badge/github/nachiketa3299/RDS.svg)](https://wakatime.com/badge/github/nachiketa3299/RDS)

## 사용된 도구들

- 텍스트 에디터
    - Visual Studio Code
- 빌드 자동화 도구
    - CMake (3.27.0)
- 환경
    - Windows 11 Pro(x64)<sup>Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz 2.20 GHz, 16GB RAM</sup>
- 컴파일러
    - [ ] MSVC 
        - Visual Studio 2022 Community Release (x64)
            - 알 수 없는 오류로 Configure가 되지 않음
        - Visual Studio 2019 Community Release (x64)
            - PC 포맷 후 2019 설치가 날아가서 현재는 잠정 중단
    - [X] MSYS g++
        - 문제 없이 컴파일
    - [ ] Clang
- 정적 분석 도구
    - Clang-tidy
        - 쓰다가 잠정 중단
- 테스트
    - Google Test
- 포매팅
    - clang-format
        - 쓰다가 잠정 중단
- 문서화
    - Doxygen

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