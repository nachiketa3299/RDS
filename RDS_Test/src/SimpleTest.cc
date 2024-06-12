#include "RDS/Array.hpp"
#include "RDS/List.hpp"
#include <iostream>

using namespace rds;
using namespace std;

int main()
{
	List<int> t_list = {1, 2, 3, 4};
	for (auto it = t_list.CBegin(); it != t_list.CEnd(); ++it)
	{
		cout << *it << endl;
	}

	return 0;
}

