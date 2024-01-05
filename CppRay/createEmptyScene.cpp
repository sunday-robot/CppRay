#include "createEmptyScene.h"

Scene createEmptyScene() {
	auto objects = std::vector<std::shared_ptr<const Hittable>>();

	auto lookFrom = Vec3(478, 278, -600);
	auto lookAt = Vec3(278, 278, 0);
	auto vFov = 40;
	auto aperture = 0;
	auto exposureTime = 1;
	Camera camera = Camera::createCamera(lookFrom, lookAt, Vec3(0, 1, 0), vFov, 16.0 / 9, aperture, exposureTime);

	return Scene(objects, camera, Color::black);
}
