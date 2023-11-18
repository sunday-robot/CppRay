#include "render.h"
#include <iostream>
#include "Material.h"

static const double _tMin = 0.001;

/**
 * �F��Ԃ�
 * @param ray ���C
 * @param world ���̌Q
 * @param depth �c��̒ǐՉ�
 * @return �F
 */
static Color color(const Hittable* world, const Color* background, Ray ray, int depth) {
	// �ǐՉ񐔂��K��l�ɒB�����ꍇ��(0,0,0)��Ԃ�
	if (depth <= 0)
		return Color::black;

	HitRecord rec;
	if (!world->hit(ray, _tMin, DBL_MAX, &rec)) {
		// �ǂ̕��̂Ƃ��q�b�g���Ȃ��ꍇ�́A�w�肳�ꂽ�w�i�F���邢�͓V���̐F��Ԃ�
		if (background == 0) {
			auto unitDirection = ray.direction().unit();
			auto t = 0.5 * (unitDirection.y + 1);
			auto v1 = Color(1, 1, 1);
			auto v2 = Color(0.5, 0.7, 1);
			return (1 - t) * v1 + t * v2;
		} else
			return *background;
	}
	auto emitted = rec.material->emitted(rec.u, rec.v, rec.position);
	ScatterResult scatterResult;
	if (!rec.material->scatter(ray, rec, &scatterResult))
		return emitted;
	return emitted + scatterResult.color * color(world, background, scatterResult.ray, depth - 1);
}

Color* render(Hittable* world, Color* background, const Camera& camera, int width, int height, int maxDepth, int sampleCount) {
	auto pixels = new Color[(size_t)height * width];
	auto processed_lines = 0;
#pragma omp parallel for
	for (auto y = 0; y < height; y++) {
		for (auto x = 0; x < width; x++) {
			auto rgbSum = Color(0, 0, 0);
			for (auto i = 0; i < sampleCount; i++) {
				auto u = (x + getRandomDouble()) / width;
				auto v = (height - 1.0 - y + getRandomDouble()) / height;
				auto r = camera.ray(u, v);
				auto rgb = color(world, background, r, maxDepth);
				rgbSum += rgb;
			}
#pragma warning(push)
#pragma warning(disable:6385)
			// VC++�̃o�O�ŁA�Ӗ��s���Ȍx������������
			pixels[y * width + x] = rgbSum / sampleCount;
#pragma warning(pop)
		}
		processed_lines++;
		std::cout << processed_lines << "/" << height << std::endl;
	}
	return pixels;
}
