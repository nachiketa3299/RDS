# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

**사용 도구**

- (Text Editor) **Visual Studio Code**
- (Build Automation) **CMake (3.27.0)**
- (Compilers) **MSYS g++** / **MSVC**
- (Test) **Google Test**
- (Formatting) **clang-format**
- (Document) **Doxygen**

# Plans

- [ ] Doxygen 사용 설정
- [X] `Vector2`, `Vector3` 클래스의 이름을 `FVector2`, `FVector3`으로 바꿀 것
    - 동적 배열 클래스 이름을 `Vector`로 할 거라서 이름이 겹칠 위험이 있음.
    - 의미적으로도 `float` 형을 2, 3개 모아둔 자료형이니 접두어 `F`를 붙이는게 맞을 듯.

# Implemenation

- 모두 `rds` 네임스페이스에 선언 및 정의되어 있음.
- 템플릿 클래스의 경우 확장자 `*.hpp` 로 표현하며, 한 파일에 선언과 구현이 모두 들어있다.
- 파일의 이름은 모두 파일이 보유하고 있는 클래스 이름과 정확히 일치한다.

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
