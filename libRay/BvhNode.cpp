#include "BvhNode.h"
#include <iostream>

void BvhNode::print(int depth) const {
	printIndent(depth);
	std::cout << "aabb = ";
	_aabb.print();
	std::cout << std::endl;

	printIndent(depth);
	std::cout << "left:" << std::endl;
	_left->print(depth + 1);

	printIndent(depth);
	std::cout << "right:" << std::endl;
	_right->print(depth + 1);
}
