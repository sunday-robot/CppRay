#include "Metal.h"
#include "util.h"

bool Metal::scatter(const Ray& ray, const HitRecord& rec, ScatterResult* scatterResult) const {
	auto reflectionDirection = reflect(ray.direction().unit(), rec.normal);
	auto scattered = Ray(rec.position, reflectionDirection + _fuzz * randomInUnitSphere(), ray.time());
	if (scattered.direction().dot(rec.normal) <= 0)
		return false;
	scatterResult->ray = scattered;
	scatterResult->color = _albedo;
	return true;
}
