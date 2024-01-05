#pragma once

#include <memory>
#include "Material.h"
#include "SolidColorTexture.h"
#include "util.h"

// ���S�Ȋg�U���˂�����ގ�(���ˊp�Ƃ͖��֌W�ɔ��˂���)
class Lambertian : public Material {
	// �f�ނ̐F</summary>
	const std::shared_ptr<const Texture> _albedo;

public:
	Lambertian(const std::shared_ptr<const Texture> albedo) : _albedo(albedo) {	}

	Lambertian(const Color& rgb) : Lambertian(sp(new SolidColorTexture(rgb))) { }

	Lambertian(double r, double g, double b) : Lambertian(Color(r, g, b)) { }

	virtual	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	virtual bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;

	//public override string ToString()
	//{
	//	return $"Lambertian({_albedo})";
	//}
};
