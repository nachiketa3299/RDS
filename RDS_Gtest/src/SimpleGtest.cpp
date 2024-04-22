#include "RDS/Array.hpp"
#include <iostream>

using namespace rds;
using namespace std;

auto main() -> int
{
	Array<int, 4> arr = {1, 2, 3, 4};
	for (auto it = arr.CBegin(); it != arr.CEnd(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}