# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

계획 및 일지는 [여기](.\docs\mds\Plans.md)를 참조

## Tools

- (Text Editor) **Visual Studio Code**
- (Build Automation) **CMake (3.27.0)**
- (Compilers) **MSYS g++** / **MSVC**
- (Static Analysis) **Clang-tidy**
- (Test) **Google Test**
- (Formatting) **clang-format**
- (Document) **Doxygen**

# Implemenation

- 모두 `rds` 네임스페이스에 선언 및 정의되어 있음.
- 템플릿 클래스의 경우 확장자 `*.hpp` 로 표현하며, 한 파일에 선언과 구현이 모두 들어있다.
- 파일의 이름은 모두 파일이 보유하고 있는 클래스 이름과 정확히 일치한다.

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

### Assertion

- [X] [Assertion.h](/include/Assertion/Assertion.h)<sup>Macro function <code>RDS_Assert</code></sup>
- [X] [Assertion.cpp](/src/Assertion/Assertion.cpp)

## Data Structures

### Vector2

- [X] [Vector2.h](/include/Vector2/Vector2.h)
- [X] [Vector2.cpp](/src/Vector2/Vector2.cpp)

### Vector3

- [X] [Vector3.h](/include/Vector3/Vector3.h)
- [X] [Vector3.cpp](/src/Vector3/Vector3.cpp)

### Static Array

- [X] [Array.hpp](/include/Array/Array.hpp)
- [X] [Array_ConstIterator.hpp](/include/Array/Array_ConstIterator.hpp)
- [X] [Array_Iterator.hpp](/include/Array/Array_Iterator.hpp)

### Dynamic Array
- [ ] Vector

### LinkedList

#### Singly Linked List

- [ ] ForwardList

#### Doubly Linked List

- [ ] [List.hpp](/include/List/List.hpp)
- [ ] [List_ConstIterator.hpp](/include/List/List_ConstIterator.hpp)
- [ ] [List_Iterator.hpp](/include/List/List_Iterator.hpp)

### Others
- [ ] Adjacent Matrix
- [ ] ForwardList<sup>Singly linked</sup>
- [ ] Graph<sup>with Adjacent List</sup>
- [ ] Graph<sup>with Adjacent Matrix</sup>
- [ ] Stack
- [ ] Queue
- [ ] Deque
- [ ] Queue<sup>Circular</sup>
- [ ] Priority Queue
- [ ] Heap
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
