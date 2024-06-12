# **RDS** <sub>*Data Structures & Algorithms in C++*</sub>

[![wakatime](https://wakatime.com/badge/github/nachiketa3299/RDS.svg)](https://wakatime.com/badge/github/nachiketa3299/RDS)

## 방향성
- 표준 라이브러리의 내용을 최대한 그대로 구현해보려고 했으나, 표준 라이브러리를 제대로 사용하는 것으로 방향성 변경

## 사용된 도구들

- 텍스트 에디터
    - Visual Studio Code
- 빌드 자동화 도구
    - CMake (3.27.0)
- 환경
    - Windows 11 Pro(x64)<sup>Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz 2.20 GHz, 16GB RAM</sup>
- 테스트한 컴파일러
    - MSVC 
        - Visual Studio 2022 Community Release (x64)
            - 알 수 없는 오류로 Configure가 되지 않음 (재설치로 해결)
        - Visual Studio 2019 Community Release (x64)
            - PC 포맷 후 2019 설치가 날아가서 현재는 잠정 중단
    - [X] MSYS g++
    - [ ] Clang
- 정적 분석 도구
    - clang-tidy
- 테스트
    - Google Test
    - 자체 테스트
- 포매팅
    - clang-format
- 문서화
    - Doxygen

# *RDS* <sup><i>outlines</i></sup>

## Utilities

- **Cores**
    - [RDS_CoreDefs.h](/include/RDS_CoreDefs.h)
    - [RDS_Concepts.h](/include/RDS_Concepts.h)
- **Assertion**
    - [Assertion.h](/include/Assertion/Assertion.h)
    - [Assertion.cpp](/src/Assertion/Assertion.cpp)

## 선형 자료구조

- 정적 배열(Static Array)
    - [Array.hpp](/include/Array/Array.hpp)
    - [Array_ConstIterator.hpp](/include/Array/Array_ConstIterator.hpp)
    - [Array_Iterator.hpp](/include/Array/Array_Iterator.hpp)
- 동적 배열(Dynamic Array)
    - [Vector.hpp](/include/Vector/Vector.hpp)
    - [Vector_ConstIterator.hpp](/include/Vector/Vector_ConstIterator.hpp)
    - [Vector_Iterator.hpp](/include/Vector/Vector_Iterator.hpp)
- 이중 연결 리스트(Doubly Linked List)
    - [List.hpp](/include/List/List.hpp)
    - [List_ConstIterator.hpp](/include/List/List_ConstIterator.hpp)
    - [List_Iterator](/include/List/List_Iterator.hpp)
- 단일 연결 리스트(Singly Linked List)
    - [ForwardList.hpp](/include/ForwardList/ForwardList.hpp)
    - [ForwardList_ConstIterator.hpp](/include/ForwardList/ForwardList_ConstIterator.hpp)
    - [ForwardList_Iteartor.hpp](/include/ForwardList/ForwardList_Iterator.hpp)
- 벡터(FVector)
    - [RDS_FVectors.h](/include/RDS_FVectors.h)
    - **2차원 벡터(FVector2)**
        - [FVector2.h](/include/FVector2/FVector2.h)
        - [FVector2.cpp](/src/FVector2/FVector2.cpp)
    - **3차원 벡터(FVector3)**
        - [FVector3.h](/include/FVector3/FVector3.h)
        - [FVector3.cpp](/src/FVector3/FVector3.cpp)
- 힙
- 큐
    - Queue
    - Circular Queue
    - Priority Queue
- 스택
- 행렬
    - 희소 행렬
- Pair
- Tuple
- 해시 테이블
- 해시 셋

## 비선형 자료구조

- 트리
    - 이진 트리
- 그래프
    - 인접 리스트를 사용하는 그래프
    - 인접 행렬을 사용하는 그래프

## 알고리즘

### 정렬 알고리즘

- [ ] Bubble Sort
- [ ] Selection Sort
- [ ] Insertion Sort
- [ ] Quick Sort
- [ ] Merge Sort
- [ ] Heap Sort

### 최단 경로 알고리즘

- [ ] BFS<sup>Breadth-frist Search</sup>
- [ ] DFS<sup>Depth-first Search</sup>
- [ ] Dijkstra Algorithm
- [ ] Floyd-Warshall Algorithm

### 최소 신장 트리

- [ ] Kruskal's Algorithm
- [ ] Prim's Algorithm

### 기타

- [ ] Union-find 

# References

- [stlmp/stmlp/Github](https://github.com/stlmp/stlmp)
- [gtest-cmake-example/dmonopoly](https://github.com/dmonopoly/gtest-cmake-example)