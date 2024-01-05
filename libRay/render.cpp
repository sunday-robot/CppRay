#include "render.h"

#include <iostream>
#include <omp.h>
#include "Material.h"

static const double _tMin = 0.001;

/**
 * 色を返す
 * @param ray レイ
 * @param world 物体群
 * @param depth 残りの追跡回数
 * @return 色
 */
static Color color(std::shared_ptr<const Hittable> world, const Color* background, const Ray& ray, int depth) {
	// 追跡回数が規定値に達した場合は(0,0,0)を返す
	if (depth <= 0)
		return Color::black;

	HitRecord rec;
	if (!world->hit(ray, _tMin, DBL_MAX, &rec)) {
		// どの物体ともヒットしない場合は、指定された背景色あるいは天球の色を返す
		if (background == 0) {
			auto unitDirection = ray.direction().unit();
			auto t = 0.5 * (unitDirection.y() + 1);
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

Color* render(std::shared_ptr<const Hittable> world, const Color* background, const Camera& camera, int width, int height, int maxDepth, int sampleCount) {
	auto pixels = new Color[(size_t)height * width];
	auto processed_lines = 0;
	//omp_set_num_threads(8);	// スレッド数をコア数に合わせて8に制限(通常は16スレッドを使う)したら少し改善するかもしれないと思ったが、速度は明らかに低下した。(6.5秒だった処理が8.2秒に低下するなど。竜はわからない。メモリからのデータ読み込み待ち間に計算しているということなのだろうか？）(多分使用電力量は少なくできているとは思う。)
#pragma omp parallel for schedule(dynamic)	// 8.2,6.3,6.5,6.3
//#pragma omp parallel for schedule(dynamic, 1)	// 8.2,6.7
//#pragma omp parallel for schedule(static, 1)	// 8.0,6.6,6.8
//#pragma omp parallel for schedule(static, 2)	// 8.2
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
			// VC++の解析機能が弱いため、「C6835:pixelsから無効なデータを読み取っています。」が発せられる。(添え字をチェックするif文を追加すると解消する。）
			pixels[y * width + x] = rgbSum / sampleCount;
#pragma warning(pop)
		}
#pragma omp atomic
		processed_lines++;
		auto tn = omp_get_thread_num();
#pragma omp critical
		std::cout << "(" << tn << ")" << processed_lines << "/" << height << std::endl;
	}
	return pixels;
}
