#pragma once

#include <memory>
#include "Bvh.h"

class BvhNode : public Bvh {
	std::shared_ptr<const Bvh> _left;
	std::shared_ptr<const Bvh> _right;
public:
	BvhNode(const Aabb& aabb, std::shared_ptr<const Bvh> left, std::shared_ptr<const Bvh> right)
		: Bvh(aabb), _left(left), _right(right) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		if (!_aabb.hit(ray, tMin, tMax))
			return false;

		if (isDebugMode() && _left->isLeaf() && _right->isLeaf()) {
			setDebugModeHitRecord(rec);
			return true;
		}

		HitRecord rec1;
		if (_left->hit(ray, tMin, tMax, &rec1)) {
			HitRecord rec2;
			if (_right->hit(ray, tMin, rec1.t, &rec2)) {
				*rec = rec2;
			} else {
				*rec = rec1;
			}
			return true;
		} else
			return _right->hit(ray, tMin, tMax, rec);
	}

	bool isLeaf() const { return false; }

	void print(int depth = 0) const;
};
