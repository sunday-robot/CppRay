#pragma once

#include <memory>
#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class YzRect : public Hittable {
	const double _y0;
	const double _z0;
	const double _y1;
	const double _z1;
	const double _k;
	const std::shared_ptr<const Material> _material;
	const Aabb _aabb;
public:
	YzRect(double y0, double z0, double y1, double z1, double k, std::shared_ptr < const Material> material) :
		_y0(y0),
		_z0(z0),
		_y1(y1),
		_z1(z1),
		_k(k),
		_material(material),
		// The bounding box must have non-zero width in each dimension, so pad the Z
		// dimension a small amount.
		_aabb(Aabb(Vec3(k - 0.0001, y0, z0), Vec3(k + 0.0001, y1, z1))) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto t = (_k - ray.origin().x()) / ray.direction().x();
		if (t < tMin || t > tMax)
			return false;

		auto y = ray.origin().y() + t * ray.direction().y();
		auto z = ray.origin().z() + t * ray.direction().z();
		if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
			return false;

		rec->position = ray.positionAt(t);
		auto outwardNormal = Vec3(1, 0, 0);
		auto ff = ray.direction().dot(outwardNormal) < 0;
		rec->normal = ff ? outwardNormal : -outwardNormal;
		rec->u = (y - _y0) / (_y1 - _y0);
		rec->v = (z - _z0) / (_z1 - _z0);

		rec->material = _material.get();
		rec->t = t;
		rec->frontFace = ff;
		return true;
	}
};
