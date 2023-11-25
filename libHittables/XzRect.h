#pragma once

#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class XzRect : public Hittable {
	double _x0;
	double _z0;
	double _x1;
	double _z1;
	double _y;
	const Material* _material;
	const Aabb _aabb;
public:
	XzRect(double x0, double z0, double x1, double z1, double y, Material* material) :
		_x0(x0),
		_z0(z0),
		_x1(x1),
		_z1(z1),
		_y(y),
		_material(material),
		// The bounding box must have non-zero width in each dimension, so pad the Z
		// dimension a small amount.
		_aabb(Aabb(Vec3(x0, y - 0.0001, z0), Vec3(x1, y + 0.0001, z1))) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto t = (_y - ray.origin().y) / ray.direction().y;
		if (t < tMin || t > tMax)
			return false;

		auto x = ray.origin().x + t * ray.direction().x;
		auto z = ray.origin().z + t * ray.direction().z;
		if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
			return false;

		rec->position = ray.positionAt(t);
		auto outwardNormal = Vec3(0, 1, 0);
		auto ff = ray.direction().dot(outwardNormal) < 0;
		rec->normal = ff ? outwardNormal : -outwardNormal;
		rec->u = (x - _x0) / (_x1 - _x0);
		rec->v = (z - _z0) / (_z1 - _z0);
		rec->material = _material;
		rec->t = t;
		rec->frontFace = ff;
		return true;
	}
};
