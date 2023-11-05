#include "Lambertian.h"
#include "util.h"

bool Lambertian::scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const {
	auto scatterDirection = rec.normal + randomInUnitSphere();

	// Catch degenerate scatter direction
	if (scatterDirection.nearZero())
		scatterDirection = rec.normal;

	scatterResult->ray = Ray(rec.position, scatterDirection, ray.time());
	scatterResult->color = _albedo->value(rec.u, rec.v, rec.position);
	return true;
}
