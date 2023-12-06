#pragma once
#include "Hittable.h"
#include "Material.h"
#include "Uv.h"
#define _USE_MATH_DEFINES
#include <math.h>

/// <summary>
/// 球。Hittableの具象クラス。
/// 中心座標、半径、素材で構成される。
/// </summary>
class Sphere : public Hittable {
	// 位置
	const Vec3 _center;

	// 半径
	const double _radius;

	// 素材
	const Material* const _material;

public:
	/// <param name="center"></param>
	/// <param name="radius">半径</param>
	/// <param name="material"></param>
	Sphere(Vec3 center, double radius, const Material* material)
		: _center(center),
		_radius(radius),
		_material(material) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const {
		auto oc = ray.origin() - _center;
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
		auto outwardNormal = (p - _center) / _radius;
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

	Aabb boundingBox(double exposureTime) const {
		auto v = Vec3(_radius, _radius, _radius);
		return Aabb(_center - v, _center + v);
	}

	static Uv getSphereUv(Vec3 p) {
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

	//public override string ToString()
	//{
	//	return $"MovigSphere(c:{_center}, r:{_radius}, m:{_material}, v:{_velocity})";
	//}
};
