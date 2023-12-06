#pragma once

#include "Hittable.h"
#include "Material.h"
#include "Aabb.h"

class XyRect : public Hittable {
	double _x0;
	double _y0;
	double _x1;
	double _y1;
	double _k;
	const Material* _material;
	const Aabb _aabb;
public:
	XyRect(double x0, double y0, double x1, double y1, double k, Material* material) :
		_x0(x0),
		_y0(y0),
		_x1(x1),
		_y1(y1),
		_k(k),
		_material(material),
		// The bounding box must have non-zero width in each dimension, so pad the Z
		// dimension a small amount.
		_aabb(Aabb(Vec3(x0, y0, k - 0.0001), Vec3(x1, y1, k + 0.0001))) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto t = (_k - ray.origin().z()) / ray.direction().z();
		if (t < tMin || t > tMax)
			return false;

		auto x = ray.origin().x() + t * ray.direction().x();
		auto y = ray.origin().y() + t * ray.direction().y();
		if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
			return false;

		rec->position = ray.positionAt(t);
		auto outwardNormal = Vec3(0, 0, 1);
		auto ff = ray.direction().dot(outwardNormal) < 0;
		rec->normal = ff ? outwardNormal : -outwardNormal;
		rec->u = (x - _x0) / (_x1 - _x0);
		rec->v = (y - _y0) / (_y1 - _y0);

		rec->material = _material;
		rec->t = t;
		rec->frontFace = ff;
		return true;
	}
};
