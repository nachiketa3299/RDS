#include <iostream>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

namespace rds
{

using namespace std;

auto __assert(bool exp, const char* exp_str, const char* file_str,
              long int line) -> void
{
    if (exp)
        return;

    {
        cerr << "> RDS: Assertion Failed!\n";
        cerr << "\t- Expr: " << exp_str << '\n';
        cerr << "\t- File: " << file_str << '\n';
        cerr << "\t- Line: " << line << '\n';
    }

    exit(EXIT_FAILURE);
}

auto __error(const char* message, const char* file_str, long int line) -> void
{
    {
        cerr << "> RDS: Error!\n";
        cerr << "\t- Msgs: " << message << '\n';
        cerr << "\t- File: " << file_str << '\n';
        cerr << "\t- Line: " << line << '\n';
    }

    exit(EXIT_FAILURE);
}

} // namespace rds