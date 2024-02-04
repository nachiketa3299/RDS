# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

**사용 도구**

- Visual Studio Code
- CMake (3.27.0) 
- MSYS g++
- Google Test

# Plans

- [ ] Doxygen 사용 설정
- [ ] VSCode `tasks.json` 에 Cmake 명령어 등록
- [ ] `Vector2`, `Vector3` 클래스의 이름을 `FVector2`, `FVector3`으로 바꿀 것
    - 동적 배열 클래스 이름을 `Vector`로 할 거라서 이름이 겹칠 위험이 있음.
    - 의미적으로도 `float` 형을 2, 3개 모아둔 자료형이니 접두어 `F`를 붙이는게 맞을 듯.

# Implemenation

모두 `rds` 네임스페이스에 선언 및 정의되어 있음.

## Utilities

### Assertion

- [X] [Assertion.h](/include/Assertion/Assertion.h)<sup>Macro function <code>RDS_Assert</code></sup>
- [X] [Assertion.cpp](/src/Assertion/Assertion.cpp)

## Data Structures

### (Ref) Iterator Categories

| Container | Iterator Category |
| :-: | :-:|
| Vector | Random-Access |
| List | Bidirectional |
| Deque | Random-Access |
| Map | Bidirectional |
| Multimap | Bidirectional |
| Set | Bidirectional |
| MultiSet | Bidirectional |
| Stack | None |
| Queue | None |
| Priority-Queue | None |


#### Vector2

- [X] [Vector2.h](/include/Vector2/Vector2.h)
- [X] [Vector2.cpp](/src/Vector2/Vector2.cpp)

#### Vector3

- [X] [Vector3.h](/include/Vector3/Vector3.h)
- [X] [Vector3.cpp](/src/Vector3/Vector3.cpp)

### Static Array

- [X] [Array.hpp](/include/Array/Array.hpp)
- [X] [Array_ConstIterator.hpp](/include/Array/Array_ConstIterator.hpp)
- [X] [Array_Iterator.hpp](/include/Array/Array_Iterator.hpp)

### Dynamic Array
- [ ] DArray

### Others
- [ ] Adjacent Matrix
- [ ] List<sup>Doubly linked</sup>
- [ ] ForwardList<sup>Singly linked</sup>
- [ ] Graph<sup>with Adjacent List</sup>
- [ ] Graph<sup>with Adjacent Matrix</sup>
- [ ] Stack
- [ ] Queue
- [ ] Deque
- [ ] Queue<sup>Circular</sup>
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


# Tests

- Vector2
- Vector3


# References

- [stlmp/stmlp/Github](https://github.com/stlmp/stlmp)
- [gtest-cmake-example/dmonopoly](https://github.com/dmonopoly/gtest-cmake-example)
    - 유용한 GTest 예제 (아직 이해하지 못한 부분이 있음)
