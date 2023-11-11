#pragma once
#include "Hittable.h"
#include "Material.h"

// 等速直線運動している球
// Sphereとの違いは、以下の２点のみ。
// (1) MovingShereには速度がプロパティとして存在する。
// (2) MovingShereは、hit()での球の中心座標を計算で求める。
// おそらく(2)によるhit()の速度低下はほとんど無視できる程度と思われるので、
// Shereは廃止してもよいかも。
class MovingSphere : public Hittable {
	// t = 0の時の中心の位置
	const Vec3 _centerT0;

	// 半径
	const double _radius;

	// 素材
	const Material* const _material;

	// 速度
	const Vec3 _velocity;

public:
	MovingSphere(Vec3 centerT0, double radius, const Material* material, Vec3 velocity)
		: _centerT0(centerT0),
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
