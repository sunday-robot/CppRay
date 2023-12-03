#pragma once
#include <vector>
#include "Hittable.h"

class HittableList : public Hittable {
	std::vector<const Hittable*> _objects;

public:
	HittableList() {}
	HittableList(std::vector<const Hittable*> objects) : _objects(objects) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const override;

	Aabb boundingBox(double exposureTime) const override;

	void add(const Hittable* object) {
		_objects.push_back(object);
	}

	size_t size() const { return _objects.size(); }

	const Hittable* get(size_t index) const { return _objects[index]; }
};
