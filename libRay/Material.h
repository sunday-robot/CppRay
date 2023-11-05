#pragma once

#include <tuple>
#include "HitRecord.h"
#include "ScatterResult.h"
#include "Vec3.h"

// 素材の基底クラス
class Material abstract {
protected:
	// v: 入射ベクトル
	// normal: 法線ベクトル
	// 反射ベクトル
	static Vec3 reflect(const Vec3& v, const Vec3& normal) {
		return v - 2 * v.dot(normal) * normal;
	}

	// v: 入射ベクトル
	// normal: 法線ベクトル
	// niOverNt: ?
	// 屈折ベクトル(屈折しない場合はnull)
	static std::tuple<bool, const Vec3&> refract(Vec3 v, Vec3 normal, double niOverNt) {
		auto uv = v.unit();
		auto dt = uv.dot(normal);
		auto discriminant = 1 - niOverNt * niOverNt * (1 - dt * dt);
		if (discriminant <= 0) {
			return std::make_tuple(false, Vec3::o);
		}
		return std::make_tuple(true, niOverNt * (uv - normal * dt) - normal * sqrt(discriminant));
	}

public:
	virtual Color emitted(double u, double v, const Vec3& p) const = 0;

	virtual bool scatter(	// 衝突点で分散(？)されたレイ
		const Ray& ray,						// レイ
		const HitRecord& rec,	// 衝突情報
		ScatterResult* scatterResult) const = 0;
};
