#include <iostream>
#include <vector>

using namespace std;

// clang-format off

auto main() -> int
{
    vector<int> vec{1, 2, 3, 4, 5};

    // clang-format off
    #define PSC(VectorName) \
        cout << "- Size: " << VectorName.size() << endl; \
        cout << "- Capacity: " << VectorName.capacity() << '\n' << endl;

    PSC(vec)

    cout << "vec.reserve(10);\n";
    vec.reserve(10);

    PSC(vec)

    cout << "vec.reserve(5);\n";
    vec.reserve(5);

    PSC(vec)

    cout << "vec.reserve(1);\n";
    vec.reserve(1);

    PSC(vec)

    cout << "vec.reserve(20);\n";
    vec.reserve(20);

    PSC(vec)

    return 0;
}
