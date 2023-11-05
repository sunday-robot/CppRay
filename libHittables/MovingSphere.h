#pragma once
#include "Hittable.h"
#include "Material.h"

class MovingSphere : public Hittable {
	// íÜêSÇÃà íu
	const Vec3 _center;

	// îºåa
	const double _radius;

	// ëfçﬁ
	const Material* const _material;

	// ë¨ìx
	const Vec3 _velocity;

public:
	MovingSphere(Vec3 center, double radius, const Material* material, Vec3 velocity)
		: _center(center),
		_radius(radius),
		_material(material),
		_velocity(velocity) {}

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;
	Aabb boundingBox(double exposureTime) const;

	//public override string ToString()
	//{
	//	return $"MovigSphere(c:{_center}, r:{_radius}, m:{_material}, v:{_velocity})";
	//}
};
