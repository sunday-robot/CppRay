#include "createSingleSphereScene.h"
#include "DebugMaterial.h"
#include "Lambertian.h"
#include "Sphere.h"
#include "DiffuseLight.h"

Scene createSingleSphereScene()
{
	auto objects = std::vector<std::shared_ptr<const Hittable>>();
	{
#if false
		auto material = new DebugMaterial();
#else
		Color color(0.5, 0.5, 1.0);
		auto material = new Lambertian(color);
#endif
		objects.push_back(sp(new Sphere(Vec3(0, 0, 0), 50, sp(material))));

		auto lightMaterial = new DiffuseLight(7, 7, 7);
		objects.push_back(sp(new Sphere(Vec3(-50, -50, -50), 30, sp(lightMaterial))));
	}

	auto lookFrom = Vec3(0, 0, -200);
	auto lookAt = Vec3(0, 0, 0);
	auto vFov = 40;
	auto aperture = 0;
	auto exposureTime = 1;
	Camera camera = Camera::createCamera(lookFrom, lookAt, Vec3(0, 1, 0), vFov, 16.0 / 9, aperture, exposureTime);

	return Scene(objects, camera, Color::black);
}
