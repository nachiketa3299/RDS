# Plans

- [X] Doxygen 사용 설정
    - 루트에 Doxyfiile.config 로 설정, GenerateDoxygen.bat 을 VSCode Task에 등록해서 사용
- [X] `Vector2`, `Vector3` 클래스의 이름을 `FVector2`, `FVector3`으로 바꿀 것
    - 동적 배열 클래스 이름을 `Vector`로 할 거라서 이름이 겹칠 위험이 있음.
    - 의미적으로도 `float` 형을 2, 3개 모아둔 자료형이니 접두어 `F`를 붙이는게 맞을 듯.

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