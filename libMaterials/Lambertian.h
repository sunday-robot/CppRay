#pragma once

#include "Material.h"
#include "SolidColorTexture.h"

// Š®‘S‚ÈŠgU”½Ë‚ğ‚·‚éŞ¿(“üËŠp‚Æ‚Í–³ŠÖŒW‚É”½Ë‚·‚é)
class Lambertian : public Material {
	// ‘fŞ‚ÌF</summary>
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
