#pragma once
#include <memory>
#include <vector>
#include "Hittable.h"

class HittableList : public Hittable {
	std::vector<std::shared_ptr<const Hittable>> _objects;

public:
	HittableList() {}
	HittableList(std::vector<std::shared_ptr<const Hittable>> objects) : _objects(objects) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const override;

	Aabb boundingBox(double exposureTime) const override;

	void add(std::shared_ptr<const Hittable> object) {
		_objects.push_back(object);
	}

	size_t size() const { return _objects.size(); }

	std::shared_ptr<const Hittable> get(size_t index) const { return _objects[index]; }
};
