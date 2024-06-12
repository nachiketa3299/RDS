#include <vector>
#include <RDS/vector.h>

int main() {

	rds::vector<int> v(2, 3);
	v.reserve(10);
}