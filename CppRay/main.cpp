#include "createEmptyScene.h"
#include "createSingleSphereScene.h"
#include "createFinalScene.h"
#include <iostream>
#include "createBvhTree.h"
#include <chrono>
#include "saveBmp.h"
#include "render.h"

int main() {
#if true
	auto imageWidth = 1280;
	auto imageHeight = 720;
#else
	auto imageWidth = 320;
	auto imageHeight = 180;
#endif

	//auto overSamplingCount = 1000;	// 320x180でも1000ならノイズが分からないほどキレイになるかと思ったが、それほどでもなかった…
	//auto overSamplingCount = 100;
	//auto overSamplingCount = 20;
	auto overSamplingCount = 10;

	//auto scene = createEmptyScene();
	//auto scene = createSingleSphereScene();
	//var (hittables, camera, background) = CreateXyRectScene();
	//var (hittables, camera, background) = CreateSingleBoxScene();
	//var (hittables, camera, background) = CreateCornellSmoke();
	auto scene = createFinalScene();
	//var (hittables, camera, background) = CreateFinalScene2();
	//var (hittables, camera, background) = CreateCornellBox();
	//var (hittables, camera, background) = CreateSimpleLight();
	//var (hittables, camera, background) = CreateSimpleScene();
	//var (hittables, camera, background) = CreateSimpleScene2();
	//var (hittables, camera, background) = CreateScene0();
	//var (hittables, camera, background) = CreateScene1();
	//var (hittables, camera, background) = CreateScene2();
	//var (hittables, camera, background) = Create2PerlinSpheresScene();
	//var (hittables, camera, background) = CreateRandomScene();
#if true
	auto world = createBvhTree(scene.hittables(), scene.camera().exposureTime());
	//world.Print();
#else
	var world = new HittableList(hittables);
#endif
	Hittable* hs = world;
	Color bg = scene.backgroundColor();
#if true
	{
		Bvh::setDebugMode(true);
		auto pixels = render(hs, &bg, scene.camera(), imageWidth, imageHeight, 1, 1);
		saveBmp("SpheresBb.bmp", pixels, imageWidth, imageHeight);
		delete pixels;

		Bvh::setDebugMode(false);
	}
#endif
	auto start = std::chrono::system_clock::now();
	auto pixels = render(hs, &bg, scene.camera(), imageWidth, imageHeight, 50, overSamplingCount);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "time = " << duration.count() << std::endl;
	std::cin;

	saveBmp("Spheres.bmp", pixels, imageWidth, imageHeight);

	delete pixels;
}
