#pragma once

#include "Ray.h"
#include "Vec3.h"

// Axis Aligned Bounding Box
class Aabb {
	Vec3 _min;
	Vec3 _max;

public:
	Aabb(const Vec3& min, const Vec3& max) :_min(min), _max(max) {}

	const Vec3& min() const { return _min; }
	const Vec3& max() const { return _max; }

	Aabb operator =(const Aabb& a) {
		_min = a._min;
		_max = a._max;
		return *this;
	}

	bool hit(const Ray& ray, double tMin, double tMax) const;

	static Aabb surroundingAabb(const Aabb& a, const Aabb& b);

	//public override string ToString()
	//{
	//    return $"{Min}-{Max}";
	//}
};
