#pragma once

#include <memory>
#include "Hittable.h"
#include "Vec3.h"

class Translate : public Hittable {
	const std::shared_ptr<const Hittable> _ptr;
	const Vec3 _offset;

public:
	Translate(std::shared_ptr<const Hittable> p, const Vec3& displacement)
		: _ptr(p), _offset(displacement) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto movedR = Ray(ray.origin() - _offset, ray.direction(), ray.time());

		if (!_ptr->hit(movedR, tMin, tMax, rec))
			return false;

		rec->position += _offset;
		return true;
	}

	Aabb boundingBox(double exposureTime) const {
		auto b = _ptr->boundingBox(exposureTime);
		return Aabb(
			b.min() + _offset,
			b.max() + _offset);
	}
};
