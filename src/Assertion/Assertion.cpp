/// @file Assertion.cpp

#include <iostream>

#include "Assertion.h"
#include "RDS_CoreDefs.h"

using namespace std;

RDS_BEGIN

void rds_assert(bool exp, const char* exp_str, const char* file_str, long int line)
{
    if (exp)
        return;

    cerr << "> RDS: Assertion Failed!\n";
    cerr << "\t- Expr: " << exp_str << '\n';
    cerr << "\t- File: " << file_str << '\n';
    cerr << "\t- Line: " << line << '\n';
    exit(EXIT_FAILURE);
}

void rds_error(const char* message, const char* file_str, long int line)
{
    cerr << "> RDS: Error!\n";
    cerr << "\t- Msgs: " << message << '\n';
    cerr << "\t- File: " << file_str << '\n';
    cerr << "\t- Line: " << line << '\n';
    exit(EXIT_FAILURE);
}

RDS_END