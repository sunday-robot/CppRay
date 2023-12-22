#include "createFinalScene.h"
#include <vector>
#include "Box.h"
#include "ConstantMedium.h"
#include "createBvhTree.h"
#include "Dielectric.h"
#include "DiffuseLight.h"
#include "ImageTexture.h"
#include "Lambertian.h"
#include "Metal.h"
#include "MovingSphere.h"
#include "NoiseTexture.h"
#include "RotateY.h"
#include "Sphere.h"
#include "Translate.h"
#include "util.h"

Scene createFinalScene() {
	auto objects = std::vector<const Hittable*>();
	{
		// 床に敷き詰められた淡い緑の箱
#if true
		auto boxes1 = std::vector<const Hittable*>();
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
#if false
		objects.push_back(createBvhTree(boxes1, 1));
#else
		objects.insert(objects.end(), boxes1.begin(), boxes1.end());
#endif
#endif
		// 天井の白い四角い照明
#if true
		auto light = new DiffuseLight(7, 7, 7);
		objects.push_back(new XzRect(123, 147, 423, 412, 554, light));
#endif
		// BVHデバッグ用。少し低い位置の天井の白い四角い照明
#if false
		auto light = new DiffuseLight(7, 7, 7);
		objects.push_back(new XzRect(123, 147, 423, 412, 200, light));
#endif
		// 画面左上の移動中のオレンジ色の球
#if true
		auto center = Vec3(400, 400, 200);
		auto velocity = Vec3(30, 0, 0);
		auto movingSphereMaterial = new Lambertian(0.7, 0.3, 0.1);
		objects.push_back(new MovingSphere(center, 50, movingSphereMaterial, velocity));
#endif
		// 画面中央下部のガラス玉
#if true
		objects.push_back(new Sphere(Vec3(260, 150, 45), 50, new Dielectric(1.5)));
#endif
		// 画面右下の銀色の玉
#if true
		objects.push_back(new Sphere(Vec3(0, 150, 145), 50, new Metal(Color(0.8, 0.8, 0.9), 1)));
#endif
		// 画面左下のガラス玉？
#if true
		{
			auto boundary = new Sphere(Vec3(360, 150, 145), 70, new Dielectric(1.5));
			objects.push_back(boundary);
			objects.push_back(new ConstantMedium(boundary, 0.2, Color(0.2, 0.4, 0.9)));
		}
#endif
		// シーン全体を覆う霧
#if true
		{
			auto boundary = new Sphere(Vec3(0, 0, 0), 5000, new Dielectric(1.5));
			objects.push_back(new ConstantMedium(boundary, .0001, Color(1, 1, 1)));
		}
#endif
		// (デバッグ用)シーン中央部のみに存在する球形の霧
#if false
		{
			auto boundary = new Sphere(Vec3(278, 278, 0), 200, new Dielectric(1.5));
			objects.push_back(new ConstantMedium(boundary, .0001, Color(1, 1, 1)));
		}
#endif
		// 画面左の地球
#if true
		auto emat = new Lambertian(new ImageTexture("earthmap.bmp"));
		objects.push_back(new Sphere(Vec3(400, 200, 400), 100, emat));
#endif
		// 画面中央の白い球
#if true
		auto pertext = new NoiseTexture(0.1);
		objects.push_back(new Sphere(Vec3(220, 280, 300), 80, new Lambertian(pertext)));
#endif
		// 画面左上の小さな球の集団
#if true
		{
			const auto white = new Lambertian(.73, .73, .73);
			const auto sphereCount = 1000;
			const auto sphereRadius = 10;
			auto boxes2 = std::vector<const Hittable*>();
			for (auto j = 0; j < sphereCount; j++) {
				auto sphere = new Sphere(Vec3(getRandomDouble(), getRandomDouble(), getRandomDouble()) * 165, sphereRadius, white);
				boxes2.push_back(sphere);
			}
#if false
			objects.push_back(new Translate(RotateY::create(createBvhTree(boxes2, 1), 15), Vec3(-100, 270, 395)));
#else
			objects.push_back(new Translate(RotateY::create(createBvhTree(boxes2, 1), 15), Vec3(-100, 270, 395)));
#endif
		}
#else
#if true
		{
			const auto sphereCount = 3;
			const auto sphereRadius = 50;
			auto boxes2 = std::vector<const Hittable*>();

			for (auto i = 0; i < sphereCount; i++) {
				for (auto j = 0; j < sphereCount; j++) {
					for (auto k = 0; k < sphereCount; k++) {
						const auto material = new Lambertian(
							i / (sphereCount - 1.0),
							j / (sphereCount - 1.0),
							k / (sphereCount - 1.0));
						auto sphere = new Sphere(
							Vec3(i * sphereRadius * 2, j * sphereRadius * 2, k * sphereRadius * 2),
							sphereRadius,
							material);
						boxes2.push_back(sphere);
					}
				}
			}
			const Hittable* hittable;
			hittable = createBvhTree(boxes2, 1);
			hittable = RotateY::create(hittable, 15);
			//hittable = RotateY::create(hittable, 0);
			hittable = new Translate(hittable, Vec3(-100, 270, 395));
			objects.push_back(hittable);
		}
#else
		{
			const double sphereRadius = 100;
			auto o = Vec3(278, 278, 400);
			Material* material;
			Vec3 vec3;

			vec3 = Vec3(-sphereRadius * 2, 0, 0);
			material = new Lambertian(1, 0, 0);
			objects.push_back(new Sphere(o + vec3, sphereRadius, material));

			vec3 = Vec3(0, 0, 0);
			material = new Lambertian(0, 1, 0);
			objects.push_back(new Sphere(o + vec3, sphereRadius, material));

			vec3 = Vec3(sphereRadius * 2, 0, 0);
			material = new Lambertian(0, 0, 1);
			objects.push_back(new Sphere(o + vec3, sphereRadius, material));

			material = new Lambertian(1, 1, 1);
			vec3 = Vec3(0, sphereRadius * 2, 0);
			objects.push_back(new Sphere(o + vec3, sphereRadius, material));
			vec3 = Vec3(0, -sphereRadius * 2, 0);
			objects.push_back(new Sphere(o + vec3, sphereRadius, material));
		}
#endif
#endif
		// C++版でのRotateYのバグ調査用の立方体
#if false
		{
			auto material = new Lambertian(0.48, 0.83, 0.53);
			Hittable* hittable = new Box(Vec3(0, 0, 0), Vec3(100, 100, 100), material);
			//hittable = RotateY::create(hittable, 15);
			//hittable = RotateY::create(hittable, 0);
			hittable = RotateY::create(hittable, 45);
			objects.push_back(hittable);
		}
#endif
	}

	auto lookFrom = Vec3(478, 278, -600);
	auto lookAt = Vec3(278, 278, 0);
	auto vFov = 40;
	auto aperture = 0;
	auto exposureTime = 1;
	Camera camera = Camera::createCamera(lookFrom, lookAt, Vec3(0, 1, 0), vFov, 16.0 / 9, aperture, exposureTime);

	return Scene(objects, camera, Color::black);
}
