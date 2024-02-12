# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

계획 및 일지는 [여기](.\docs\mds\Plans.md)를 참조

## Tools

- (Text Editor) **Visual Studio Code**
- (Build Automation) **CMake (3.27.0)**
    - [CMakeList.txt](/CMakeLists.txt) <sub>기본 빌드 설정</sub>
    - [RDS_CMakeVars.cmake](/RDS_CMakeVars.cmake) <sub>빌드 설정 위한 변수 및 매크로 정의</sub>
- (Compilers)
    - MSVC (Visual Studio 2019)
    - MSYS g++
    - Clang
- (Static Analysis) **Clang-tidy**
- (Test) **Google Test**
- (Formatting) **clang-format**
- (Document) **Doxygen**

# Implemenation

- 최상위 네임스페이스는 `rds`
- 템플릿 클래스의 경우 확장자 `*.hpp` 로 표현하며, 한 파일에 선언과 구현이 모두 들어있다.

컨테이너 템플릿 클래스의 경우 다음의 순으로 멤버를 정의  

1. Type Alias
2. Inner Class/Struct
3. Ctor/Dtor
5. Element Access
6. Iterators
7. Capacity
8. Modifiers
9. Operations
10. Members

## Utilities

### Cores

- [RDS_CoreDefs.h](/include/RDS_CoreDefs.h)
- [RDS_Concepts.h](/include/RDS_Concepts.h)

### Assertion

- [X] [Assertion.h](/include/Assertion/Assertion.h)<sup>Macro function <code>RDS_Assert</code></sup>
- [X] [Assertion.cpp](/src/Assertion/Assertion.cpp)

## Data Structures

### FVector2

> 2 개의 `float` 을 저장하는 벡터 클래스

- [X] [FVector2.h](/include/FVector2/FVector2.h)
- [X] [FVector2.cpp](/src/FVector2/FVector2.cpp)

### FVector3

> 3 개의 `float` 을 저장하는 벡터 클래스

- [X] [FVector3.h](/include/FVector3/FVector3.h)
- [X] [FVector3.cpp](/src/FVector3/FVector3.cpp)

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

### Linked List

#### Doubly Linked List

> 이중 연결 리스트 템플릿 클래스

- [ ] [List.hpp](/include/List/List.hpp)
- [ ] [List_ConstIterator.hpp](/include/List/List_ConstIterator.hpp)
- [ ] [List_Iterator.hpp](/include/List/List_Iterator.hpp)

#### Singly Linked List

> 단일 연결 리스트 템플릿 클래스

- [ ] ForwardList.hpp
- [ ] ForwardList_ConstIterator.hpp
- [ ] ForwardList_Iterator.hpp

### Container Adapters

#### Heap

- [ ] Heap

#### Queue

- [ ] Queue
- [ ] Deque
- [ ] Queue<sup>Circular</sup>
- [ ] Priority Queue

#### Stack

- [ ] Stack


### Others
- [ ] Adjacent Matrix
- [ ] ForwardList<sup>Singly linked</sup>
- [ ] Graph<sup>with Adjacent List</sup>
- [ ] Graph<sup>with Adjacent Matrix</sup>
- [ ] Binary Tree
- [ ] HashMap
- [ ] HashSet
- [ ] Pair
- [ ] Tuple

## Algorithms

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
    - 유용한 GTest 예제 (아직 이해하지 못한 부분이 있음)
