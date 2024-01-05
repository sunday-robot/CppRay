#pragma once

#include <memory>
#include "Material.h"
#include "Texture.h"
#include "SolidColorTexture.h"
#include "util.h"

class Isotropic :public Material {
	const std::shared_ptr<const Texture> _albedo;

public:
	Isotropic(std::shared_ptr<const Texture> texture) : _albedo(texture) {}

	Isotropic(Color rgb) : Isotropic(sp(new SolidColorTexture(rgb))) {}

	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;
};
