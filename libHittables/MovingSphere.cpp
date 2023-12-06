#include "MovingSphere.h"
#include "Uv.h"
#define _USE_MATH_DEFINES
#include <math.h>

Uv getSphereUv(Vec3 p) {
	// p: a given point on the sphere of radius one, centered at the origin.
	// u: returned value [0,1] of angle around the Y axis from X=-1.
	// v: returned value [0,1] of angle from Y=-1 to Y=+1.
	//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
	//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
	//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>
	auto theta = acos(-p.y());
	auto phi = atan2(-p.z(), p.x()) + M_PI;
	auto u = phi / (2 * M_PI);
	auto v = theta / M_PI;
	return Uv{ u, v };
}

bool MovingSphere::hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
	auto center = _centerT0 + _velocity * ray.time();
	auto oc = ray.origin() - center;
	auto a = ray.direction().squaredLength();
	auto halfB = oc.dot(ray.direction());
	auto c = oc.squaredLength() - _radius * _radius;

	auto discriminant = halfB * halfB - a * c;
	if (discriminant < 0)
		return false;

	auto d2 = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-halfB - d2) / a;
	if (root < tMin || tMax < root) {
		root = (-halfB + d2) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	auto p = ray.positionAt(root);
	auto outwardNormal = (p - center) / _radius;
	auto uv = getSphereUv(outwardNormal);
	auto ff = ray.direction().dot(outwardNormal) < 0;
	auto n = ff ? outwardNormal : -outwardNormal;

	rec->position = p;
	rec->normal = n;
	rec->material = _material;
	rec->t = root;
	rec->u = uv.u;
	rec->v = uv.v;
	rec->frontFace = ff;
	return true;
}

Aabb MovingSphere::boundingBox(double exposureTime) const {
	auto c0 = _centerT0 - _velocity * exposureTime / 2;
	auto c1 = _centerT0 + _velocity * exposureTime / 2;
	auto v = Vec3(_radius, _radius, _radius);
	auto box0 = Aabb(c0 - v, c0 + v);
	auto box1 = Aabb(c1 - v, c1 + v);
	return Aabb::surroundingAabb(box0, box1);
}
