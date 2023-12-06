#include "Vec3.h"
#include <iostream>
#include <iomanip>

// Œ´“_
const Vec3 Vec3::o = Vec3(0, 0, 0);

void Vec3::print() const {
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "(" << _x << ", " << _y << ", " << _z << ")";
	std::cout << std::defaultfloat;
}
