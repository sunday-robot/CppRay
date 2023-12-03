#include "BvhLeaf.h"
#include <iostream>

void BvhLeaf::print(int depth) const {
	printIndent(depth);
	std::cout << "aabb = ";
	_aabb.print();
	std::cout << std::endl;

#if false
	printIndent(depth);
	_hittable->print();
	std::cout << std::endl;
#endif
}
