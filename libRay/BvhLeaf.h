#pragma once

#include "Bvh.h"

class BvhLeaf : public Bvh {
	const Hittable* _hittable;
public:
	BvhLeaf(Aabb aabb, Hittable* hittable) : Bvh(aabb), _hittable(hittable) {}

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

	//public override void Print(string indent = "")
	//{
	//	Console.WriteLine($"{indent}aabb = {_aabb}");
	//	Console.WriteLine($"{indent}{_hittable}");
	//}
};
