#pragma once

#include "Material.h"

// 誘電体マテリアル(透明な材質)
class Dielectric : public Material {
	// 屈折率
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
