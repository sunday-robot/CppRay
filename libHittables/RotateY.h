#pragma once

#include "Hittable.h"
#include "Aabb.h"

class RotateY : public Hittable {
	const Hittable* _ptr;
	const double _sin;
	const double _cos;
	const Aabb _bbox;

	RotateY(const Hittable* p, double sin, double cos, const Aabb& bbox)
		: _ptr(p),
		_sin(sin),
		_cos(cos),
		_bbox(bbox) {}

	RotateY(const Hittable* p, double angleInRadians)
		: RotateY(
			p,
			sin(angleInRadians),
			cos(angleInRadians),
			p->boundingBox(0)) {}

	inline Vec3 rotate(const Vec3 v) const;
	inline Vec3 rotateOpposite(const Vec3 v) const;

public:
	static RotateY* create(const Hittable* p, double angleInDegrees);
	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;
	Aabb boundingBox(double exposureTime) const { return _bbox; }
};
