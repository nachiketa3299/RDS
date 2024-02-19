#include <iostream>

using namespace std;

// clang-format off

class ParentWithoutVTable
{
char m_empty;
};

class ParentWithVTable
{
public: virtual ~ParentWithVTable() {};
};

class Derived: public ParentWithoutVTable, public ParentWithVTable
{
};

// clang-format on
auto main() -> int
{
    ParentWithoutVTable* p = new Derived();

    Derived* a = reinterpret_cast<Derived*>(p); // (1) Fail
    // Fails because the ParentWithoutVTable* pointer does not point at the beginning of
    // the newly created Derived object in memory, but somewhere else.
    // Visual C++ puts the virtual table pointer as the first element of the class, so
    // the real layout of Derived is something like:
    // struct __Derived
    // {
    //     function_ptr vtable; char empty;
    // };
    Derived* b = static_cast<Derived*>(p); // (2) Work
    Derived* c = (Derived*)(p);            // (3) depends on
    return 0;
}
