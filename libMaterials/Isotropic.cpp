#include "Isotropic.h"
#include "util.h"

bool Isotropic::scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const {
	auto attenuation = _albedo->value(rec.u, rec.v, rec.position);
	auto scattered = Ray(rec.position, randomInUnitSphere(), ray.time());
	scatterResult->ray = scattered;
	scatterResult->color = attenuation;
	return true;
}
