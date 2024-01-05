#pragma once

#include "Hittable.h"
#include "Aabb.h"
#include "HittableList.h"
#include "Vec3.h"
#include "Material.h"
#include "XyRect.h"
#include "XzRect.h"
#include "YzRect.h"

class Box : public Hittable {
	const HittableList _sides;
	const Aabb _aabb;

	static HittableList createSides(const Vec3& p0, const Vec3& p1, std::shared_ptr<const Material> material) {
		auto top = new XzRect(p0.x(), p0.z(), p1.x(), p1.z(), p0.y(), material);
		auto bottom = new XzRect(p0.x(), p0.z(), p1.x(), p1.z(), p1.y(), material);
		auto front = new XyRect(p0.x(), p0.y(), p1.x(), p1.y(), p1.z(), material);
		auto rear = new XyRect(p0.x(), p0.y(), p1.x(), p1.y(), p0.z(), material);
		auto left = new YzRect(p0.y(), p0.z(), p1.y(), p1.z(), p1.x(), material);
		auto right = new YzRect(p0.y(), p0.z(), p1.y(), p1.z(), p0.x(), material);
		std::vector<std::shared_ptr<const Hittable>> r{
			std::shared_ptr<const Hittable>(top),
				std::shared_ptr<const Hittable>(bottom),
				std::shared_ptr<const Hittable>(front),
				std::shared_ptr<const Hittable>(rear),
				std::shared_ptr<const Hittable>(left),
				std::shared_ptr<const Hittable>(right),
		};
		return r;
	}

public:
	Box(const Vec3& p0, const Vec3& p1, std::shared_ptr < const  Material> material) :
		_sides(createSides(p0, p1, material)),
		_aabb(Aabb(p0, p1)) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const { return _sides.hit(ray, tMin, tMax, rec); }
};
