#pragma once

#include "Material.h"
#include "Color.h"

// 金属マテリアル
class Metal : public Material {
	// 色
	const Color _albedo;

	// <=1
	const double _fuzz;

public:
	Metal(const Color& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz) {}

	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	virtual bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;

	//public override string ToString()
	//{
	//	return $"Metal({_albedo}, fuzz:{_fuzz:0.000})";
	//}
};
