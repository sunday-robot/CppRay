#pragma once

#include "Vec3.h"

class Material;

// RayとHittableの衝突情報
struct HitRecord {
	// 衝突点
	Vec3 position;

	// 衝突点の法線
	Vec3 normal;

	// 衝突点の表面素材
	const Material* material;

	// レイ軸上の位置
	double t;

	double u;
	double v;

	// 表面でヒットしたのか、裏面でヒットしたのか(屈折率をそのまま使うか、逆数にして使うかの判定に必要)
	bool frontFace;

#pragma warning(push)
#pragma warning(disable : 26495)
	HitRecord() {};
#pragma warning(pop)

	HitRecord(double t, const Vec3& position, const Vec3& normal, const Material* material, bool frontFace = false, double u = 0, double v = 0) :
		t(t), position(position), normal(normal), material(material), frontFace(frontFace), u(u), v(v) {};
};
