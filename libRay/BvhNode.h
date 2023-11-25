#pragma once

#include "Bvh.h"

class BvhNode : public Bvh {
	const Bvh* _left;
	const Bvh* _right;
public:
	BvhNode(const Aabb& aabb, const Bvh* left, const Bvh* right)
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

	//public override void Print(string indent = "")
	//{
	//    Console.WriteLine($"{indent}aabb = {_aabb}");
	//    Console.WriteLine($"{indent}left:");
	//    _left.Print(indent + "  ");
	//    Console.WriteLine($"{indent}right:");
	//    _right.Print(indent + "  ");
	//}
};
