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
};
