#pragma once

#include "Hittable.h"

class RotateY : public Hittable {
	const Hittable* _ptr;
	const double _sin;
	const double _cos;

	RotateY(const Hittable* p, double sin, double cos)
		: _ptr(p),
		_sin(sin),
		_cos(cos) {}

	RotateY(const Hittable* p, double angleInRadians)
		: RotateY(
			p,
			sin(angleInRadians),
			cos(angleInRadians)) {}

	inline Vec3 rotate(const Vec3 v) const;
	inline Vec3 rotateOpposite(const Vec3 v) const;

public:
	static RotateY* create(const Hittable* p, double angleInDegrees);
	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;
	Aabb boundingBox(double exposureTime) const;
};
