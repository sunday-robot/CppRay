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

public:
	Box(const Vec3& p0, const Vec3& p1, Material* material)
		: _sides(HittableList(std::vector<const Hittable*>{
		new XyRect(p0.x, p0.y, p1.x, p1.y, p1.z, material),
			new XyRect(p0.x, p0.y, p1.x, p1.y, p0.z, material),
			new XzRect(p0.x, p0.z, p1.x, p1.z, p1.y, material),
			new XzRect(p0.x, p0.z, p1.x, p1.z, p0.y, material),
			new YzRect(p0.y, p0.z, p1.y, p1.z, p1.x, material),
			new YzRect(p0.y, p0.z, p1.y, p1.z, p0.x, material)})),
		_aabb(Aabb(p0, p1)) {}

	Aabb boundingBox(double exposureTime) const { return _aabb; }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const { return _sides.hit(ray, tMin, tMax, rec); }
};
