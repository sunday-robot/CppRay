#include "RotateY.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <algorithm>

RotateY* RotateY::create(const Hittable* p, double angleInDegrees) {
	return new RotateY(p, angleInDegrees / 180 * M_PI);
}

Vec3 RotateY::rotate(const Vec3 v)const {
	auto x = _cos * v.x - _sin * v.z;
	auto y = v.y;
	auto z = _sin * v.x + _cos * v.z;
	return Vec3(x, y, z);
}

static Aabb getBoundingBox(const Aabb& bbox, double sinTheta, double cosTheta) {
	auto minX = DBL_MAX;
	auto minY = DBL_MAX;
	auto minZ = DBL_MAX;
	auto maxX = -DBL_MAX;
	auto maxY = -DBL_MAX;
	auto maxZ = -DBL_MAX;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * bbox.max().x + (1.0 - i) * bbox.min().x;
				auto y = j * bbox.max().y + (1.0 - j) * bbox.min().y;
				auto z = k * bbox.max().z + (1.0 - k) * bbox.min().z;

				auto newx = cosTheta * x + sinTheta * z;
				auto newz = -sinTheta * x + cosTheta * z;

				minX = std::min(minX, newx);
				maxX = std::max(maxX, newx);
				minY = std::min(minY, y);
				maxY = std::max(maxY, y);
				minZ = std::min(minZ, newz);
				maxZ = std::max(maxZ, newz);
			}
		}
	}

	return Aabb(Vec3(minX, minY, minZ), Vec3(maxX, maxY, maxZ));
}

bool RotateY::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	auto origin = rotate(ray.origin());
	auto direction = rotate(ray.direction());
	auto rotatedR = Ray(origin, direction, ray.time());

	HitRecord tmpRec;
	if (!_ptr->hit(rotatedR, tMin, tMax, &tmpRec))
		return false;

	auto p = rotate(tmpRec.position);
	auto n = rotate(tmpRec.normal);
	auto ff = ray.direction().dot(n) < 0;
	if (!ff)
		n = -n;

	rec->position = p;
	rec->normal = n;
	rec->material = tmpRec.material;
	rec->t = tmpRec.t;
	// u,v‚ÍŽQÆ‚³‚ê‚È‚¢‚Ì‚ÅÝ’è‚µ‚È‚¢B
	rec->frontFace = ff;

	return true;
}
