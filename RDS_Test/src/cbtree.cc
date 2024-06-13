#include <RDS/cbtree.h>

using namespace rds;

int main() {
	cbtree<int> bt(4, 9,true);
	println(bt);
}
