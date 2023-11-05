#pragma once
#include "Hittable.h"
#include "Vec3.h"

class Translate : public Hittable {
	const Hittable* _ptr;
	const Vec3 _offset;

public:
	Translate(const Hittable* p, const Vec3& displacement)
		: _ptr(p), _offset(displacement) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto movedR = Ray(ray.origin() - _offset, ray.direction(), ray.time());
		HitRecord tmpRec;
		if (!_ptr->hit(movedR, tMin, tMax, &tmpRec))
			return false;

		auto p = tmpRec.position + _offset;
		auto ff = movedR.direction().dot(tmpRec.normal) < 0;
		auto  n = ff ? tmpRec.normal : -tmpRec.normal;

		rec->position = p;
		rec->normal = n;
		rec->material = tmpRec.material;
		rec->t = tmpRec.t;
		// u, v‚ÍŽQÆ‚³‚ê‚È‚¢‚Ì‚ÅÝ’è‚µ‚È‚¢B
		rec->frontFace = ff;
		return true;
	}

	Aabb boundingBox(double exposureTime) const {
		auto b = _ptr->boundingBox(exposureTime);
		return Aabb(
			b.min() + _offset,
			b.max() + _offset);
	}
};
