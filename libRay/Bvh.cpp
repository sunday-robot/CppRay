#include "Bvh.h"
#include <iostream>

bool Bvh::_debugMode = false;

const HitRecord Bvh::_debugModeHitRecord{
	Vec3::o,
	Vec3::o,
	(const Material*)0,
	0.0,
	0.0,
	0.0,
	false
};

void Bvh::printIndent(int depth) {
	std::cout << std::string(depth * 2, ' ');
}
