#include "Dielectric.h"
#include "util.h"

static double reflectance(double cosine, double refIdx) {
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - refIdx) / (1 + refIdx);
	auto r02 = r0 * r0;
	return r0 + (1 - r02) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& rec, ScatterResult*scatterResult) const {
	auto attenuation = Color(1, 1, 1);

	auto refractionRatio = rec.frontFace ? (1 / _refractiveIndex) : _refractiveIndex;

	auto unitDirection = ray.direction().unit();
	auto dt = unitDirection.dot(rec.normal);
	auto cosTheta = std::min(-dt, 1.0);
	auto sinTheta = sqrt(1 - cosTheta * cosTheta);

	//auto cannotRefract = refractionRatio * sinTheta > 1;
	Vec3 direction;
	if (refractionRatio * sinTheta > 1) {
		direction = reflect(unitDirection, rec.normal);
	}
	else {
		if (reflectance(cosTheta, refractionRatio) > getRandomDouble(0, 1))
			direction = reflect(unitDirection, rec.normal);
		else {
#if false
			direction = Refract(unitDirection, rec.Normal, refractionRatio);
#else
			auto discriminant = 1 - refractionRatio * refractionRatio * (1 - dt * dt);
			if (discriminant <= 0) {
				return 0;
			}
			direction = refractionRatio * (unitDirection - rec.normal * dt)
				- rec.normal * sqrt(discriminant);
#endif
		}
	}
	auto scattered = Ray(rec.position, direction, ray.time());

	scatterResult->ray = scattered;
	scatterResult->color = attenuation;

	return true;
}
