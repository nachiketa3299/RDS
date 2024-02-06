#include <gtest/gtest.h>

#include "Arena.hpp"

struct A
{
    char a = 'a';
    char b = 'b';
};

struct C
{
    char c = 'c';
    char d = 'd';
    char e = 'e';
};

TEST(Arena_test, BasicTest)
{
    rds::Arena<100> arena;

    char            buffer[200];
    auto*           ptr = buffer;
    new (ptr) A{};
    auto* a_ptr  = reinterpret_cast<A*>(ptr);
    ptr         += sizeof(A);

    new (ptr) C{};
    auto* c_ptr = reinterpret_cast<C*>(ptr);
}
