#include <iostream>
#include "perlinNoise.h"
#include "saveBmp.h"

int main() {
	auto colors = new Color[100 * 100];
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			auto v = perlinNoise(x / 2.0, y / 2.0, 0);
			colors[y * 100 + x] = Color(v, v, v);
		}
	}
	saveBmp("perlin.bmp", colors, 100, 100);

	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			auto v = perlinNoise2(x / 2.0, y / 2.0, 0, 7);
			colors[y * 100 + x] = Color(v, v, v);
		}
	}
	saveBmp("perlin2.bmp", colors, 100, 100);

	return 0;
}
