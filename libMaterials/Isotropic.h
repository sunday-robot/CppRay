#pragma once
#include "Material.h"
#include "Texture.h"
#include "SolidColorTexture.h"

class Isotropic :public Material {
	const Texture* _albedo;

public:
	Isotropic(const Texture* texture) : _albedo(texture) {}

	Isotropic(Color rgb) : Isotropic(new SolidColorTexture(rgb)) {}

	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;
};
