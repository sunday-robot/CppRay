#pragma once

#include "Hittable.h"
#include <vector>

class HittableList : public Hittable {
	const std::vector<const Hittable*> _objects;

public:
	HittableList(const std::vector<const Hittable*> hittables) : _objects(hittables) {}

	bool hit(const Ray& r, double tMin, double tMax, HitRecord *rec) const;

	Aabb boundingBox(double exposureTime) const;
};
