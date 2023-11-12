#include "createFinalScene.h"
#include <vector>
#include "Bvh.h"
#include "Hittable.h"
#include "Color.h"
#include "Lambertian.h"
#include "Box.h"
#include "createBvhTree.h"
#include "DiffuseLight.h"
#include "MovingSphere.h"
#include "Sphere.h"
#include "Dielectric.h"
#include "Metal.h"
#include "ConstantMedium.h"
#include "ImageTexture.h"
#include "NoiseTexture.h"
#include "util.h"
#include "Translate.h"
#include "RotateY.h"

Scene createFinalScene() {
	auto objects = std::vector<Hittable*>();
	{
		// 床に敷き詰められた淡い緑の箱
		auto boxes1 = std::vector<Hittable*>();
		{
			auto material = new Lambertian(0.48, 0.83, 0.53);
			auto boxesPerSide = 20;
			auto w = 100;
			for (int i = 0; i < boxesPerSide; i++) {
				for (int j = 0; j < boxesPerSide; j++) {
					auto x0 = -1000 + i * w;
					auto z0 = -1000 + j * w;
					auto y0 = 0;
					auto x1 = x0 + w;
					auto y1 = 1 + getRandomDouble(0, 100);
					auto z1 = z0 + w;

					boxes1.push_back(new Box(Vec3(x0, y0, z0), Vec3(x1, y1, z1), material));
				}
			}
		}
		objects.push_back(createBvhTree(boxes1, 1));

		// 天井の白い四角い照明
		auto light = new DiffuseLight(7, 7, 7);
		objects.push_back(new XzRect(123, 147, 423, 412, 554, light));

		// 画面左上の移動中のオレンジ色の球
		auto center = Vec3(400, 400, 200);
		auto velocity = Vec3(30, 0, 0);
		auto movingSphereMaterial = new Lambertian(0.7, 0.3, 0.1);
		objects.push_back(new MovingSphere(center, 50, movingSphereMaterial, velocity));

		// 画面中央下部のガラス玉
		objects.push_back(new Sphere(Vec3(260, 150, 45), 50, new Dielectric(1.5)));

		// 画面右下の銀色の玉
		objects.push_back(new Sphere(Vec3(0, 150, 145), 50, new Metal(Color(0.8, 0.8, 0.9), 1)));

		// 画面左下のガラス玉？
		{
			auto boundary = new Sphere(Vec3(360, 150, 145), 70, new Dielectric(1.5));
			objects.push_back(boundary);
			objects.push_back(new ConstantMedium(boundary, 0.2, Color(0.2, 0.4, 0.9)));
		}
		// シーン全体を覆う霧
		{
			auto boundary = new Sphere(Vec3(0, 0, 0), 5000, new Dielectric(1.5));
			objects.push_back(new ConstantMedium(boundary, .0001, Color(1, 1, 1)));
		}

		// 画面左の地球
		auto emat = new Lambertian(new ImageTexture("../../../earthmap.bmp"));
		objects.push_back(new Sphere(Vec3(400, 200, 400), 100, emat));

		// 画面中央の白い球
		auto pertext = new NoiseTexture(0.1);
		objects.push_back(new Sphere(Vec3(220, 280, 300), 80, new Lambertian(pertext)));

		// 画面左上の小さな球の集団
		auto boxes2 = std::vector<Hittable*>();
		auto white = new Lambertian(.73, .73, .73);
		int ns = 1000;
		for (int j = 0; j < ns; j++) {
			boxes2.push_back(new Sphere(Vec3(getRandomDouble(), getRandomDouble(), getRandomDouble()) * 165, 10, white));
		}
		objects.push_back(new Translate(RotateY::create(createBvhTree(boxes2, 1), 15), Vec3(-100, 270, 395)));
	}

	auto lookFrom = Vec3(478, 278, -600);
	auto lookAt = Vec3(278, 278, 0);
	auto vFov = 40;
	auto aperture = 0;
	auto exposureTime = 1;
	Camera camera = Camera::createCamera(lookFrom, lookAt, Vec3(0, 1, 0), vFov, 16.0 / 9, aperture, exposureTime);

	return Scene(objects, camera, Color::black);
}
