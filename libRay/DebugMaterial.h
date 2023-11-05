#pragma once

#include "Material.h"
#include "util.h"

class DebugMaterial : public Material {
	const Color _color = randomHueColor(1, 1);
public:
	Color emitted(double u, double v, const Vec3& p) const {
		return _color;
	}
	bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult *scatterResult) const {
		return false;
	}
};
