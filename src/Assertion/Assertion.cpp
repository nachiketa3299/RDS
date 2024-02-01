#include <iostream>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

RDS_BEGIN
using namespace std;

void _rds_assert(bool exp, const char* exp_str, const char* file_str, long int line)
{
    if (exp)
        return;

    cerr << "> RDS: Assertion Failed!\n";
    cerr << "\t- File: " << file_str << '\n';
    cerr << "\t- Line: " << line << '\n';
    cerr << "\t- Expr: " << exp_str << '\n';
    exit(EXIT_FAILURE);
}

RDS_END