#pragma once

#include <memory>
#include "Material.h"
#include "Color.h"
#include "SolidColorTexture.h"
#include "util.h"

class DiffuseLight : public Material {
	const std::shared_ptr<const Texture> _emit;

public:
	DiffuseLight(std::shared_ptr<const Texture> texture) : _emit(texture) {}
	DiffuseLight(const Color& rgb) : DiffuseLight(sp(new SolidColorTexture(rgb))) { }
	DiffuseLight(double r, double g, double b) : DiffuseLight(Color(r, g, b)) { }
	virtual Color emitted(double u, double v, const Vec3& p) const { return _emit->value(u, v, p); }
	virtual bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult*) const { return false; }
};
