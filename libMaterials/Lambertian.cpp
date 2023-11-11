#include "Lambertian.h"
#include "util.h"

static bool nearZero(const Vec3 &a) {
	// Return true if the vector is close to zero in all dimensions.
	auto s = 1e-8;
	return (fabs(a.x) < s) && (fabs(a.y) < s) && (fabs(a.z) < s);
}

bool Lambertian::scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const {
	auto scatterDirection = rec.normal + randomInUnitSphere();

	// Catch degenerate scatter direction
	if (nearZero(scatterDirection))
		scatterDirection = rec.normal;	// 

	scatterResult->ray = Ray(rec.position, scatterDirection, ray.time());
	scatterResult->color = _albedo->value(rec.u, rec.v, rec.position);
	return true;
}
