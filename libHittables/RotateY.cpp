#include "RotateY.h"

#include <algorithm>
#include <float.h>
#define _USE_MATH_DEFINES	// M_PIを使用するにはこれを定義したうえでmath.hをincludeしなければならないとのこと。
#include <math.h>

RotateY* RotateY::create(const Hittable* p, double angleInDegrees) {
	return new RotateY(p, angleInDegrees / 180 * M_PI);
}

Vec3 RotateY::rotate(const Vec3 v) const {
	auto x = _cos * v.x() - _sin * v.z();
	auto y = v.y();
	auto z = _sin * v.x() + _cos * v.z();
	return Vec3(x, y, z);
}

Vec3 RotateY::rotateOpposite(const Vec3 v) const {
	auto x = _cos * v.x() + _sin * v.z();
	auto y = v.y();
	auto z = -_sin * v.x() + _cos * v.z();
	return Vec3(x, y, z);
}

bool RotateY::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	auto origin = rotate(ray.origin());
	auto direction = rotate(ray.direction());
	auto rotatedR = Ray(origin, direction, ray.time());

	HitRecord tmpRec;
	if (!_ptr->hit(rotatedR, tMin, tMax, &tmpRec))
		return false;

	auto p = rotateOpposite(tmpRec.position);
	auto n = rotateOpposite(tmpRec.normal);
	auto ff = ray.direction().dot(n) < 0;
	if (!ff)
		n = -n;

	rec->position = p;
	rec->normal = n;
	rec->material = tmpRec.material;
	rec->t = tmpRec.t;
	// u,vは参照されないので設定しない。
	rec->frontFace = ff;

	return true;
}

Aabb RotateY::boundingBox(double exposureTime) const {
	Vec3 min(DBL_MAX, DBL_MAX, DBL_MAX);
	Vec3 max(-DBL_MAX, -DBL_MAX, -DBL_MAX);

	auto bbox = _ptr->boundingBox(exposureTime);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				auto x = i * bbox.max().x() + (1 - i) * bbox.min().x();
				auto y = j * bbox.max().y() + (1 - j) * bbox.min().y();
				auto z = k * bbox.max().z() + (1 - k) * bbox.min().z();

				auto tester = rotateOpposite(Vec3(x, y, z));

				min = Vec3(fmin(min.x(), tester.x()), fmin(min.y(), tester.y()), fmin(min.z(), tester.z()));
				max = Vec3(fmax(max.x(), tester.x()), fmax(max.y(), tester.y()), fmax(max.z(), tester.z()));
			}
		}
	}

	return Aabb(min, max);
}
