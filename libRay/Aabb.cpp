#include "Aabb.h"
#include <utility>
#include <iostream>

bool Aabb::hit(const Ray& ray, double tMin, double tMax) const {
	double a;
	double b;

	a = (_min.x - ray.origin().x) / ray.direction().x;
	b = (_max.x - ray.origin().x) / ray.direction().x;
	if (a > b) {
		if (b > tMin)
			tMin = b;
		if (a < tMax)
			tMax = a;
	} else {
		if (a > tMin)
			tMin = a;
		if (b < tMax)
			tMax = b;
	}
	if (tMax <= tMin)
		return false;

	a = (_min.y - ray.origin().y) / ray.direction().y;
	b = (_max.y - ray.origin().y) / ray.direction().y;
	if (a > b) {
		if (b > tMin)
			tMin = b;
		if (a < tMax)
			tMax = a;
	} else {
		if (a > tMin)
			tMin = a;
		if (b < tMax)
			tMax = b;
	}
	if (tMax <= tMin)
		return false;

	a = (_min.z - ray.origin().z) / ray.direction().z;
	b = (_max.z - ray.origin().z) / ray.direction().z;
	if (a > b) {
		if (b > tMin)
			tMin = b;
		if (a < tMax)
			tMax = a;
	} else {
		if (a > tMin)
			tMin = a;
		if (b < tMax)
			tMax = b;
	}
	if (tMax <= tMin)
		return false;
	return true;
}

Aabb Aabb::surroundingAabb(const Aabb& a, const Aabb& b) {
	auto minX = std::min(a._min.x, b._min.x);
	auto maxX = std::max(a._max.x, b._max.x);
	auto minY = std::min(a._min.y, b._min.y);
	auto maxY = std::max(a._max.y, b._max.y);
	auto minZ = std::min(a._min.z, b._min.z);
	auto maxZ = std::max(a._max.z, b._max.z);
	return Aabb(Vec3(minX, minY, minZ), Vec3(maxX, maxY, maxZ));
}

void Aabb::print() const {
	_min.print();
	std::cout << "-";
	_max.print();
}
