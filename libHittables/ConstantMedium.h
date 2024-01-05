#pragma once

#include <memory>
#include "Hittable.h"
#include "Texture.h"
#include "Isotropic.h"
#include "SolidColorTexture.h"
#include "util.h"

// 霧のような物体
// 他のHittableと比べると特殊なもので、直接形状をあらわすものではなく、
// メンバ変数として形状を表すHittableを保持する。
// 
class ConstantMedium : public Hittable {
	static const Vec3 _dummyNormal; // (0, 0, 0);

	const std::shared_ptr<const Hittable> _boundary;
	const std::shared_ptr<const Material> _phaseFunction;
	const double _negInvDensity;

public:
	ConstantMedium(std::shared_ptr<const Hittable> b, double d, std::shared_ptr<const Texture> a)
		: _boundary(b), _negInvDensity(-1 / d), _phaseFunction(sp(new Isotropic(a))) {}

	ConstantMedium(std::shared_ptr<const Hittable> b, double d, Color c)
		: ConstantMedium(b, d, sp(new SolidColorTexture(c))) { }

	bool hit(const Ray& ray, double tMin, double tMax, HitRecord* rec) const;

	Aabb boundingBox(double exposureTime) const {
		return _boundary->boundingBox(exposureTime);
	}
};
