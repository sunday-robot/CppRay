#include "Camera.h"

Ray Camera::ray(double s, double t) const {
	auto rd = lensRadius * randomInUnitDisk();
	auto offset = u * rd.x() + v * rd.y();
	auto o = origin + offset;
	auto d = lowerLeftCorner + s * horizontal + t * vertical - o;
	auto time = (getRandomDouble(-0.5, 0.5)) * _exposureTime;
	return Ray(o, d, time);
}

Camera Camera::createCamera(
	Vec3 lookFrom,
	Vec3 lookAt,
	Vec3 vup,
	double verticalFov,
	double aspect,
	double aperture,
	double exposureTime) {
	auto theta = verticalFov * M_PI / 180;
	auto halfHeight = tan(theta / 2);
	auto halfWidth = aspect * halfHeight;
	auto w = (lookAt - lookFrom).unit();
	auto u = -vup.cross(w).unit();
	auto v = -w.cross(u);
	auto focusDist = (lookAt - lookFrom).length();
	auto lowerLeftCorner = (lookFrom + focusDist * w
		- halfWidth * focusDist * u
		- halfHeight * focusDist * v);
	auto horizontal = 2 * halfWidth * focusDist * u;
	auto vertical = 2 * halfHeight * focusDist * v;
	auto lensRadius = aperture / 2;
	return Camera(lowerLeftCorner, horizontal, vertical, lookFrom, u, v, lensRadius, exposureTime);
}
