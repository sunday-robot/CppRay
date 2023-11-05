#include "HittableList.h"

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord *rec) const {
	auto closestSoFar = tMax;
	bool hit = false;

	for (auto hittable = _objects.begin(); hittable != _objects.end(); hittable++) {
		HitRecord tmp;
		if ((*hittable)->hit(r, tMin, closestSoFar, &tmp)) {
			hit = true;
			closestSoFar = tmp.t;
			*rec = tmp;
		}
	}
	return hit;
}

Aabb HittableList::boundingBox(double exposureTime) const {
	auto box = _objects[0]->boundingBox(exposureTime);
	for (auto i = 1; i < _objects.size(); i++) {
		box = Aabb::surroundingAabb(box, _objects[i]->boundingBox(exposureTime));
	}
	return box;
}
