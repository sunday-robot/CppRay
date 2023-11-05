#pragma once

#include "Material.h"
#include "SolidColorTexture.h"

// ���S�Ȋg�U���˂�����ގ�(���ˊp�Ƃ͖��֌W�ɔ��˂���)
class Lambertian : public Material {
	// �f�ނ̐F</summary>
	const Texture* const _albedo;

public:
	Lambertian(const Texture* const albedo) : _albedo(albedo) {	}

	Lambertian(const Color& rgb) : Lambertian(new SolidColorTexture(rgb)) { }

	Lambertian(double r, double g, double b) : Lambertian(Color(r, g, b)) { }

	virtual	Color emitted(double u, double v, const Vec3& p) const { return Color::black; }

	virtual bool scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const;

	//public override string ToString()
	//{
	//	return $"Lambertian({_albedo})";
	//}
};
