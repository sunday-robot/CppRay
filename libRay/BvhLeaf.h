#pragma once

#include "Bvh.h"

class BvhLeaf : public Bvh {
	const std::shared_ptr<const Hittable> _hittable;
public:
	BvhLeaf(Aabb aabb, std::shared_ptr<const Hittable> hittable) : Bvh(aabb), _hittable(hittable) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		if (!_aabb.hit(ray, tMin, tMax))
			return false;

		if (isDebugMode()) {
			setDebugModeHitRecord(rec);
			return true;
		}

		return _hittable->hit(ray, tMin, tMax, rec);
	}

	bool isLeaf() const { return true; }

	void print(int depth = 0) const;
};
