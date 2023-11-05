#pragma once

#include <tuple>
#include "HitRecord.h"
#include "ScatterResult.h"
#include "Vec3.h"

// �f�ނ̊��N���X
class Material abstract {
protected:
	// v: ���˃x�N�g��
	// normal: �@���x�N�g��
	// ���˃x�N�g��
	static Vec3 reflect(const Vec3& v, const Vec3& normal) {
		return v - 2 * v.dot(normal) * normal;
	}

	// v: ���˃x�N�g��
	// normal: �@���x�N�g��
	// niOverNt: ?
	// ���܃x�N�g��(���܂��Ȃ��ꍇ��null)
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

	virtual bool scatter(	// �Փ˓_�ŕ��U(�H)���ꂽ���C
		const Ray& ray,						// ���C
		const HitRecord& rec,	// �Փˏ��
		ScatterResult* scatterResult) const = 0;
};
