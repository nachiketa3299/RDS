#include "Array.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    rds::Array<int, 10> arr;
    for (auto it = arr.CBegin(); it != arr.CEnd(); ++it)
    {
        std::cout << *it << ' ';
    }
    return EXIT_SUCCESS;
}