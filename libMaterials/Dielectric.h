#pragma once

#include "Material.h"

// �U�d�̃}�e���A��(�����ȍގ�)
class Dielectric : public Material {
	// ���ܗ�
	const double _refractiveIndex;

public:
	Dielectric(double refractiveIndex) : _refractiveIndex(refractiveIndex) {}

	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;

	//public override string ToString()
	//{
	//	return $"Dielectric({_refractiveIndex})";
	//}
};
